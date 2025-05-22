//AROUXET_COLOMBRES_FERRAZZO_ORDINSKAS_REBORATTI
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
// Definir dimensiones de la pantalla OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C
// Configuración del sensor DHT11
#define DHTPIN 23 // Pin donde está conectado el DHT11
#define DHTTYPE DHT11 // Tipo de sensor (DHT11 o DHT22)
// Crear objetos para el OLED y el DHT11
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
DHT dht(DHTPIN, DHTTYPE);
void setup() {
 Serial.begin(115200);
 dht.begin(); // Iniciar sensor DHT11
 // Iniciar la pantalla OLED
 if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
 Serial.println(F("No se pudo encontrar una pantalla OLED"));
 for (;;); // Bucle infinito si falla la inicialización
 }
 delay(1000);
 display.clearDisplay();
 // Mensaje de bienvenida
 display.setTextSize(1);
 display.setTextColor(WHITE);
 display.setCursor(0, 0);
 display.println(F("Sensor de Temp. y Hum."));
 display.display();
 delay(2000);
 display.clearDisplay();
}
void loop() {
 // Leer la temperatura y humedad del DHT11
 float temperatura = dht.readTemperature();
 float humedad = dht.readHumidity();
 // Verificar si la lectura es válida
 if (isnan(temperatura) || isnan(humedad)) {
 Serial.println(F("Error al leer el sensor DHT11"));
 return;
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
 display.display(); // Actualizar pantalla
 delay(2000); // Esperar 2 segundos antes de actualizar
}
