

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// Define LED pin (adjust to your board)
#define LED_PIN 2  

// Task: Blink LED
void blink_task(void *pvParameter) {
    gpio_pad_select_gpio(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    while (1) {
        gpio_set_level(LED_PIN, 1);   // LED ON
        vTaskDelay(500 / portTICK_PERIOD_MS); // 500ms delay
        gpio_set_level(LED_PIN, 0);   // LED OFF
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

// Task: Print over UART
void uart_task(void *pvParameter) {
    while (1) {
        printf("Hello from UART task!\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS); // 1s delay
    }
}

void app_main() {
    // Create tasks
    xTaskCreate(&blink_task, "blink_task", 2048, NULL, 5, NULL);
    xTaskCreate(&uart_task, "uart_task", 2048, NULL, 6, NULL);
}