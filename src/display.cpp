#include <Arduino.h>
#include <LedControl.h>
#include "display.h"

// Definimos los pines del display.
const byte DIN_PIN = 11;
const byte CLK_PIN = 13;
const byte CS_PIN = 10;

// Instanciamos el controlador del display con los pines definidos.
LedControl led_control(DIN_PIN, CLK_PIN, CS_PIN, 1);

/**
 * @brief Función para iniciar el display
 */
void iniciar_display(){
    led_control.shutdown(0, false);
    led_control.setIntensity(0, 10);
    led_control.clearDisplay(0);
}

/**
 * @brief Función para dibujar la matriz en el display
 * 
 * @param matriz Matriz a dibujar
 */
void mostrar_matriz(const Matriz& matriz){
  // Recorremos cada celda de la matriz y dibujamos el estado LED correspondiente.
  for (byte fila = 0; fila < 8; fila++) {
    for (byte col = 0; col < 8; col++) {
      byte estadoLed = matriz.celdas[fila][col];
      led_control.setLed(0, fila, col, estadoLed);
    }
  }
}

