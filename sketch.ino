#include "DHT.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define DHT22_PIN 28

#define RGB_R_PIN 6
#define RGB_G_PIN 7
#define RGB_B_PIN 8

DHT dht(DHT22_PIN, DHT22);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int led_r = 0, led_g = 0, led_b = 0;


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

  pinMode(RGB_R_PIN, OUTPUT);
  pinMode(RGB_G_PIN, OUTPUT);
  pinMode(RGB_B_PIN, OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
  displayScreen();
  rgblight();
  delay(100); // this speeds up the simulation
}


void rgblight() {
  analogWrite(RGB_R_PIN, led_r);
  analogWrite(RGB_G_PIN, led_g);
  analogWrite(RGB_B_PIN, led_b);
}

void displayScreen() {
  // Get Humidity and Temperature
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Clear the screen
  display.clearDisplay();
  display.setTextColor(WHITE);        

  // Display (Humidity and Temperature) 
  display.setTextSize(1);
  display.setCursor(5,0);         
  display.println("Humidity:");
  display.setCursor(SCREEN_WIDTH / 2 + 20,0);
  display.println("Temp:");
  display.setCursor(10,10);         
  display.println(String(h, 1) + " %");   
  display.setCursor(SCREEN_WIDTH / 2 + 15,10);
  display.println(String(t, 1) + " C");

  display.drawLine(SCREEN_WIDTH / 2, 0, 
    SCREEN_WIDTH / 2, 25, WHITE);
  display.drawLine(0, 25, 
    SCREEN_WIDTH, 25, WHITE);

  for (int i = 1; i < 3; i++) {
    display.drawLine(SCREEN_WIDTH / 3 * i, 25, 
      SCREEN_WIDTH / 3 * i, SCREEN_HEIGHT, WHITE);
  }

  display.setTextSize(2);
  display.setCursor(0 + 16, (SCREEN_HEIGHT + 10) / 2);
  display.println("R");
  display.setCursor(SCREEN_WIDTH / 3 + 16, (SCREEN_HEIGHT + 10) / 2);
  display.println("G");
  display.setCursor(SCREEN_WIDTH / 3 * 2 + 16, (SCREEN_HEIGHT + 10) / 2);
  display.println("B");

  display.setTextSize(1);
  display.setCursor(0 + 18, (SCREEN_HEIGHT + 45) / 2);
  display.println(String(led_r));
  display.setCursor(SCREEN_WIDTH / 3 + 18, (SCREEN_HEIGHT + 45) / 2);
  display.println(String(led_g));
  display.setCursor(SCREEN_WIDTH / 3 * 2 + 18, (SCREEN_HEIGHT + 45) / 2);
  display.println(String(led_b));

  
  display.display();
}