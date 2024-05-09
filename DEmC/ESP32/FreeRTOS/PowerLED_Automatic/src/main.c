#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"

// Light variable resistor - ADC
#define SAMPLE_CNT 50
static const adc1_channel_t adc_channel = ADC_CHANNEL_6;
// GPIO to Octocoupler and Power LED
#define GPIO_EN_LED 23
#define GPIO_EN_LED_MASK (1ULL<<GPIO_EN_LED)

static void init_hw(void) {
    // ADC
    adc1_config_width(ADC_WIDTH_BIT_10);
    adc1_config_channel_atten(adc_channel, ADC_ATTEN_DB_11);
    // GPIO
    gpio_config_t io_conf;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_EN_LED_MASK;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
}

void app_main() {
    init_hw();
    while(1) {
        uint32_t adc_val = 0;
        for(int i = 0; i < SAMPLE_CNT; i++) {
            adc_val += adc1_get_raw(adc_channel);
        }
        adc_val /= SAMPLE_CNT;
        if(adc_val > 900){
            gpio_set_level(GPIO_EN_LED, 1);
        } else {
            gpio_set_level(GPIO_EN_LED, 0);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}