#define LED1 2    // Built-in LED (GPIO2)
#define LED2 22   // External LED connected to GPIO34

// Task: Blink LED on Core 1
void blinkTaskCore1(void *pvParameters) {
  pinMode(LED1, OUTPUT);
  while (true) {
    digitalWrite(LED1, HIGH);
    vTaskDelay(pdMS_TO_TICKS(500));
    digitalWrite(LED1, LOW);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

// Task: Blink LED on Core 0
void blinkTaskCore0(void *pvParameters) {
  pinMode(LED2, OUTPUT);
  while (true) {
    digitalWrite(LED2, HIGH);
    vTaskDelay(pdMS_TO_TICKS(1000));
    digitalWrite(LED2, LOW);
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Create task pinned to Core 1
  xTaskCreatePinnedToCore(
    blinkTaskCore1,     // Task function
    "Blink Core1",      // Name
    2048,               // Stack size
    NULL,               // Parameters
    1,                  // Priority
    NULL,               // Task handle
    1                   // Core ID (Core 1)
  );

  // Create task pinned to Core 0
  xTaskCreatePinnedToCore(
    blinkTaskCore0,
    "Blink Core0",
    2048,
    NULL,
    1,
    NULL,
    0                   // Core ID (Core 0)
  );
}

void loop() {
  // Empty — tasks run independently on different cores
}