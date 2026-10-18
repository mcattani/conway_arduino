#pragma once

#include <Arduino.h>

struct Matriz
{
    byte celdas[8][8];
};

Matriz generar_matriz();
Matriz siguiente_generacion(const Matriz &matriz);
