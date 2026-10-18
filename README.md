[![Arduino Nano](https://img.shields.io/badge/Arduino-Nano-00979D?logo=arduino&logoColor=white)](https://docs.arduino.cc/hardware/nano/)
[![PlatformIO](https://img.shields.io/badge/PlatformIO-IDE-orange?logo=platformio&logoColor=white)](https://platformio.org/)
[![Licencia: GPL v3](https://img.shields.io/badge/Licencia-GPLv3-blue.svg)](LICENSE)

# Juego de la Vida de Conway en Arduino

Implementación del Juego de la Vida de Conway en un Arduino Nano y una matriz LED de 8×8 controlada por MAX7219. La simulación empieza con un tablero aleatorio, actualiza una generación por segundo y permite generar un tablero nuevo con un pulsador.

Este proyecto lleva la secuencia de implementaciones de Conway desde la versión didáctica para consola hasta la interfaz gráfica con Pygame y, ahora, a un dispositivo físico:

1. [conway_writeups_cli_py](https://github.com/mcattani/conway_writeups_cli_py): cuadernos didácticos y versión CLI.
2. [conway_pygame](https://github.com/mcattani/conway_pygame): versión gráfica interactiva.
3. **conway_arduino**: simulación en Arduino Nano con una matriz LED.

## Características

- Tablero de 8×8 con estado inicial aleatorio.
- Reglas clásicas de Conway: nacimiento, supervivencia y muerte.
- Evolución automática cada segundo.
- Pulsador para generar una nueva matriz aleatoria y reiniciar el contador.
- Generación actual informada por el monitor serie a 9600 baudios.
- Bordes finitos: las celdas fuera de la matriz no se cuentan como vecinas.

## Hardware y conexiones

Componentes:

- Arduino Nano con ATmega328P.
- Módulo de matriz LED 8×8 con controlador MAX7219.
- Pulsador.
- Cables de conexión.

| Arduino | Conexión | Descripción |
| --- | --- | --- |
| D11 | MAX7219: DIN | Datos |
| D13 | MAX7219: CLK | Reloj |
| D10 | MAX7219: CS (o LOAD) | Selección del módulo |
| 5V | MAX7219: VCC | Alimentación |
| GND | MAX7219: GND y pulsador: una terminal | Tierra común |
| D2 | Pulsador  | Entrada con pull-up interna; al pulsar, D2 pasa a LOW |

El pulsador se conecta entre D2 y GND; no hace falta una resistencia pull-up externa. Comprueba las etiquetas de alimentación de tu módulo MAX7219 antes de conectarlo y comparte GND entre los componentes.

## Requisitos

- [PlatformIO](https://platformio.org/) (PlatformIO IDE o PlatformIO Core).
- Arduino Nano clásico con ATmega328P.
- Módulo MAX7219 y pulsador conectados según la tabla anterior.

La dependencia `LedControl` se declara en `platformio.ini` y PlatformIO la instala al compilar.

## Compilar, cargar y monitor serie

Clona el repositorio y abre su directorio en PlatformIO:

```bash
git clone https://github.com/mcattani/conway_arduino.git
cd conway_arduino
```

Con PlatformIO Core, ejecuta:

```bash
pio run
pio run --target upload
pio device monitor --baud 9600
```

Si hay más de un puerto serie disponible, indica el puerto de tu placa al cargar o abrir el monitor:

```bash
pio run --target upload --upload-port /dev/ttyUSB0
pio device monitor --port /dev/ttyUSB0 --baud 9600
```

En Linux, el puerto puede aparecer como `/dev/ttyUSB0` o `/dev/ttyACM0`; en otros sistemas, selecciona el puerto asignado por el sistema operativo.

Al iniciar, la matriz muestra un tablero aleatorio y el monitor serie informa `Generación: 0`. Después, el contador avanza cada segundo. Pulsa el botón para crear otro tablero aleatorio y comenzar de nuevo desde la generación cero.

## Estructura del proyecto

```text
.
├── include/
│   ├── display.h       # Interfaz para inicializar y actualizar la matriz LED
│   └── logica.h        # Tipo Matriz y funciones de evolución
├── src/
│   ├── display.cpp     # Comunicación con el controlador MAX7219
│   ├── logica.cpp      # Reglas de Conway y cálculo de vecinos
│   └── main.cpp        # Inicialización, botón y ciclo de generaciones
└── platformio.ini      # Placa, framework, monitor serie y dependencia
```

## Licencia

Este proyecto se distribuye bajo la licencia [GNU General Public License v3.0](LICENSE).

---

Desarrollado por [The Nerdy Apprentice](https://thenerdyapprentice.blogspot.com/).

[![Invítame un café en Cafecito](https://img.shields.io/badge/Cafecito-Soporte-orange?style=flat-square&logo=coffeescript&logoColor=white)](https://cafecito.app/thenerdyapprentice)
