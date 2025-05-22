//AROUXET_COLOMBRES_FERRAZZO_ORDINSKAS_REBORATTI
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
// Dimensiones de la pantalla OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C
// Configuración del sensor DHT11
#define DHTPIN 23
#define DHTTYPE DHT11
// Pin del relé o LED (ajustalo según tu conexión)
#define RELAY_PIN 25
// Intervalo entre lecturas (en milisegundos)
const unsigned long INTERVALO_LECTURA = 2000;
unsigned long ultimoTiempoLectura = 0;
// Crear objetos
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
DHT dht(DHTPIN, DHTTYPE);
void setup() {
 Serial.begin(115200);
 dht.begin();
 // Inicializar el pin del relé/LED
 pinMode(RELAY_PIN, OUTPUT);
 digitalWrite(RELAY_PIN, LOW); // Apagado al iniciar
 // Iniciar pantalla OLED
 if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
 Serial.println(F("No se pudo encontrar una pantalla OLED"));
 while (true); // Detener si falla la pantalla
 }
 display.clearDisplay();
 display.setTextSize(1);
 display.setTextColor(WHITE);
 display.setCursor(0, 0);
 display.println(F("Sensor de Temp. y Hum."));
 display.display();
 delay(1000); // Este sí es aceptable por única vez en setup
 display.clearDisplay();
}
void loop() {
 unsigned long tiempoActual = millis();
 if (tiempoActual - ultimoTiempoLectura >= INTERVALO_LECTURA) {
 ultimoTiempoLectura = tiempoActual;
 float temperatura = dht.readTemperature();
 float humedad = dht.readHumidity();
 if (isnan(temperatura) || isnan(humedad)) {
 Serial.println(F("Error al leer el sensor DHT11"));
 return;
 }
 // Control del relé
 if (temperatura > 28.0) {
 digitalWrite(RELAY_PIN, HIGH); // Encender
 } else {
 digitalWrite(RELAY_PIN, LOW); // Apagar
 }
 // Mostrar en Serial Monitor
 Serial.print(F("Temperatura: "));
 Serial.print(temperatura);
 Serial.print(F(" °C | Humedad: "));
 Serial.print(humedad);
 Serial.println(F(" %"));
 // Mostrar en pantalla OLED
 display.clearDisplay();
 display.setTextSize(2);
 display.setTextColor(WHITE);
 display.setCursor(0, 0);
 display.print("T: ");
 display.print(temperatura);
 display.print(" C");
 display.setCursor(0, 30);
 display.print("H: ");
 display.print(humedad);
 display.print(" %");
 display.display();
 }
}
