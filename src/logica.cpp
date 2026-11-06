#include "logica.h"

struct Direccion
{
    int fila;
    int columna;
};

// Definimos las direcciones de las células vecinas.
const Direccion direcciones[8] = {
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, -1},
    {0, 1},
    {1, -1},
    {1, 0},
    {1, 1}};

/**
 * @brief Función que genera una matriz aleatoria de 8x8
 *
 * @return una matriz con valores aleatorios de 0 y 1
 */
Matriz generar_matriz()
{
    Matriz matriz;

    for (byte i = 0; i < 8; i++)
    {
        for (byte j = 0; j < 8; j++)
        {
            matriz.celdas[i][j] = random(2);
        }
    }
    return matriz;
}

/**
 * @brief Función que determina la cantidad de vecinos vivos de una célula
 *
 * @param matriz Matriz de la que se calcula el contador de vecinos vivos
 * @param fila Fila de la célula
 * @param columna Columna de la célula
 * @return byte Devuelve el número de vecinos vivos de la célula
 */
byte contar_vecinos_vivos(const Matriz &matriz, byte fila, byte columna)
{
    byte contador = 0;
    for (Direccion direccion : direcciones)
    {
        int filaVecino = fila + direccion.fila;
        int columnaVecino = columna + direccion.columna;
        // Verificamos que la célula vecina esté dentro de la matriz
        if (filaVecino < 0 || filaVecino >= 8 || columnaVecino < 0 || columnaVecino >= 8)
        {
            continue;
        }
        if (matriz.celdas[filaVecino][columnaVecino] == 1)
        {
            contador++;
        }
    }
    return contador;
}

/**
 * @brief Función que determina el siguiente estado de una célula a partir de su estado actual y el número de vecinos vivos
 *
 * @param estado_actual Estado actual de la célula
 * @param vecinos_vivos Cantidad de vecinos vivos de la célula
 * @return byte Devuelve el siguiente estado de la célula
 */
byte estado_proxima_generacion(byte estado_actual, byte vecinos_vivos)
{
    if (estado_actual == 1)
    {
        // Una célula viva sobrevive con 2 o 3 vecinos vivos.
        if (vecinos_vivos == 2 || vecinos_vivos == 3)
        {
            return 1;
        }
    }
    else
    {
        // Una célula muerta revive con exactamente 3 vecinos vivos.
        if (vecinos_vivos == 3)
        {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Función que calcula el siguiente estado de una matriz
 *
 * @param matriz Matriz de la que se calcula el siguiente estado
 * @return Matriz Matriz con las reglas aplicadas
 */
Matriz siguiente_generacion(const Matriz &matriz)
{
    Matriz matriz_siguiente;

    for (byte fila = 0; fila < 8; fila++)
    {
        for (byte columna = 0; columna < 8; columna++)
        {
            byte estado_actual = matriz.celdas[fila][columna];
            byte vecinos_vivos = contar_vecinos_vivos(matriz, fila, columna);
            byte estado_siguiente = estado_proxima_generacion(estado_actual, vecinos_vivos);
            matriz_siguiente.celdas[fila][columna] = estado_siguiente;
        }
    }

    return matriz_siguiente;
}

/**
 * @brief Función que devuelve un preset para la matriz
 *
 * @return Matriz Matriz con los valores del preset
 */
Matriz generar_preset()
{
    Matriz matriz = {{{0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 1, 0, 0},
                      {0, 0, 0, 0, 0, 1, 0, 0},
                      {0, 0, 0, 0, 0, 1, 1, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 1, 1, 1, 0, 0, 1, 1},
                      {0, 0, 0, 1, 0, 1, 0, 1},
                      {0, 0, 0, 0, 0, 1, 1, 0}}};
    return matriz;
}