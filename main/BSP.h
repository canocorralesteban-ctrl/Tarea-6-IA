#ifndef BSP_H
#define BSP_H

//Librerias
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_intr_alloc.h"
#include "esp_attr.h"
#include "esp32/rom/ets_sys.h"
#include <unistd.h> 
#include "driver/gpio.h"
#include "hal/gpio_types.h"
#include "esp_timer.h"
#include "esp_adc/adc_oneshot.h"

extern const char *TAG;

//Definiciones de pines
#define BOTON 18
#define LED 2           // LED de estado del sistema
#define LED_SALIDA 17    // LED de salida del XOR
#define UMBRAL_ADC 2048
#define NUM_POTS_2 2     // XOR de 2 entradas

// Variables globales compartidas en el proyecto
extern volatile bool system_ON;
extern volatile bool state_led;

extern int adc_raw[NUM_POTS_2];
extern int X_inputs[NUM_POTS_2];

extern const adc_channel_t pot_channels[NUM_POTS_2];

// Prototipos de funciones
void gpio_init(void);
bool boton_presionado(void);
void adc_init(void);
void adc_read(void);
void adc_to_binary(void);

bool escalon(double entrada);
bool xor(double x1, double x2);

#endif