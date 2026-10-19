/******************************** Timer MACROS Configuration **********************************
 * @subject: Inteligencia Artificial
 * @file: mlp.c
 * @hardware: ESP32 
 * @author: Paulina Cabriales, Armando Garcia, Esteban Cano
 * @date: 18/Octubre/2026
 * @overview: Perceptron multicapa (MLP) para XOR de 2 entradas (tarea 6)
 *********************************************************************************************/

#include "BSP.h"

// Pesos de la red 
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
bool escalon(double entrada) {
    if (entrada >= 0.0)
        return true;
    else
        return false;
}

// Red XOR: calcula las 3 neuronas, imprime pesos y regresa la salida
bool xor(double x1, double x2) {
    double u1, u2, u3;
    bool h1, h2, salida;

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