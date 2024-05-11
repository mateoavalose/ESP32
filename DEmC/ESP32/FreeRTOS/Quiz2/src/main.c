#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"

// ADC - Potentiometer
#define SAMPLE_CNT 100  
static const adc1_channel_t adc_channel = ADC_CHANNEL_6;

// Stepper Motor - 14HS10-0404S
// Step Motor1.1
#define GPIO_STEPa1 23 // Black wire - Output 1
#define GPIO_STEPa1_PIN_SEL (1ULL << GPIO_STEPa1)
#define GPIO_STEPa2 22 // Green wire - Output 2
#define GPIO_STEPa2_PIN_SEL (1ULL << GPIO_STEPa2)
// Step Motor1.2
#define GPIO_STEPb1 1 // Red wire - Output 3
#define GPIO_STEPb1_PIN_SEL (1ULL << GPIO_STEPb1)
#define GPIO_STEPb2 3 // Blue wire - Output 4
#define GPIO_STEPb2_PIN_SEL (1ULL << GPIO_STEPb2)

// Variables
int coilPos = 0; // Position of the stepper motor coil
int stepPos = 0; // Position of the stepper motor
int potPos = 0; // Position of the potentiometer

// Functions 
static void step_left(void);
static void step_right(void);

static void init_hw() {
    // ADC
    adc1_config_width(ADC_WIDTH_BIT_10);
    adc1_config_channel_atten(adc_channel, ADC_ATTEN_DB_11);
    // GPIO
    gpio_config_t io_conf;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (GPIO_STEPa1_PIN_SEL | GPIO_STEPa2_PIN_SEL | GPIO_STEPb1_PIN_SEL | GPIO_STEPb2_PIN_SEL);
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
}

void app_main() {
    init_hw();
    while(1) {
        // Read ADC
        uint32_t adc_val = 0; 
		for(int i = 0; i < SAMPLE_CNT; i++) {
			adc_val += adc1_get_raw(adc_channel);
		}
		adc_val /= SAMPLE_CNT;
        // Convert ADC value to steps (0-100 range for half rotation)
        potPos = adc_val*(100/1023.0);
        // Move stepper motor to the potentiometer position
        while(potPos > stepPos){
            step_right();
            stepPos++;
        }
        while(potPos < stepPos){
            step_left();
            stepPos--;
        }
    }
}

static void step_left(void){
    switch(coilPos){
        case 0:
            gpio_set_level(GPIO_STEPa1, 1);
            gpio_set_level(GPIO_STEPa2, 0);
            gpio_set_level(GPIO_STEPb1, 1);
            gpio_set_level(GPIO_STEPb2, 0);
            coilPos = 1;
            break;
        case 1:
            gpio_set_level(GPIO_STEPa1, 1);
            gpio_set_level(GPIO_STEPa2, 0);
            gpio_set_level(GPIO_STEPb1, 0);
            gpio_set_level(GPIO_STEPb2, 1);
            coilPos = 2;
            break;
        case 2:
            gpio_set_level(GPIO_STEPa1, 0);
            gpio_set_level(GPIO_STEPa2, 1);
            gpio_set_level(GPIO_STEPb1, 0);
            gpio_set_level(GPIO_STEPb2, 1);
            coilPos = 3;
            break;
        case 3:
            gpio_set_level(GPIO_STEPa1, 0);
            gpio_set_level(GPIO_STEPa2, 1);
            gpio_set_level(GPIO_STEPb1, 1);
            gpio_set_level(GPIO_STEPb2, 0);
            coilPos = 0;
            break;
    }
    vTaskDelay(10 / portTICK_PERIOD_MS);
    gpio_set_level(GPIO_STEPa1, 0);
    gpio_set_level(GPIO_STEPa2, 0);
    gpio_set_level(GPIO_STEPb1, 0);
    gpio_set_level(GPIO_STEPb2, 0);
}
static void step_right(void){
    switch(coilPos){
        case 0:
            gpio_set_level(GPIO_STEPa1, 0);
            gpio_set_level(GPIO_STEPa2, 1);
            gpio_set_level(GPIO_STEPb1, 1);
            gpio_set_level(GPIO_STEPb2, 0);
            coilPos = 1;
            break;
        case 1:
            gpio_set_level(GPIO_STEPa1, 0);
            gpio_set_level(GPIO_STEPa2, 1);
            gpio_set_level(GPIO_STEPb1, 0);
            gpio_set_level(GPIO_STEPb2, 1);
            coilPos = 2;
            break;
        case 2:
            gpio_set_level(GPIO_STEPa1, 1);
            gpio_set_level(GPIO_STEPa2, 0);
            gpio_set_level(GPIO_STEPb1, 0);
            gpio_set_level(GPIO_STEPb2, 1);
            coilPos = 3;
            break;
        case 3:
            gpio_set_level(GPIO_STEPa1, 1);
            gpio_set_level(GPIO_STEPa2, 0);
            gpio_set_level(GPIO_STEPb1, 1);
            gpio_set_level(GPIO_STEPb2, 0);
            coilPos = 0;
            break;
    }
    vTaskDelay(10 / portTICK_PERIOD_MS);
    gpio_set_level(GPIO_STEPa1, 0);
    gpio_set_level(GPIO_STEPa2, 0);
    gpio_set_level(GPIO_STEPb1, 0);
    gpio_set_level(GPIO_STEPb2, 0);
}
