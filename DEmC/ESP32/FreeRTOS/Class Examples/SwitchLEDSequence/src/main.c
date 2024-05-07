#include <stddef.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define GPIO_LED1 14
#define GPIO_LED1_PIN_SEL (1ULL << GPIO_LED1)
#define GPIO_LED2 27
#define GPIO_LED2_PIN_SEL (1ULL << GPIO_LED2)
#define GPIO_LED3 26
#define GPIO_LED3_PIN_SEL (1ULL << GPIO_LED3)
#define GPIO_LED4 25
#define GPIO_LED4_PIN_SEL (1ULL << GPIO_LED4)

#define GPIO_BUT1 33
#define GPIO_BUT1_PIN_SEL (1ULL << GPIO_BUT1)
#define ESP_INTR_FLAG_DEFAULT 0

static void seq1(void){
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

static void seq2(void){
    gpio_set_level(GPIO_LED1, 1);
    gpio_set_level(GPIO_LED2, 1);
    gpio_set_level(GPIO_LED3, 1);
    gpio_set_level(GPIO_LED4, 1);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    
    gpio_set_level(GPIO_LED1, 0);
    gpio_set_level(GPIO_LED2, 0);
    gpio_set_level(GPIO_LED3, 0);
    gpio_set_level(GPIO_LED4, 0);
    vTaskDelay(500 / portTICK_PERIOD_MS);
}

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

    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED3_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED4_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = GPIO_BUT1_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);
}

void app_main() {
    init_hw();
    while(1){
        while(!gpio_get_level(GPIO_BUT1)){
            seq2();
        }
        seq1();
    }
}