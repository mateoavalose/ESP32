#include <stddef.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// 7 segment display pins
#define a 18
#define b 19
#define c 1
#define d 22
#define e 23
#define f 21
#define g 3

#define GPIO_a_PIN_SEL (1ULL << a)
#define GPIO_b_PIN_SEL (1ULL << b)
#define GPIO_c_PIN_SEL (1ULL << c)
#define GPIO_d_PIN_SEL (1ULL << d)
#define GPIO_e_PIN_SEL (1ULL << e)
#define GPIO_f_PIN_SEL (1ULL << f)
#define GPIO_g_PIN_SEL (1ULL << g)

// Transistor pins to cycle through the 7 segment displays
#define tran1 4
#define GPIO_tran1_PIN_SEL (1ULL << tran1)
#define tran2 0
#define GPIO_tran2_PIN_SEL (1ULL << tran2)


// Functions
void display(int num);

void init_hw() {
    // 7 segment display pins
    gpio_config_t io_conf;
    // a
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_a_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    // b
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_b_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    // c
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_c_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    // d
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_d_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    // e
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_e_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    // f
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_f_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    // g
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_g_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    // Transistor pins
    // tran1
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_tran1_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    // tran2
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_tran2_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
}

void app_main() {
    init_hw();
    int disp1 = 0;
    int disp2 = 0;
    int second = 0;
    while(1) {
        gpio_set_level(tran1, 0);
        gpio_set_level(tran2, 0);
        
        display(disp1);
        gpio_set_level(tran1, 1);
        gpio_set_level(tran2, 0);
        vTaskDelay(10 / portTICK_PERIOD_MS);

        gpio_set_level(tran1, 0);
        gpio_set_level(tran2, 0);

        display(disp2);
        gpio_set_level(tran1, 0);
        gpio_set_level(tran2, 1);
        vTaskDelay(10 / portTICK_PERIOD_MS);

        second++;
        if (second == 50) {
            second = 0;
            disp1++;
            if (disp1 == 10) {
                disp1 = 0;
                disp2++;
                if (disp2 == 10) {
                    disp2 = 0;
                }
            }
        }
    }
}

void display(int num) {
    switch(num) {
        case 0:
            gpio_set_level(a, 1);
            gpio_set_level(b, 1);
            gpio_set_level(c, 1);
            gpio_set_level(d, 1);
            gpio_set_level(e, 1);
            gpio_set_level(f, 1);
            gpio_set_level(g, 0);
            break;
        case 1:
            gpio_set_level(a, 0);
            gpio_set_level(b, 1);
            gpio_set_level(c, 1);
            gpio_set_level(d, 0);
            gpio_set_level(e, 0);
            gpio_set_level(f, 0);
            gpio_set_level(g, 0);
            break;
        case 2:
            gpio_set_level(a, 1);
            gpio_set_level(b, 1);
            gpio_set_level(c, 0);
            gpio_set_level(d, 1);
            gpio_set_level(e, 1);
            gpio_set_level(f, 0);
            gpio_set_level(g, 1);
            break;
        case 3:
            gpio_set_level(a, 1);
            gpio_set_level(b, 1);
            gpio_set_level(c, 1);
            gpio_set_level(d, 1);
            gpio_set_level(e, 0);
            gpio_set_level(f, 0);
            gpio_set_level(g, 1);
            break;
        case 4:
            gpio_set_level(a, 0);
            gpio_set_level(b, 1);
            gpio_set_level(c, 1);
            gpio_set_level(d, 0);
            gpio_set_level(e, 0);
            gpio_set_level(f, 1);
            gpio_set_level(g, 1);
            break;
        case 5:
            gpio_set_level(a, 1);
            gpio_set_level(b, 0);
            gpio_set_level(c, 1);
            gpio_set_level(d, 1);
            gpio_set_level(e, 0);
            gpio_set_level(f, 1);
            gpio_set_level(g, 1);
            break;
        case 6:
            gpio_set_level(a, 1);
            gpio_set_level(b, 0);
            gpio_set_level(c, 1);
            gpio_set_level(d, 1);
            gpio_set_level(e, 1);
            gpio_set_level(f, 1);
            gpio_set_level(g, 1);
            break;
        case 7:
            gpio_set_level(a, 1);
            gpio_set_level(b, 1);
            gpio_set_level(c, 1);
            gpio_set_level(d, 0);
            gpio_set_level(e, 0);
            gpio_set_level(f, 0);
            gpio_set_level(g, 0);
            break;
        case 8:
            gpio_set_level(a, 1);
            gpio_set_level(b, 1);
            gpio_set_level(c, 1);
            gpio_set_level(d, 1);
            gpio_set_level(e, 1);
            gpio_set_level(f, 1);
            gpio_set_level(g, 1);
            break;
        case 9:
            gpio_set_level(a, 1);
            gpio_set_level(b, 1);
            gpio_set_level(c, 1);
            gpio_set_level(d, 1);
            gpio_set_level(e, 0);
            gpio_set_level(f, 1);
            gpio_set_level(g, 1);
            break;
        default:
            break;
    }
}