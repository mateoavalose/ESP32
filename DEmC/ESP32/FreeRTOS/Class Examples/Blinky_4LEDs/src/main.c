#include <stddef.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define GPIO_LED1 16
#define GPIO_LED_PIN_SEL1 (1ULL << GPIO_LED1)
#define GPIO_LED2 17
#define GPIO_LED_PIN_SEL2 (1ULL << GPIO_LED2)
#define GPIO_LED3 5
#define GPIO_LED_PIN_SEL3 (1ULL << GPIO_LED3)
#define GPIO_LED4 18
#define GPIO_LED_PIN_SEL4 (1ULL << GPIO_LED4)

static void init_hw(void){
    gpio_config_t io_conf;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED_PIN_SEL1;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED_PIN_SEL2;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED_PIN_SEL3;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED_PIN_SEL4;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
}

void app_main() {
    init_hw();
    while(1){
        gpio_set_level(GPIO_LED1, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);

        gpio_set_level(GPIO_LED1, 0);
        gpio_set_level(GPIO_LED2, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);

        gpio_set_level(GPIO_LED2, 0);
        gpio_set_level(GPIO_LED3, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        
        gpio_set_level(GPIO_LED3, 0);
        gpio_set_level(GPIO_LED4, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);

        gpio_set_level(GPIO_LED4, 0);
        gpio_set_level(GPIO_LED3, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);

        gpio_set_level(GPIO_LED3, 0);
        gpio_set_level(GPIO_LED2, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);

        gpio_set_level(GPIO_LED2, 0);
    }
}