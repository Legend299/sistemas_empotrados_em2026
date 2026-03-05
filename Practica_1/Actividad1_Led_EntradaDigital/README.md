# Actividad 1 — LED con entrada digital (ESP32)

Este repositorio contiene un sketch sencillo para ESP32 que enciende y apaga un LED cada segundo.

## Archivos
- `actividad1.ino` — Sketch principal (ESP32) que alterna el estado de un LED conectado a GPIO2.

## Descripción del código
El programa hace lo siguiente:

1. Define el pin donde está conectado el LED:

   const int ledPin = 2;

2. En `setup()` inicializa el pin como salida y apaga el LED al inicio:

   pinMode(ledPin, OUTPUT);
   digitalWrite(ledPin, LOW);

3. En `loop()` alterna el LED cada 1 segundo usando `digitalWrite` y `delay`:

   digitalWrite(ledPin, HIGH);
   delay(1000);
   digitalWrite(ledPin, LOW);
   delay(1000);

## Conexión (hardware)
- LED → resistor de 220Ω (Opcional) → GPIO2 (o el pin que hayas configurado)
- LED cathode → GND
- ESP32 alimentado según tu módulo (usa 5V o 3.3V según corresponda)

> Nota: algunos módulos ESP32 ya tienen un LED integrado en GPIO2, por lo que podrías ver el parpadeo sin conectar un LED externo.

## Diagrama de conexión
Imagen del diagrama de Tinkercad y el enlace al proyecto en Tinkercad:

- Imagen del diagrama: `./img/tinkercad_diagram.png`
- Enlace a Tinkercad: https://www.tinkercad.com/things/2nKtMK5MIPY-1leddigital?sharecode=pX9LFTpKYWoREUY1aIF6_ApNUSlEYM1kqun8cxmG2XQ

## Foto del montaje real

- Foto : `./img/foto_esp32_conexion.jpeg`

## Cómo subir el sketch
1. Abre Arduino IDE.
2. Selecciona la placa ESP32 (por ejemplo: "ESP32 Dev Module").
3. Selecciona el puerto serie correcto.
4. Haz clic en "Subir".