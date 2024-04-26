#include <stddef.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define GPIO_LED1 23
#define GPIO_LED1_PIN_SEL (1ULL << GPIO_LED1)
#define GPIO_LED2 22
#define GPIO_LED2_PIN_SEL (1ULL << GPIO_LED2)
#define GPIO_BUT1 26
#define GPIO_BUT1_PIN_SEL (1ULL << GPIO_BUT1)
#define GPIO_BUT2 27
#define GPIO_BUT2_PIN_SEL (1ULL << GPIO_BUT2)
#define ESP_INTR_FLAG_DEFAULT 0

static void init_hw(void){
    gpio_config_t io_conf;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED1_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED2_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = GPIO_BUT1_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);

    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = GPIO_BUT2_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);
}

void app_main() {
    init_hw();
    while(1){
        gpio_set_level(GPIO_LED1, !gpio_get_level(GPIO_BUT1));
        gpio_set_level(GPIO_LED2, !gpio_get_level(GPIO_BUT2));
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}