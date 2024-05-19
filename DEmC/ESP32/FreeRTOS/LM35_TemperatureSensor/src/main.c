#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"

#define SAMPLE_CNT 100
static const adc1_channel_t adc_channel = ADC_CHANNEL_5;

int temp = 0;

static void init_hw(void) {
	adc1_config_width(ADC_WIDTH_BIT_12);
	adc1_config_channel_atten(adc_channel, ADC_ATTEN_DB_11);
}

void app_main() {
	init_hw();
	while(1){
		uint32_t adc_val = 0;
		for(int i = 0; i < SAMPLE_CNT; i++) {
			adc_val += adc1_get_raw(adc_channel);
		}
		adc_val /= SAMPLE_CNT;
        printf("ADC value: "); printf("%lu\n", adc_val);

        temp = adc_val*(3300 / 4095.0) / 10;
        printf("Temperature: "); printf("%d\n", temp); 
        printf("\n");
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}