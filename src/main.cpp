/**
 * Juego de la vida de Conway en un Arduino Nano con matriz LED MAX7219 de 8x8.
 * La matriz aleatoria avanza cada segundo y el botón genera una nueva.
 * Publicado en: https://thenerdyapprentice.blogspot.com/
 */

#include <Arduino.h>
#include "logica.h"
#include "display.h"

// Estado actual del juego.
Matriz matriz_actual;
int generacion;

// Control del intervalo entre generaciones.
const unsigned long intervalo = 1000;
unsigned long tiempo_anterior = 0;

// Configuración y estado del botón para filtrar pulsaciones repetidas por rebote.
const unsigned long debounce_push = 300;
unsigned long tiempo_ultimo_push = 0;
const byte PUSH_BUTTON = 2;
volatile bool boton_pulsado = false; // Se modifica en la interrupción y se consulta en loop().

void pulsacion_boton()
{
  boton_pulsado = true;
}

void setup()
{
  Serial.begin(9600);
  pinMode(PUSH_BUTTON, INPUT_PULLUP); // Activa la resistencia pull-up interna: el pin queda en HIGH y pasa a LOW al pulsar.
  attachInterrupt(digitalPinToInterrupt(PUSH_BUTTON), pulsacion_boton, FALLING);
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
  // La interrupción marca la pulsación; loop() la acepta si pasó el tiempo de debounce.
  if (boton_pulsado)
  {
    boton_pulsado = false;
    unsigned long tiempo_push_actual = millis();
    if (tiempo_push_actual - tiempo_ultimo_push >= debounce_push)
    {
      tiempo_ultimo_push = tiempo_push_actual;
      matriz_actual = generar_matriz();
      generacion = 0;
      tiempo_anterior = millis();
      mostrar_matriz(matriz_actual);
      Serial.println("Nueva matriz generada");
      return;
    }
  }

  unsigned long tiempo_actual = millis();

  // Avanza una generación cuando vence el intervalo.
  if (tiempo_actual - tiempo_anterior >= intervalo)
  {
    tiempo_anterior = tiempo_actual;
    matriz_actual = siguiente_generacion(matriz_actual);
    generacion++;
    mostrar_matriz(matriz_actual);
    Serial.print("Generación: ");
    Serial.println(generacion);
  }
}
