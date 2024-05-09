#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"

// Button Controls
#define ButForward 13
#define GPIO_BUTF_PIN_SEL (1ULL << ButForward)
#define ButBackward 12
#define GPIO_BUTB_PIN_SEL (1ULL << ButBackward)
#define ButLeft 14
#define GPIO_BUTL_PIN_SEL (1ULL << ButLeft)
#define ButRight 27 
#define GPIO_BUTR_PIN_SEL (1ULL << ButRight)
#define ButStop 26
#define GPIO_BUTS_PIN_SEL (1ULL << ButStop)
#define ESP_INTR_FLAG_DEFAULT 0

// DC Motor - PWM
#define motor1Pin1 23
static ledc_channel_config_t ledc_channel_M1P1;
#define motor1Pin2 22
static ledc_channel_config_t ledc_channel_M1P2;
#define motor2Pin1 1
static ledc_channel_config_t ledc_channel_M2P1;
#define motor2Pin2 3
static ledc_channel_config_t ledc_channel_M2P2;


static void init_hw(void) {
    // Button Controls
    gpio_config_t io_conf;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = GPIO_BUTF_PIN_SEL | GPIO_BUTB_PIN_SEL | GPIO_BUTL_PIN_SEL | GPIO_BUTR_PIN_SEL | GPIO_BUTS_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);

    // PWM timer
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_10_BIT,
        .freq_hz = 1000,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    ledc_timer_config (&ledc_timer);
    
    // PWM channel 1 - Motor 1 pin 1
    ledc_channel_M1P1.channel = LEDC_CHANNEL_0;
    ledc_channel_M1P1.duty = 0;
    ledc_channel_M1P1.gpio_num = motor1Pin1;
    ledc_channel_M1P1.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_channel_M1P1.hpoint = 0;
    ledc_channel_M1P1.timer_sel = LEDC_TIMER_0;
    ledc_channel_config (&ledc_channel_M1P1);
    // PWM channel 2 - Motor 1 pin 2
    ledc_channel_M1P2.channel = LEDC_CHANNEL_1;
    ledc_channel_M1P2.duty = 0;
    ledc_channel_M1P2.gpio_num = motor1Pin2;
    ledc_channel_M1P2.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_channel_M1P2.hpoint = 0;
    ledc_channel_M1P2.timer_sel = LEDC_TIMER_0;
    ledc_channel_config (&ledc_channel_M1P2);

    // PWM channel 3 - Motor 2 pin 1
    ledc_channel_M2P1.channel = LEDC_CHANNEL_2;
    ledc_channel_M2P1.duty = 0;
    ledc_channel_M2P1.gpio_num = motor2Pin1;
    ledc_channel_M2P1.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_channel_M2P1.hpoint = 0;
    ledc_channel_M2P1.timer_sel = LEDC_TIMER_0;
    ledc_channel_config (&ledc_channel_M2P1);
    // PWM channel 4 - Motor 2 pin 2
    ledc_channel_M2P2.channel = LEDC_CHANNEL_3;
    ledc_channel_M2P2.duty = 0;
    ledc_channel_M2P2.gpio_num = motor2Pin2;
    ledc_channel_M2P2.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_channel_M2P2.hpoint = 0;
    ledc_channel_M2P2.timer_sel = LEDC_TIMER_0;
    ledc_channel_config (&ledc_channel_M2P2);
}

void app_main() {
    init_hw();
    int duty = 0;
    ledc_set_duty(ledc_channel_M1P1.speed_mode, ledc_channel_M1P1.channel, duty);
    ledc_update_duty(ledc_channel_M1P1.speed_mode, ledc_channel_M1P1.channel);
    ledc_set_duty(ledc_channel_M1P2.speed_mode, ledc_channel_M1P2.channel, duty);
    ledc_update_duty(ledc_channel_M1P2.speed_mode, ledc_channel_M1P2.channel);
    ledc_set_duty(ledc_channel_M2P1.speed_mode, ledc_channel_M2P1.channel, duty);
    ledc_update_duty(ledc_channel_M2P1.speed_mode, ledc_channel_M2P1.channel);
    ledc_set_duty(ledc_channel_M2P2.speed_mode, ledc_channel_M2P2.channel, duty);
    ledc_update_duty(ledc_channel_M2P2.speed_mode, ledc_channel_M2P2.channel);
	while(1) {
		if(gpio_get_level(ButStop)) { // Button Stop has not been pressed - pull up
            duty = 0;
            if (!gpio_get_level(ButForward)) {
                duty = 512;
                // Update Motor 1 cycle duty
                ledc_set_duty(ledc_channel_M1P1.speed_mode, ledc_channel_M1P1.channel, duty);
                ledc_update_duty(ledc_channel_M1P1.speed_mode, ledc_channel_M1P1.channel);
                ledc_set_duty(ledc_channel_M1P2.speed_mode, ledc_channel_M1P2.channel, 0);
                ledc_update_duty(ledc_channel_M1P2.speed_mode, ledc_channel_M1P2.channel);
                // Update Motor 2 cycle duty
                ledc_set_duty(ledc_channel_M2P1.speed_mode, ledc_channel_M2P1.channel, duty);
                ledc_update_duty(ledc_channel_M2P1.speed_mode, ledc_channel_M2P1.channel);
                ledc_set_duty(ledc_channel_M2P2.speed_mode, ledc_channel_M2P2.channel, 0);
                ledc_update_duty(ledc_channel_M2P2.speed_mode, ledc_channel_M2P2.channel);
                vTaskDelay(250 / portTICK_PERIOD_MS);
                // Increase duty cycle while button is pressed
                while(!gpio_get_level(ButForward) && duty < 1023 && gpio_get_level(ButStop)) {
                    duty += 25;
                    ledc_set_duty(ledc_channel_M1P1.speed_mode, ledc_channel_M1P1.channel, duty);
                    ledc_update_duty(ledc_channel_M1P1.speed_mode, ledc_channel_M1P1.channel);
                    ledc_set_duty(ledc_channel_M2P1.speed_mode, ledc_channel_M2P1.channel, duty);
                    ledc_update_duty(ledc_channel_M2P1.speed_mode, ledc_channel_M2P1.channel);
                    vTaskDelay(250 / portTICK_PERIOD_MS);
                }
            } else if (!gpio_get_level(ButBackward)) {
                duty = 512;
                // Update Motor 1 cycle duty
                ledc_set_duty(ledc_channel_M1P1.speed_mode, ledc_channel_M1P1.channel, 0);
                ledc_update_duty(ledc_channel_M1P1.speed_mode, ledc_channel_M1P1.channel);
                ledc_set_duty(ledc_channel_M1P2.speed_mode, ledc_channel_M1P2.channel, duty);
                ledc_update_duty(ledc_channel_M1P2.speed_mode, ledc_channel_M1P2.channel);
                // Update Motor 2 cycle duty
                ledc_set_duty(ledc_channel_M2P1.speed_mode, ledc_channel_M2P1.channel, 0);
                ledc_update_duty(ledc_channel_M2P1.speed_mode, ledc_channel_M2P1.channel);
                ledc_set_duty(ledc_channel_M2P2.speed_mode, ledc_channel_M2P2.channel, duty);
                ledc_update_duty(ledc_channel_M2P2.speed_mode, ledc_channel_M2P2.channel);
                vTaskDelay(250 / portTICK_PERIOD_MS);
                // Increase duty cycle while button is pressed
                while(!gpio_get_level(ButBackward) && duty < 1023 && gpio_get_level(ButStop)) {
                    duty += 25;
                    ledc_set_duty(ledc_channel_M1P2.speed_mode, ledc_channel_M1P2.channel, duty);
                    ledc_update_duty(ledc_channel_M1P2.speed_mode, ledc_channel_M1P2.channel);
                    ledc_set_duty(ledc_channel_M2P2.speed_mode, ledc_channel_M2P2.channel, duty);
                    ledc_update_duty(ledc_channel_M2P2.speed_mode, ledc_channel_M2P2.channel);
                    vTaskDelay(250 / portTICK_PERIOD_MS);
                }
            } else if (!gpio_get_level(ButLeft)) {
                duty = 512;
                // Update Motor 1 cycle duty
                ledc_set_duty(ledc_channel_M1P1.speed_mode, ledc_channel_M1P1.channel, 0);
                ledc_update_duty(ledc_channel_M1P1.speed_mode, ledc_channel_M1P1.channel);
                ledc_set_duty(ledc_channel_M1P2.speed_mode, ledc_channel_M1P2.channel, duty);
                ledc_update_duty(ledc_channel_M1P2.speed_mode, ledc_channel_M1P2.channel);
                // Update Motor 2 cycle duty
                ledc_set_duty(ledc_channel_M2P1.speed_mode, ledc_channel_M2P1.channel, duty);
                ledc_update_duty(ledc_channel_M2P1.speed_mode, ledc_channel_M2P1.channel);
                ledc_set_duty(ledc_channel_M2P2.speed_mode, ledc_channel_M2P2.channel, 0);
                ledc_update_duty(ledc_channel_M2P2.speed_mode, ledc_channel_M2P2.channel);
            } else if (!gpio_get_level(ButRight)) {
                duty = 512;
                // Update Motor 1 cycle duty
                ledc_set_duty(ledc_channel_M1P1.speed_mode, ledc_channel_M1P1.channel, duty);
                ledc_update_duty(ledc_channel_M1P1.speed_mode, ledc_channel_M1P1.channel);
                ledc_set_duty(ledc_channel_M1P2.speed_mode, ledc_channel_M1P2.channel, 0);
                ledc_update_duty(ledc_channel_M1P2.speed_mode, ledc_channel_M1P2.channel);
                // Update Motor 2 cycle duty
                ledc_set_duty(ledc_channel_M2P1.speed_mode, ledc_channel_M2P1.channel, 0);
                ledc_update_duty(ledc_channel_M2P1.speed_mode, ledc_channel_M2P1.channel);
                ledc_set_duty(ledc_channel_M2P2.speed_mode, ledc_channel_M2P2.channel, duty);
                ledc_update_duty(ledc_channel_M2P2.speed_mode, ledc_channel_M2P2.channel);
            } 
        } else {
            // Stop the motors
            duty = 0;
            ledc_set_duty(ledc_channel_M1P1.speed_mode, ledc_channel_M1P1.channel, 0);
            ledc_update_duty(ledc_channel_M1P1.speed_mode, ledc_channel_M1P1.channel);
            ledc_set_duty(ledc_channel_M1P2.speed_mode, ledc_channel_M1P2.channel, 0);
            ledc_update_duty(ledc_channel_M1P2.speed_mode, ledc_channel_M1P2.channel);
            ledc_set_duty(ledc_channel_M2P1.speed_mode, ledc_channel_M2P1.channel, 0);
            ledc_update_duty(ledc_channel_M2P1.speed_mode, ledc_channel_M2P1.channel);
            ledc_set_duty(ledc_channel_M2P2.speed_mode, ledc_channel_M2P2.channel, 0);
            ledc_update_duty(ledc_channel_M2P2.speed_mode, ledc_channel_M2P2.channel);
        }
		vTaskDelay(200 / portTICK_PERIOD_MS);
	}
}