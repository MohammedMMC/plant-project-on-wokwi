#include "DHT.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define DHT22_PIN 28

DHT dht(DHT22_PIN, DHT22);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // put your setup code here, to run once:
  dht.begin();
  pinMode(DHT22_PIN, INPUT);
  Serial1.begin(115200);
  Serial1.println("Hello, Raspberry Pi Pico W!");

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial1.println("SSD1306 allocation failed");
    for(;;);
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  displayScreen();
  delay(100); // this speeds up the simulation
}


void displayScreen() {
  // Get Humidity and Temperature
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Clear the screen
  display.clearDisplay();
  display.setTextColor(WHITE);        

  // Display (Humidity and Temperature) 
  display.setCursor(0,0);         
  display.println("Humidity:");
  display.setCursor(SCREEN_WIDTH / 2 + 5,0);
  display.println("Temp:");
  display.setCursor(0,10);         
  display.println(String(h, 1) + "%");   
  display.setCursor(SCREEN_WIDTH / 2 + 5,10);
  display.println(String(t, 1) + "C");

  display.drawLine(SCREEN_WIDTH / 2, 0, 
    SCREEN_WIDTH / 2, 25, WHITE);
  display.drawLine(0, 25, 
    SCREEN_WIDTH, 25, WHITE);

  
  display.display();
}