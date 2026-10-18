/******************************** Timer MACROS Configuration **********************************
 * @subject: Inteligencia Artificial
 * @file: main.c
 * @hardware: ESP32 (PANTHER48)
 * @author: Paulina Cabriales, Armando Garcia, Esteban Cano
 * @date: 17/Octubre/2026
 * @overview: MLP para XOR de 2 entradas con 2 potenciometros (tarea 6)
 *********************************************************************************************/

#include "BSP.h"

// Variables globales declaradas en BSP.h (aqui se definen)
volatile bool system_ON = false;
volatile bool state_led = false;

// Pesos de la red (REEMPLAZAR por los del notebook cuando los tengan)
double w01 = -7.3870172501;
double w11 = 15.9740314484;
double w12 = 15.4625444412;
double w02 = -22.9216899872;
double w21 = 15.1479005814;
double w22 = 15.1510715485;
double w03 = -8.5453147888;
double v1  = 17.0284881592;
double v2  = -16.7011604309;

// Funcion escalon con umbral cero
int escalon(double entrada_neta) {
    if (entrada_neta >= 0.0)
        return 1;
    else
        return 0;
}

// Red XOR: calcula las 3 neuronas, imprime y regresa la salida
int red_xor(double x1, double x2) {
    double u1, u2, u3;
    int h1, h2, salida;

    // Neurona oculta 1 (OR)
    u1 = w01 + w11*x1 + w12*x2;
    h1 = escalon(u1);

    // Neurona oculta 2 (AND)
    u2 = w02 + w21*x1 + w22*x2;
    h2 = escalon(u2);

    // Neurona de salida
    u3 = w03 + v1*h1 + v2*h2;
    salida = escalon(u3);

    printf("Entrada: [%.0f %.0f] | u1: %8.4f h1: %d | u2: %8.4f h2: %d | u3: %8.4f | Salida: %d\n",
           x1, x2, u1, h1, u2, h2, u3, salida);

    return salida;
}

void app_main(void) {
    int contador = 0;   // cuenta ciclos de 10 ms
    int salida;

    gpio_init();
    adc_init();

    while (true) {
        // Boton: alterna entre OFF y RUN
        if (boton_presionado()) {
            system_ON = !system_ON;
            gpio_set_level(LED, system_ON);
            if (!system_ON)
                gpio_set_level(LED_SALIDA, 0);   // apaga el LED de salida al parar
            contador = 0;
        }

        // En RUN, cada 200 ms (20 ciclos de 10 ms) evalua la red
        if (system_ON) {
            contador++;
            if (contador >= 20) {
                contador = 0;
                adc_read();         // lee los 2 potenciometros
                adc_to_binary();    // los convierte a 0/1 con el umbral 2048
                salida = red_xor(X_inputs[0], X_inputs[1]);
                gpio_set_level(LED_SALIDA, salida);
            }
        }

        vTaskDelay(pdMS_TO_TICKS(10));   // 10 ms: sirve de debounce del boton
    }
}