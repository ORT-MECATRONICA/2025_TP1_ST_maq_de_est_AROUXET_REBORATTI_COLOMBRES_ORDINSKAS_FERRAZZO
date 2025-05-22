//AROUXET_COLOMBRES_FERRAZZO_ORDINSKAS_REBORATTI
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // Ancho del OLED en píxeles
#define SCREEN_HEIGHT 64 // Alto del OLED en píxeles
// Dirección I2C del OLED (0x3C o 0x3D según el modelo)
#define OLED_ADDRESS 0x3C
// Crear objeto para la pantalla OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
void setup() {
 Serial.begin(115200);
 // Iniciar la pantalla OLED
 if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
 Serial.println(F("Fallo al iniciar OLED"));
 for (;;);
 }
 delay(1000); // Pequeña pausa
 display.clearDisplay(); // Limpiar la pantalla
 // Configurar texto
 display.setTextSize(2); // Tamaño de la fuente
 display.setTextColor(WHITE); // Color del texto
 display.setCursor(10, 20); // Posición del texto
 // Mostrar mensaje
 display.println("Hola mundo");
 display.display(); // Mostrar en pantalla
}
void loop() {
 // No es necesario hacer nada en loop(), ya que el mensaje es estático
}
