#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "driver/adc.h"

// Potenciometer Speed control - ADC
#define SAMPLE_CNT 32
static const adc1_channel_t adc_channel = ADC_CHANNEL_6;

// DC Motor - PWM
#define motorPin1 27
static ledc_channel_config_t ledc_channel1;
#define motorPin2 26
static ledc_channel_config_t ledc_channel2;


static void init_hw(void) {
    // ADC
    adc1_config_width(ADC_WIDTH_BIT_10);
    adc1_config_channel_atten(adc_channel, ADC_ATTEN_DB_11);
    
    // PWM timer
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_10_BIT,
        .freq_hz = 1000,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    ledc_timer_config (&ledc_timer);
    
    // PWM channel 1 - Motor 1
    ledc_channel1.channel = LEDC_CHANNEL_0;
    ledc_channel1.duty = 0;
    ledc_channel1.gpio_num = motorPin1;
    ledc_channel1.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_channel1.hpoint = 0;
    ledc_channel1.timer_sel = LEDC_TIMER_0;
    ledc_channel_config (&ledc_channel1);

    // PWM channel 2 - Motor 2
    ledc_channel2.channel = LEDC_CHANNEL_1;
    ledc_channel2.duty = 0;
    ledc_channel2.gpio_num = motorPin2;
    ledc_channel2.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_channel2.hpoint = 0;
    ledc_channel2.timer_sel = LEDC_TIMER_0;
    ledc_channel_config (&ledc_channel2);
}

void app_main() {
    init_hw();
	while(1){
		uint32_t adc_val = 0;
		for(int i = 0; i < SAMPLE_CNT; i++) {
			adc_val += adc1_get_raw(adc_channel);
		}
		adc_val /= SAMPLE_CNT;
		
		ledc_set_duty(ledc_channel1.speed_mode, ledc_channel1.channel, adc_val);
		ledc_update_duty(ledc_channel1.speed_mode, ledc_channel1.channel);
        ledc_set_duty(ledc_channel2.speed_mode, ledc_channel2.channel, adc_val);
        ledc_update_duty(ledc_channel2.speed_mode, ledc_channel2.channel);
		vTaskDelay(100 / portTICK_PERIOD_MS);
	}
}