//AROUXET_COLOMBRES_FERRAZZO_ORDINSKAS_REBORATTI
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
// DHT
#define DHTPIN 23
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
// Pines
#define LED_PIN 25
#define SW1 26 // Subir umbral
#define SW2 27 // Bajar umbral
// Estados
enum Estado { P1, P2 };
Estado estadoActual = P1;
// Variables
float temperatura = 0;
int umbral = 28;
unsigned long ultimoTiempoLectura = 0;
const unsigned long INTERVALO_LECTURA = 2000;
// Botones
bool sw1Actual = false;
bool sw2Actual = false;
bool sw1Anterior = false;
bool sw2Anterior = false;
void setup() {
Serial.begin(115200);
dht.begin();
pinMode(LED_PIN, OUTPUT);
digitalWrite(LED_PIN, LOW);
pinMode(SW1, INPUT_PULLUP);
pinMode(SW2, INPUT_PULLUP);
if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
Serial.println(F("No se pudo encontrar una pantalla OLED"));
while (true);
}
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(0, 0);
display.println(F("Sistema Iniciado"));
display.display();
delay(1000);
display.clearDisplay();
}
void loop() {
unsigned long ahora = millis();
// Leer botones
sw1Actual = !digitalRead(SW1); // Invertimos porque INPUT_PULLUP
sw2Actual = !digitalRead(SW2);
// Leer temperatura periódicamente
if (ahora - ultimoTiempoLectura >= INTERVALO_LECTURA) {
ultimoTiempoLectura = ahora;
float t = dht.readTemperature();
if (!isnan(t)) {
  temperatura = t;
}
}
// Control de LED
if (temperatura > umbral) {
digitalWrite(LED_PIN, HIGH);
} else {
digitalWrite(LED_PIN, LOW);
}
// Transición de pantalla si ambos botones están presionados
if (sw1Actual && sw2Actual && !(sw1Anterior && sw2Anterior)) {
estadoActual = (estadoActual == P1) ? P2 : P1;
delay(200); // Pequeño rebote para evitar cambio doble
}
// Lógica de estado
switch (estadoActual) {
case P1:
mostrarPantalla1();
break;
case P2:
if (sw1Actual && !sw1Anterior) {
umbral++;
}
if (sw2Actual && !sw2Anterior) {
umbral--;
}
mostrarPantalla2();
break;
}
// Guardar estado anterior de botones
sw1Anterior = sw1Actual;
sw2Anterior = sw2Actual;
}
// Mostrar pantalla 1
void mostrarPantalla1() {
display.clearDisplay();
display.setTextSize(2);
display.setCursor(0, 0);
display.print("T: ");
display.print(temperatura, 1);
display.print("C");
display.setCursor(0, 30);
display.setTextSize(2);
display.print("Umbral:");
display.setCursor(80, 30);
display.print(umbral);
display.display();
}
// Mostrar pantalla 2 (modificación de umbral)
void mostrarPantalla2() {
display.clearDisplay();
display.setTextSize(2);
display.setCursor(0, 0);
display.println("Set Umbral:");
display.setCursor(40, 30);
display.print(umbral);
display.display();
}
}
