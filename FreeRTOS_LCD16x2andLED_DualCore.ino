#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD address সাধারণত 0x27 বা 0x3F হয়, তোমার মডিউল অনুযায়ী ঠিক করতে হবে
LiquidCrystal_I2C lcd(0x27, 16, 2);

TaskHandle_t ledTaskHandle;
TaskHandle_t lcdTaskHandle;

// LED Task (Core 1)
void ledTask(void *pvParameters) {
  pinMode(2, OUTPUT);
  while (true) {
    digitalWrite(2, HIGH);
    vTaskDelay(pdMS_TO_TICKS(500));
    digitalWrite(2, LOW);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

// LCD Task (Core 0)
void lcdTask(void *pvParameters) {
  lcd.init();       // LCD initialize
  lcd.backlight();  // Backlight ON

  while (true) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ESP32 Dual Core");
    lcd.setCursor(0, 1);
    lcd.print("LED + LCD Demo");
    vTaskDelay(pdMS_TO_TICKS(2000));

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Core0: LCD Print");
    lcd.setCursor(0, 1);
    lcd.print("Core1: LED Blink");
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // LED Task pinned to Core 1
  xTaskCreatePinnedToCore(
    ledTask, "LED Task",
    2048, NULL, 1, &ledTaskHandle, 1
  );

  // LCD Task pinned to Core 0
  xTaskCreatePinnedToCore(
    lcdTask, "LCD Task",
    4096, NULL, 1, &lcdTaskHandle, 0
  );
}

void loop() {
  // খালি থাকবে
}