#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  Wire.begin(21,22);   // SDA = 21, SCL = 22

  lcd.begin(16,2);     // initialize LCD
  lcd.backlight();     

  lcd.setCursor(0,0);
  lcd.print("Hello");
}

void loop()
{

}