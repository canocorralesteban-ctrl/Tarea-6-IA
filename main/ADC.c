/******************************** Timer MACROS Configuration **********************************
 * @subject: Inteligencia Artificial
 * @file: ADC.c
 * @hardware: ESP32 (PANTHER48)
 * @author: Paulina Cabriales, Armando Garcia, Esteban Cano
 * @date: 17/Octubre/2026
 * @overview: Archivo de funciones para uso de ADC de la tarea 6
 *********************************************************************************************/

#include "BSP.h"
int adc_raw[NUM_POTS_2];
int X_inputs[NUM_POTS_2];

const adc_channel_t pot_channels[NUM_POTS_2] = {
    ADC_CHANNEL_0, // GPIO 36
    ADC_CHANNEL_3  // GPIO 39
};

adc_oneshot_unit_handle_t adc1_handle;

void adc_init(void) {
    //Configuración de la unidad ADC1
    adc_oneshot_unit_init_cfg_t init_config1 =  {
        .unit_id = ADC_UNIT_1,
    };
    adc_oneshot_new_unit(&init_config1, &adc1_handle);

    //Configuración de la resolución y atenuación de los canales ADC
    adc_oneshot_chan_cfg_t channel_config = {
        .bitwidth = ADC_BITWIDTH_12, // 12 bits (0 a 4095)
        .atten = ADC_ATTEN_DB_12,          
    };

    // Configuración de los 2 canales
    for (int i = 0; i < NUM_POTS_2; i++)
        adc_oneshot_config_channel(adc1_handle, pot_channels[i], &channel_config);
}

void adc_read(void) {
    for (int i = 0; i < NUM_POTS_2; i++)
        adc_oneshot_read(adc1_handle, pot_channels[i], &adc_raw[i]);
}

void adc_to_binary(void) {
    for (int i = 0; i < NUM_POTS_2; i++) {
        if (adc_raw[i] > UMBRAL_ADC)
            X_inputs[i] = 1; // Superó el umbral
        else
            X_inputs[i] = 0; // Está por debajo del umbral
    }
}