#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  Serial.println(F("Hello, Serhii!"));

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Serhii Remez");
}

void loop() {
  
}