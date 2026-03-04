#define LED_PIN 2  

// Blink Task
void blinkTask(void *pvParameters) {
  pinMode(LED_PIN, OUTPUT);

  while (true) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(500));
    digitalWrite(LED_PIN, LOW);
    vTaskDelay(pdMS_TO_TICKS(500));

    // Stack usage check
    UBaseType_t stackLeft = uxTaskGetStackHighWaterMark(NULL);
    Serial.print("Blink Task stack left: ");
    Serial.println(stackLeft);
  }
}

// UART Task
void uartTask(void *pvParameters) {
  pinMode(22, OUTPUT);
  while (true) {
    Serial.println("Hello from UART task!");
    vTaskDelay(pdMS_TO_TICKS(1000));
       digitalWrite(22, HIGH);
    vTaskDelay(pdMS_TO_TICKS(500));
    digitalWrite(22, LOW);
    vTaskDelay(pdMS_TO_TICKS(500));

    // Stack usage check
    UBaseType_t stackLeft = uxTaskGetStackHighWaterMark(NULL);
    Serial.print("UART Task stack left: ");
    Serial.println(stackLeft);
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Create tasks
  xTaskCreate(
    blinkTask, "Blink Task",
    2048, NULL, 1, NULL
  );

  xTaskCreate(
    uartTask, "UART Task",
    4000, NULL, 2, NULL
  );
}

void loop() {
  // Empty
}