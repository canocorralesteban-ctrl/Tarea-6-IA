/******************************** Timer MACROS Configuration **********************************
 * @subject: Inteligencia Artificial
 * @file: main.c
 * @hardware: ESP32 (PANTHER48)
 * @author: Paulina Cabriales, Armando Garcia, Esteban Cano
 * @date: 17/Octubre/2026
 * @overview: MLP para XOR de 2 entradas con 2 potenciometros (tarea 6)
 *********************************************************************************************/

#include "BSP.h"

// Variables globales declaradas en BSP.h 
volatile bool system_ON = false;

volatile bool btn_state = true;
volatile bool btn_state_old;

void app_main(void) {
    
    // Variables locales
    bool salida;
    //Se inicializan los gpio y el ADC
    gpio_init();
    adc_init();

    ESP_LOGI( TAG, "preione el boton para encender/apagar el sistema" );
    while (true) {

        
        if (boton_presionado()) {
            system_ON = !system_ON;
            if(system_ON)
            {
                ESP_LOGI(TAG, "sistema activo");
                gpio_set_level(LED, system_ON);
            }
                
            if (!system_ON)
            {
                ESP_LOGI(TAG, "sistema inactivo");
                gpio_set_level(LED, system_ON);
            }
                  
        }
        btn_state_old = btn_state;
        
        if (system_ON) {
    
            adc_read();         // lee los 2 potenciometros
            adc_to_binary();    // los convierte a 0/1 con el umbral 2048
            salida = xor(X_inputs[0], X_inputs[1]);
            gpio_set_level(LED_SALIDA, salida);

            vTaskDelay(pdMS_TO_TICKS(200));
        }

        vTaskDelay(pdMS_TO_TICKS(10));   // 10 ms: sirve de debounce del boton
    }
}