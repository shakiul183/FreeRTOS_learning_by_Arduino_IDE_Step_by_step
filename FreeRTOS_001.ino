#define LED_PIN 2  // Built-in LED on most ESP32 boards

// Task: Blink LED
void blinkTask(void *pvParameters) {
  pinMode(LED_PIN, OUTPUT);

  while (true) {
    digitalWrite(LED_PIN, HIGH);   // LED ON
    vTaskDelay(pdMS_TO_TICKS(500)); // 500ms delay
    digitalWrite(LED_PIN, LOW);    // LED OFF
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

// Task: Print over UART
void uartTask(void *pvParameters) {
  while (true) {
    Serial.println("Hello from UART task!");
    vTaskDelay(pdMS_TO_TICKS(1000)); // 1s delay
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000); // Give Serial time to initialize

  // Create tasks with larger stack sizes
  xTaskCreate(
    blinkTask, "Blink Task",
    2048, NULL, 1, NULL
  );

  xTaskCreate(
    uartTask, "UART Task",
    4096, NULL, 2, NULL
  );
}

void loop() {
  // Empty — tasks run independently under FreeRTOS
}