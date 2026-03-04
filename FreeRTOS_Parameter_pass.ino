// Blink Task with parameter
void blinkTask(void *pvParameters) {
  int pin = *((int*)pvParameters);  // parameter কে int হিসেবে পড়া

  pinMode(pin, OUTPUT);

  while (true) {
    digitalWrite(pin, HIGH);
    vTaskDelay(pdMS_TO_TICKS(500));
    digitalWrite(pin, LOW);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // LED পিন নম্বর
  static int led1 = 2;   // Built-in LED
  static int led2 = 25;  // External LED

  // প্রথম টাস্ক: LED1 blink করবে
  xTaskCreate(
    blinkTask, "Blink LED1",
    2048, &led1, 1, NULL
  );

  // দ্বিতীয় টাস্ক: LED2 blink করবে
  xTaskCreate(
    blinkTask, "Blink LED2",
    2048, &led2, 1, NULL
  );
}

void loop() {
  // খালি থাকবে
}