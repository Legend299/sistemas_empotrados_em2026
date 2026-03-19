# Practica 3 , Actividad 7 — Control con Arduino Esplora y visualización en ESP32

Este repositorio contiene una práctica donde un **Arduino Esplora** funciona como control y envía comandos por comunicación serial a un **ESP32**, el cual dibuja una escena sencilla tipo pseudo-3D en una pantalla **Nokia 5110**.

## Archivos
- `esp32_juego.ino` — Sketch principal del ESP32 que recibe comandos desde el Esplora y renderiza la escena en la pantalla Nokia 5110.
- `esplora_control.ino` — Sketch del Arduino Esplora que lee el joystick y botones para enviarlos como comandos al ESP32.

## Descripción del código
El programa realiza lo siguiente:

1. Incluye las librerías necesarias:
	```cpp
	#include <Adafruit_GFX.h>
	#include <Adafruit_PCD8544.h>
	#include <math.h>
	```

	Para el Arduino Esplora se utilizan:
	```cpp
	#include <Esplora.h>
	#include <SoftwareSerial.h>
	```
- ![Imagen de la libreria](./img/libreria_esplora.png "Libreria esplora.")

2. Define los pines de conexión del ESP32 con la pantalla Nokia 5110 y la recepción serial:
	```cpp
	#define PIN_RST  15
	#define PIN_CE    2
	#define PIN_DC    4
	#define PIN_DIN  23
	#define PIN_CLK  18
	#define PIN_RX2  16
	```

3. Configura un mapa del mundo de 8x8 para representar paredes y espacios libres:
	```cpp
	const char worldMap[MAP_H][MAP_W + 1] = {
	  "########",
	  "#......#",
	  "#..#...#",
	  "#......#",
	  "#..#...#",
	  "#......#",
	  "#......#",
	  "########"
	};
	```

4. En el ESP32 se inicializa la pantalla y la comunicación serial en `setup()`:
	- `Serial.begin(9600);` para depuración.
	- `Serial2.begin(9600, SERIAL_8N1, PIN_RX2, 17);` para recibir los datos enviados por el Esplora.
	- Se inicia la pantalla y se ajusta el contraste.

5. En el Arduino Esplora, el sketch lee el joystick y los botones:
	```cpp
	int x = Esplora.readJoystickX();
	int y = Esplora.readJoystickY();
	```

	Dependiendo de la dirección del joystick, manda letras al ESP32:
	- `F` = avanzar
	- `B` = retroceder
	- `L` = girar a la izquierda
	- `R` = girar a la derecha

	También envía `1`, `2`, `3` y `4` cuando se presionan los botones del Esplora.

6. En el ESP32, la función `handleCommand()` procesa esos comandos para mover al jugador o girar la vista:
	```cpp
	switch (cmd) {
	  case 'F':
	  case 'B':
	  case 'L':
	  case 'R':
	}
	```

7. La función `castRay()` genera un efecto visual tipo raycasting, donde cada columna de la pantalla representa la distancia a una pared.

- ![Imagen del proyecto](./img/castRay.png "Visualización tipo raycasting en pantalla Nokia 5110.")

8. La función `render()` actualiza toda la escena en la pantalla Nokia 5110 y dibuja también una mira al centro.

## Conexión (hardware)
- **ESP32 + Nokia 5110** conectados con los pines definidos en `esp32_juego.ino`.
- **Arduino Esplora** funcionando como control de entrada.
- Comunicación serial entre Esplora y ESP32 para enviar comandos.
- Alimentación adecuada para ambos dispositivos.

## Funcionamiento general
- El usuario mueve el joystick del Esplora.
- El Esplora manda comandos simples por serial.
- El ESP32 recibe esos comandos y actualiza la posición o dirección del jugador.
- Después vuelve a dibujar la escena en la pantalla LCD Nokia 5110.

## Imagen de montaje real
- ![Imagen del proyecto](./img/montaje_real.jpg "Imagen del montaje real de esp32 y arduino esplora.")

## Imagen del Diagrama + Url al proyecto
- ![Imagen del diagrama](./img/diagrama_formal.png "Diagrama de conexión entre ESP32 y Arduino Esplora.")

# Enlace
[Diagrama](https://app.cirkitdesigner.com/project/3cb56d7a-0161-401d-9d29-9c2fbd69803b)

## Cómo subir el sketch
1. Abre Arduino IDE.
2. Carga `esplora_control.ino` en la placa **Arduino Esplora**.
3. Carga `esp32_juego.ino` en la placa **ESP32**.
4. Verifica que ambas placas usen la misma velocidad serial (`9600`).
5. Realiza las conexiones necesarias y prueba el movimiento con el joystick.

## Ejercicios extra

1. **Agregar sonido con buzzer**
	- Conecta un buzzer pasivo o activo al ESP32.
	- Haz que haga ruido cuando se presione un botón del Esplora.

2. **Agregar LEDs de estado**
	- Conecta LEDs al ESP32 para indicar acciones del juego.
	- Ejemplo:
	  - LED verde: avanzar
	  - LED amarillo: girar
	  - LED rojo: choque con pared

3. **Modificar el mapa del escenario**
	- Cambia el contenido de `worldMap` para crear un laberinto diferente.
	- Prueba distintas distribuciones de paredes y espacios libres.
