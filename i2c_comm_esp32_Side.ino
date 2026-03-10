#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD address (scanner দিয়ে নিশ্চিত করো)
#define STM32_ADDR 0x08   // STM32 Slave address

void setup() {
  Serial.begin(115200);
  Wire.begin(21,22); // ESP32 default SDA=21, SCL=22
  lcd.init();
  lcd.backlight();
}

void loop() {
  // LCD তে টেক্সট দেখানো
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hello from ESP32");

  // STM32 Slave এ টেক্সট পাঠানো
  const char *msg = "Hello";
  Wire.beginTransmission(STM32_ADDR);
  Wire.write((const uint8_t*)msg, strlen(msg));
  Wire.endTransmission();

  delay(2000);
}