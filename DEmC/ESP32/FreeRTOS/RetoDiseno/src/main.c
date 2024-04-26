#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"

// Start Button
#define GPIO_BUT1 33
#define GPIO_BUT1_PIN_SEL (1ULL << GPIO_BUT1)
#define ESP_INTR_FLAG_DEFAULT 0
// End Button
#define GPIO_BUT2 32
#define GPIO_BUT2_PIN_SEL (1ULL << GPIO_BUT2)
#define ESP_INTR_FLAG_DEFAULT 0
// Stop1 Button
#define GPIO_BUT3 4
#define GPIO_BUT3_PIN_SEL (1ULL << GPIO_BUT3)
#define ESP_INTR_FLAG_DEFAULT 0
// Stop2 Button
#define GPIO_BUT4 2
#define GPIO_BUT4_PIN_SEL (1ULL << GPIO_BUT4)
#define ESP_INTR_FLAG_DEFAULT 0

// Step Motor1
#define GPIO_STEPa1 14
#define GPIO_STEPa1_PIN_SEL (1ULL << GPIO_STEPa1)
#define GPIO_STEPa2 27
#define GPIO_STEPa2_PIN_SEL (1ULL << GPIO_STEPa2)
// Step Motor2
#define GPIO_STEPb1 26
#define GPIO_STEPb1_PIN_SEL (1ULL << GPIO_STEPb1)
#define GPIO_STEPb2 25
#define GPIO_STEPb2_PIN_SEL (1ULL << GPIO_STEPb2)

// Frequency Potenciometer
#define SAMPLE_CNT 32 // Sample size
static const adc1_channel_t adc_channelF = ADC_CHANNEL_6; // ADC channel

// Pressure Sensor
#define SAMPLE_CNT 32 // Sample size
static const adc2_channel_t adc_channelP = ADC_CHANNEL_5; // ADC channel

static void step_left(void){
    static int stepl = 0;
    switch(stepl){
        case 0:
            gpio_set_level(GPIO_STEPa1, 1);
            gpio_set_level(GPIO_STEPa2, 0);
            gpio_set_level(GPIO_STEPb1, 1);
            gpio_set_level(GPIO_STEPb2, 0);
            stepl++;
            break;
        case 1:
            gpio_set_level(GPIO_STEPa1, 1);
            gpio_set_level(GPIO_STEPa2, 0);
            gpio_set_level(GPIO_STEPb1, 0);
            gpio_set_level(GPIO_STEPb2, 1);
            stepl++;
            break;
        case 2:
            gpio_set_level(GPIO_STEPa1, 0);
            gpio_set_level(GPIO_STEPa2, 1);
            gpio_set_level(GPIO_STEPb1, 0);
            gpio_set_level(GPIO_STEPb2, 1);
            stepl++;
            break;
        case 3:
            gpio_set_level(GPIO_STEPa1, 0);
            gpio_set_level(GPIO_STEPa2, 1);
            gpio_set_level(GPIO_STEPb1, 1);
            gpio_set_level(GPIO_STEPb2, 0);
            stepl = 0;
            break;
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
    gpio_set_level(GPIO_STEPa1, 0);
    gpio_set_level(GPIO_STEPa2, 0);
    gpio_set_level(GPIO_STEPb1, 0);
    gpio_set_level(GPIO_STEPb2, 0);
    vTaskDelay(100 / portTICK_PERIOD_MS);
}
static void step_right(void){
    static int stepr = 0;
    switch(stepr){
        case 0:
            gpio_set_level(GPIO_STEPa1, 0);
            gpio_set_level(GPIO_STEPa2, 1);
            gpio_set_level(GPIO_STEPb1, 1);
            gpio_set_level(GPIO_STEPb2, 0);
            stepr++;
            break;
        case 1:
            gpio_set_level(GPIO_STEPa1, 0);
            gpio_set_level(GPIO_STEPa2, 1);
            gpio_set_level(GPIO_STEPb1, 0);
            gpio_set_level(GPIO_STEPb2, 1);
            stepr++;
            break;
        case 2:
            gpio_set_level(GPIO_STEPa1, 1);
            gpio_set_level(GPIO_STEPa2, 0);
            gpio_set_level(GPIO_STEPb1, 0);
            gpio_set_level(GPIO_STEPb2, 1);
            stepr++;
            break;
        case 3:
            gpio_set_level(GPIO_STEPa1, 1);
            gpio_set_level(GPIO_STEPa2, 0);
            gpio_set_level(GPIO_STEPb1, 1);
            gpio_set_level(GPIO_STEPb2, 0);
            stepr = 0;
            break;
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
    gpio_set_level(GPIO_STEPa1, 0);
    gpio_set_level(GPIO_STEPa2, 0);
    gpio_set_level(GPIO_STEPb1, 0);
    gpio_set_level(GPIO_STEPb2, 0);
    vTaskDelay(100 / portTICK_PERIOD_MS);

}

static void init_hw(void) {
    gpio_config_t io_conf;

    // Start Button
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = GPIO_BUT1_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 1;
    gpio_config(&io_conf);
    // End Button
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = GPIO_BUT2_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 1;
    gpio_config(&io_conf);
    // Stop1 Button
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = GPIO_BUT3_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 1;
    gpio_config(&io_conf);
    // Stop2 Button
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = GPIO_BUT4_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 1;
    gpio_config(&io_conf);

    // Step Motor1
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_STEPa1_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_STEPa2_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    // Step Motor2
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_STEPb1_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_STEPb2_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

	// Frequency Potenciometer
    adc1_config_width(ADC_WIDTH_BIT_10);
    adc1_config_channel_atten(adc_channelF, ADC_ATTEN_DB_11);
    // Pressure Sensor
    adc2_config_width(ADC_WIDTH_BIT_10);
    adc2_config_channel_atten(adc_channelP, ADC_ATTEN_DB_11);
}

void app_main() {
	init_hw();
	while(1){
        if(gpio_get_level(GPIO_BUT1) == 1){
            while(1){
                uint32_t adc_val_pot = 0;
                for(int i = 0; i < SAMPLE_CNT; i++) {
                    adc_val_pot += adc1_get_raw(adc_channelF);
                }
                adc_val_pot /= SAMPLE_CNT;

                for(int i = 0; i < 200; i++){
                    if(gpio_get_level(GPIO_BUT2) == 1){
                        break;
                    } else if(gpio_get_level(GPIO_BUT3) == 1){
                        break;
                    } else if(gpio_get_level(GPIO_BUT4) == 1){
                        break;
                    }
                    step_left();
                    vTaskDelay(adc_val_pot / portTICK_PERIOD_MS);
                }
                for(int i = 0; i < 200; i++){
                    if(gpio_get_level(GPIO_BUT2) == 1){
                        break;
                    } else if(gpio_get_level(GPIO_BUT3) == 1){
                        break;
                    } else if(gpio_get_level(GPIO_BUT4) == 1){
                        break;
                    }
                    step_right();
                    vTaskDelay(adc_val_pot / portTICK_PERIOD_MS);
                }
            }
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }
	}
}