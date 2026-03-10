#include <Arduino.h>
#include <stdlib.h>   // rand() ব্যবহার করার জন্য

TaskHandle_t led2Handle;    // GPIO2 LED টাস্কের handle
TaskHandle_t led22Handle;   // GPIO22 LED টাস্কের handle

// Blink Task for GPIO2
void blinkTask2(void *pvParameters) {
  pinMode(2, OUTPUT);
  while (true) {
    digitalWrite(2, HIGH);
    vTaskDelay(pdMS_TO_TICKS(500));
    digitalWrite(2, LOW);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

// Blink Task for GPIO22
void blinkTask22(void *pvParameters) {
  pinMode(22, OUTPUT);
  while (true) {
    digitalWrite(22, HIGH);
    vTaskDelay(pdMS_TO_TICKS(500));
    digitalWrite(22, LOW);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

// Controller Task: Randomly suspend/resume LEDs
void controlTask(void *pvParameters) {
  while (true) {
    int choice = rand() % 2; // 0 বা 1 randomly আসবে

    if (choice == 0) {
      vTaskSuspend(led2Handle);
      vTaskResume(led22Handle);
      Serial.println("GPIO2 LED suspended, GPIO22 LED resumed!");
    } else {
      vTaskSuspend(led22Handle);
      vTaskResume(led2Handle);
      Serial.println("GPIO22 LED suspended, GPIO2 LED resumed!");
    }

    vTaskDelay(pdMS_TO_TICKS(5000)); // প্রতি ৫ সেকেন্ডে পরিবর্তন হবে
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // LED2 Task তৈরি
  xTaskCreate(
    blinkTask2, "Blink LED2",
    2048, NULL, 1, &led2Handle
  );

  // LED22 Task তৈরি
  xTaskCreate(
    blinkTask22, "Blink LED22",
    2048, NULL, 1, &led22Handle
  );

  // Controller Task তৈরি
  xTaskCreate(
    controlTask, "Controller",
    2048, NULL, 2, NULL
  );
}

void loop() {
  // খালি থাকবে
}