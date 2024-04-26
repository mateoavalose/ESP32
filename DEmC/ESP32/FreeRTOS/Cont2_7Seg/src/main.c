#include <stddef.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define GPIO_LED_A1 0
#define GPIO_LED_PIN_SEL_A1 (1ULL << GPIO_LED_A1)
#define GPIO_LED_B1 4
#define GPIO_LED_PIN_SEL_B1 (1ULL << GPIO_LED_B1)
#define GPIO_LED_C1 16
#define GPIO_LED_PIN_SEL_C1 (1ULL << GPIO_LED_C1)
#define GPIO_LED_D1 17
#define GPIO_LED_PIN_SEL_D1 (1ULL << GPIO_LED_D1)
#define GPIO_LED_E1 5
#define GPIO_LED_PIN_SEL_E1 (1ULL << GPIO_LED_E1)
#define GPIO_LED_F1 15
#define GPIO_LED_PIN_SEL_F1 (1ULL << GPIO_LED_F1)
#define GPIO_LED_G1 2
#define GPIO_LED_PIN_SEL_G1 (1ULL << GPIO_LED_G1)

#define GPIO_LED_A2 12
#define GPIO_LED_PIN_SEL_A2 (1ULL << GPIO_LED_A2)
#define GPIO_LED_B2 14
#define GPIO_LED_PIN_SEL_B2 (1ULL << GPIO_LED_B2)
#define GPIO_LED_C2 27
#define GPIO_LED_PIN_SEL_C2 (1ULL << GPIO_LED_C2)
#define GPIO_LED_D2 26
#define GPIO_LED_PIN_SEL_D2 (1ULL << GPIO_LED_D2)
#define GPIO_LED_E2 25
#define GPIO_LED_PIN_SEL_E2 (1ULL << GPIO_LED_E2)
#define GPIO_LED_F2 33
#define GPIO_LED_PIN_SEL_F2 (1ULL << GPIO_LED_F2)
#define GPIO_LED_G2 32
#define GPIO_LED_PIN_SEL_G2 (1ULL << GPIO_LED_G2)

static void display_number1(int number){
    switch (number){
        case 0:
            gpio_set_level(GPIO_LED_A1, 1);
            gpio_set_level(GPIO_LED_B1, 1);
            gpio_set_level(GPIO_LED_C1, 1);
            gpio_set_level(GPIO_LED_D1, 1);
            gpio_set_level(GPIO_LED_E1, 1);
            gpio_set_level(GPIO_LED_F1, 1);
            gpio_set_level(GPIO_LED_G1, 0);
            break;
        case 1:
            gpio_set_level(GPIO_LED_A1, 0);
            gpio_set_level(GPIO_LED_B1, 1);
            gpio_set_level(GPIO_LED_C1, 1);
            gpio_set_level(GPIO_LED_D1, 0);
            gpio_set_level(GPIO_LED_E1, 0);
            gpio_set_level(GPIO_LED_F1, 0);
            gpio_set_level(GPIO_LED_G1, 0);
            break;
        case 2:
            gpio_set_level(GPIO_LED_A1, 1);
            gpio_set_level(GPIO_LED_B1, 1);
            gpio_set_level(GPIO_LED_C1, 0);
            gpio_set_level(GPIO_LED_D1, 1);
            gpio_set_level(GPIO_LED_E1, 1);
            gpio_set_level(GPIO_LED_F1, 0);
            gpio_set_level(GPIO_LED_G1, 1);
            break;
        case 3:
            gpio_set_level(GPIO_LED_A1, 1);
            gpio_set_level(GPIO_LED_B1, 1);
            gpio_set_level(GPIO_LED_C1, 1);
            gpio_set_level(GPIO_LED_D1, 1);
            gpio_set_level(GPIO_LED_E1, 0);
            gpio_set_level(GPIO_LED_F1, 0);
            gpio_set_level(GPIO_LED_G1, 1);
            break;
        case 4:
            gpio_set_level(GPIO_LED_A1, 0);
            gpio_set_level(GPIO_LED_B1, 1);
            gpio_set_level(GPIO_LED_C1, 1);
            gpio_set_level(GPIO_LED_D1, 0);
            gpio_set_level(GPIO_LED_E1, 0);
            gpio_set_level(GPIO_LED_F1, 1);
            gpio_set_level(GPIO_LED_G1, 1);
            break;
        case 5:
            gpio_set_level(GPIO_LED_A1, 1);
            gpio_set_level(GPIO_LED_B1, 0);
            gpio_set_level(GPIO_LED_C1, 1);
            gpio_set_level(GPIO_LED_D1, 1);
            gpio_set_level(GPIO_LED_E1, 0);
            gpio_set_level(GPIO_LED_F1, 1);
            gpio_set_level(GPIO_LED_G1, 1);
            break;
        case 6:
            gpio_set_level(GPIO_LED_A1, 1);
            gpio_set_level(GPIO_LED_B1, 0);
            gpio_set_level(GPIO_LED_C1, 1);
            gpio_set_level(GPIO_LED_D1, 1);
            gpio_set_level(GPIO_LED_E1, 1);
            gpio_set_level(GPIO_LED_F1, 1);
            gpio_set_level(GPIO_LED_G1, 1);
            break;
        case 7:
            gpio_set_level(GPIO_LED_A1, 1);
            gpio_set_level(GPIO_LED_B1, 1);
            gpio_set_level(GPIO_LED_C1, 1);
            gpio_set_level(GPIO_LED_D1, 0);
            gpio_set_level(GPIO_LED_E1, 0);
            gpio_set_level(GPIO_LED_F1, 0);
            gpio_set_level(GPIO_LED_G1, 0);
            break;
        case 8:
            gpio_set_level(GPIO_LED_A1, 1);
            gpio_set_level(GPIO_LED_B1, 1);
            gpio_set_level(GPIO_LED_C1, 1);
            gpio_set_level(GPIO_LED_D1, 1);
            gpio_set_level(GPIO_LED_E1, 1);
            gpio_set_level(GPIO_LED_F1, 1);
            gpio_set_level(GPIO_LED_G1, 1);
            break;
        case 9:
            gpio_set_level(GPIO_LED_A1, 1);
            gpio_set_level(GPIO_LED_B1, 1);
            gpio_set_level(GPIO_LED_C1, 1);
            gpio_set_level(GPIO_LED_D1, 1);
            gpio_set_level(GPIO_LED_E1, 0);
            gpio_set_level(GPIO_LED_F1, 1);
            gpio_set_level(GPIO_LED_G1, 1);
            break;
        default:
            gpio_set_level(GPIO_LED_A1, 0);
            gpio_set_level(GPIO_LED_B1, 0);
            gpio_set_level(GPIO_LED_C1, 0);
            gpio_set_level(GPIO_LED_D1, 0);
            gpio_set_level(GPIO_LED_E1, 0);
            gpio_set_level(GPIO_LED_F1, 0);
            gpio_set_level(GPIO_LED_G1, 0);
            break;
    }
}

static void display_number2(int number){
    switch (number){
        case 0:
            gpio_set_level(GPIO_LED_A2, 1);
            gpio_set_level(GPIO_LED_B2, 1);
            gpio_set_level(GPIO_LED_C2, 1);
            gpio_set_level(GPIO_LED_D2, 1);
            gpio_set_level(GPIO_LED_E2, 1);
            gpio_set_level(GPIO_LED_F2, 1);
            gpio_set_level(GPIO_LED_G2, 0);
            break;
        case 1:
            gpio_set_level(GPIO_LED_A2, 0);
            gpio_set_level(GPIO_LED_B2, 1);
            gpio_set_level(GPIO_LED_C2, 1);
            gpio_set_level(GPIO_LED_D2, 0);
            gpio_set_level(GPIO_LED_E2, 0);
            gpio_set_level(GPIO_LED_F2, 0);
            gpio_set_level(GPIO_LED_G2, 0);
            break;
        case 2:
            gpio_set_level(GPIO_LED_A2, 1);
            gpio_set_level(GPIO_LED_B2, 1);
            gpio_set_level(GPIO_LED_C2, 0);
            gpio_set_level(GPIO_LED_D2, 1);
            gpio_set_level(GPIO_LED_E2, 1);
            gpio_set_level(GPIO_LED_F2, 0);
            gpio_set_level(GPIO_LED_G2, 1);
            break;
        case 3:
            gpio_set_level(GPIO_LED_A2, 1);
            gpio_set_level(GPIO_LED_B2, 1);
            gpio_set_level(GPIO_LED_C2, 1);
            gpio_set_level(GPIO_LED_D2, 1);
            gpio_set_level(GPIO_LED_E2, 0);
            gpio_set_level(GPIO_LED_F2, 0);
            gpio_set_level(GPIO_LED_G2, 1);
            break;
        case 4:
            gpio_set_level(GPIO_LED_A2, 0);
            gpio_set_level(GPIO_LED_B2, 1);
            gpio_set_level(GPIO_LED_C2, 1);
            gpio_set_level(GPIO_LED_D2, 0);
            gpio_set_level(GPIO_LED_E2, 0);
            gpio_set_level(GPIO_LED_F2, 1);
            gpio_set_level(GPIO_LED_G2, 1);
            break;
        case 5:
            gpio_set_level(GPIO_LED_A2, 1);
            gpio_set_level(GPIO_LED_B2, 0);
            gpio_set_level(GPIO_LED_C2, 1);
            gpio_set_level(GPIO_LED_D2, 1);
            gpio_set_level(GPIO_LED_E2, 0);
            gpio_set_level(GPIO_LED_F2, 1);
            gpio_set_level(GPIO_LED_G2, 1);
            break;
        case 6:
            gpio_set_level(GPIO_LED_A2, 1);
            gpio_set_level(GPIO_LED_B2, 0);
            gpio_set_level(GPIO_LED_C2, 1);
            gpio_set_level(GPIO_LED_D2, 1);
            gpio_set_level(GPIO_LED_E2, 1);
            gpio_set_level(GPIO_LED_F2, 1);
            gpio_set_level(GPIO_LED_G2, 1);
            break;
        case 7:
            gpio_set_level(GPIO_LED_A2, 1);
            gpio_set_level(GPIO_LED_B2, 1);
            gpio_set_level(GPIO_LED_C2, 1);
            gpio_set_level(GPIO_LED_D2, 0);
            gpio_set_level(GPIO_LED_E2, 0);
            gpio_set_level(GPIO_LED_F2, 0);
            gpio_set_level(GPIO_LED_G2, 0);
            break;
        case 8:
            gpio_set_level(GPIO_LED_A2, 1);
            gpio_set_level(GPIO_LED_B2, 1);
            gpio_set_level(GPIO_LED_C2, 1);
            gpio_set_level(GPIO_LED_D2, 1);
            gpio_set_level(GPIO_LED_E2, 1);
            gpio_set_level(GPIO_LED_F2, 1);
            gpio_set_level(GPIO_LED_G2, 1);
            break;
        case 9:
            gpio_set_level(GPIO_LED_A2, 1);
            gpio_set_level(GPIO_LED_B2, 1);
            gpio_set_level(GPIO_LED_C2, 1);
            gpio_set_level(GPIO_LED_D2, 1);
            gpio_set_level(GPIO_LED_E2, 0);
            gpio_set_level(GPIO_LED_F2, 1);
            gpio_set_level(GPIO_LED_G2, 1);
            break;
        default:
            gpio_set_level(GPIO_LED_A2, 0);
            gpio_set_level(GPIO_LED_B2, 0);
            gpio_set_level(GPIO_LED_C2, 0);
            gpio_set_level(GPIO_LED_D2, 0);
            gpio_set_level(GPIO_LED_E2, 0);
            gpio_set_level(GPIO_LED_F2, 0);
            gpio_set_level(GPIO_LED_G2, 0);
            break;
    }
}

static void init_hw(void){
    //Seven Segment 1
    // A LED 1
    gpio_config_t io_conf;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED_PIN_SEL_A1;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    // B LED 1
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED_PIN_SEL_B1;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    // C LED 1
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED_PIN_SEL_C1;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    // D LED 1
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED_PIN_SEL_D1;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    // E LED 1
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED_PIN_SEL_E1;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    // F LED 1
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED_PIN_SEL_F1;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    // G LED 1
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED_PIN_SEL_G1;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    //Seven Segment 2
    // A LED 2
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED_PIN_SEL_A2;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    // B LED 2
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED_PIN_SEL_B2;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    // C LED 2
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED_PIN_SEL_C2;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    // D LED 2
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED_PIN_SEL_D2;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    // E LED 2
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED_PIN_SEL_E2;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    // F LED 2
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED_PIN_SEL_F2;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    // G LED 2
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED_PIN_SEL_G2;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
}

void app_main() {
    int freq_ms = 400;
    init_hw();
    while(1){
        for(int i = 0; i < 10; i++){
            display_number2(i);
            for(int j = 0; j < 10; j++){
                display_number1(j);
                vTaskDelay(freq_ms / portTICK_PERIOD_MS);
            }
        }
    }
}