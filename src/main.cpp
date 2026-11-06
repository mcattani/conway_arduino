/**
 * Juego de la vida de Conway en un Arduino Nano con matriz LED MAX7219 de 8x8.
 * La matriz avanza cada 500ms; una pulsación corta genera un tablero aleatorio
 * y una pulsación larga carga el preset oscilador de tres generaciones.
 * Publicado en: https://thenerdyapprentice.blogspot.com/
 */

#include <Arduino.h>
#include "logica.h"
#include "display.h"
#include <Button2.h>

// Estado actual del juego.
Matriz matriz_actual;
int generacion;

// Control del intervalo entre generaciones.
const unsigned long intervalo = 500;
unsigned long tiempo_anterior = 0;

// Configuración del pulsador
const byte PUSH_BUTTON = 2;
Button2 pulsador;

// Variables para el pulsador (tiempos de debounce y pulsación larga)
const int debounce_push = 50;
const int long_push = 800;

/**
 * @brief Función de callback para el pulsador (pulsación corta). Crea una matriz aleatoria nueva y la muestra.
 *
 */
void pulsacion_corta(Button2 &btn)
{
  matriz_actual = generar_matriz();
  generacion = 0;
  tiempo_anterior = millis();
  mostrar_matriz(matriz_actual);
  Serial.println("Nueva matriz generada");
}

/**
 * @brief Función de callback para el pulsador (pulsación larga). Carga el preset de la matriz y la muestra.
 *
 */
void pulsacion_larga(Button2 &btn)
{
  matriz_actual = generar_preset();
  generacion = 0;
  tiempo_anterior = millis();
  mostrar_matriz(matriz_actual);
  Serial.println("Preset cargado");
}

void setup()
{
  Serial.begin(9600);

  // Configuraciones del pulsador
  pulsador.begin(PUSH_BUTTON);
  pulsador.setDebounceTime(debounce_push);
  pulsador.setLongClickTime(long_push);

  // Registramos las funciones de callback del pulsador
  pulsador.setClickHandler(pulsacion_corta);
  pulsador.setLongClickDetectedHandler(pulsacion_larga);

  randomSeed(analogRead(A0)); // Usa la lectura de A0 para inicializar la secuencia aleatoria.
  iniciar_display();

  matriz_actual = generar_matriz();
  mostrar_matriz(matriz_actual);
  generacion = 0;

  Serial.print("Generación: ");
  Serial.println(generacion);
}

void loop()
{
  pulsador.loop();
  unsigned long tiempo_actual = millis();
  if (tiempo_actual - tiempo_anterior >= intervalo)
  {
    matriz_actual = siguiente_generacion(matriz_actual);
    tiempo_anterior = tiempo_actual;
    generacion++;
    mostrar_matriz(matriz_actual);
    Serial.print("Generación: ");
    Serial.println(generacion);
  }
}
