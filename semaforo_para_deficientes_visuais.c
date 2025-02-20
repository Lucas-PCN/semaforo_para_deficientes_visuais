#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "hardware/gpio.h"

#define BUZZER_PIN 9
#define LED_GREEN_PEDESTRIAN 10
#define LED_GREEN 11
#define LED_YELLOW 12
#define LED_RED 13
#define BUTTON_PIN 28
#define BUZZER_FREQUENCY 1500

void traffic_light_cycle();

void init_hardware() {
    uint leds[] = {LED_GREEN, LED_YELLOW, LED_RED, LED_GREEN_PEDESTRIAN};
    for (int i = 0; i < 4; i++) {
        gpio_init(leds[i]);
        gpio_set_dir(leds[i], GPIO_OUT);
    }
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
}

void pwm_init_buzzer() {
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (BUZZER_FREQUENCY * 4096));
    pwm_init(slice_num, &config, true);
    pwm_set_gpio_level(BUZZER_PIN, 0);
}

void update_states(bool green, bool yellow, bool red, bool pedestrian) {
    gpio_put(LED_GREEN, green);
    gpio_put(LED_YELLOW, yellow);
    gpio_put(LED_RED, red);
    gpio_put(LED_GREEN_PEDESTRIAN, pedestrian);
}

void beep(uint pin, uint duration_ms) {
    uint slice_num = pwm_gpio_to_slice_num(pin); // Obter o slice do PWM associado ao pino
    pwm_set_gpio_level(pin, 1024); // Configurar o duty cycle para 50% (ativo)
    sleep_ms(duration_ms); // Temporização
    update_states(false, false, true, true);
    pwm_set_gpio_level(pin, 0); // Desativar o sinal PWM (duty cycle 0)
    update_states(false, false, true, false);
    sleep_ms(100); // Temporização
}

int button_pressed(int time_ms) {
    for (int time = 0; time < time_ms; time += 100) {
        if (gpio_get(BUTTON_PIN) == 0) {
            return 1;
        }
        sleep_ms(100);
    }
    return 0;
}

void pedestrian_cycle(bool with_yellow) {
    update_states(false, false, false, false);

    if (with_yellow) {
      update_states(false, true, false, false);
      sleep_ms(5000);
   }

    update_states(false, false, true, true); // Vermelho e pedestre

    beep(BUZZER_PIN, 15000);
    traffic_light_cycle();
}

void traffic_light_cycle() {
    while (true) {        
        update_states(true, false, false, false);
        if (button_pressed(8000)) {
            pedestrian_cycle(true);     
        }

        update_states(false, true, false, false);
        if (button_pressed(2000)) {
            pedestrian_cycle(true);  
        }

        update_states(false, false, true, false);
        if (button_pressed(10000)) {
            pedestrian_cycle(false);
        }
    }
}

int main() {
    stdio_init_all();
    init_hardware();
    pwm_init_buzzer();
    traffic_light_cycle();
    return 0;
}