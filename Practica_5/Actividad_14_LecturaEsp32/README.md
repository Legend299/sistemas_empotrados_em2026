# Actividad 14 — Monitor de Temperatura y Humedad con ESP-NOW y Dashboard Web

## Objetivo
El ESP32 principal lee temperatura y humedad de un sensor DHT11 y transmite los datos en tiempo real a los ESP32 de los alumnos usando el protocolo **ESP-NOW** (comunicación directa entre ESP32, sin router ni red WiFi escolar). Cada alumno recibe los datos en su ESP32 y los visualiza en un dashboard web que se abre directamente desde la computadora de escritorio usando el cable USB del ESP32.

## Materiales

### ESP32 Principal
- ESP32
- Sensor DHT11
- Cable USB
- Computadora con Arduino IDE

### ESP32 Receptor <- El que se va a descargar
- ESP32
- Cable USB
- Computadora con Arduino IDE y navegador Chrome o Edge

---

## Arquitectura de la práctica

```
              DHT11
                │
        ┌───────▼─────────┐
        │  ESP32 Principal │ ══ ESP-NOW (radio, sin router) ══► ESP32 ──USB──► PC (Chrome)
        │                  │
        └─────────────────┘
```

El ESP32 Receptor recibe el paquete ESP-NOW y lo reenvía por **Serial USB** a la PC. El archivo `dashboard.html` se abre en Chrome o Edge y lee el puerto USB directamente con la **Web Serial API**, sin instalar ningún programa adicional.

---

## Estructura de archivos

```
Actividad_14_LecturaEsp32/
├── ESP32_Receptor.ino   ← Código del ESP32 Receptor
├── dashboard.html                  ← Dashboard que se ejecuta en Chrome/Edge
└── ESP32_Principal/
    └── ESP32_Principal.ino         ← Código del ESP32 principal
```

---

## Conexión del sensor DHT11 (solo para el ESP32 Principal)

| DHT11 | ESP32 |
|-------|-------|
| VCC   | 3.3V  |
| GND   | GND   |
| DATA  | GPIO 4 |

El ESP32 Receptor **no necesita sensores**, solo el cable USB a la PC.

---

## Librerías necesarias

Instalar desde **Arduino IDE → Herramientas → Gestionar librerías**:

| Librería | Para quién |
|---|---|
| `DHT sensor library` (Adafruit) | ESP32 Principal |
| `Adafruit Unified Sensor` (Adafruit) | ESP32 Principal |

El código del ESP32 Receptor no requiere librerías adicionales. `esp_now.h` y `WiFi.h` ya vienen incluidas con el paquete ESP32 de Arduino.

---

## Pasos para ejecutar

### ESP32 Principal
1. Abrir `ESP32_Principal/ESP32_Principal.ino` en Arduino IDE.
2. Seleccionar la placa ESP32 y el puerto correspondiente.
3. Subir el sketch al ESP32 con el botón **→**.
4. Conectar el DHT11 al GPIO 4.
5. Verificar en el Monitor Serie a **115200 baudios** que aparezcan lecturas:
   ```
   Mac Address: XX:XX:XX:XX:XX:XX
   Transmitiendo cada 2 segundos
   Temp: 27.3 °C  |  Humedad: 21.0 %
   Envío de datos a: CORRECTO
   ```

### ESP32 Receptor
1. Abrir `Actividad_14_LecturaEsp32.ino` en Arduino IDE.
2. Seleccionar la placa ESP32 y el puerto correspondiente.
3. Subir el sketch al ESP32 con el botón **→**.
4. **Cerrar el Monitor Serie** si está abierto.
5. Abrir el archivo `dashboard.html` en **Google Chrome o Microsoft Edge**.
6. Hacer clic en el botón **"Conectar ESP32"**.
7. Seleccionar el puerto COM del ESP32 en el cuadro de diálogo.
8. Observar los datos del sensor en tiempo real.

---

## Conceptos clave

| Término | Significado |
|---------|-------------|
| **ESP-NOW** | Protocolo de Espressif para comunicación directa entre ESP32 sin necesitar un router. Funciona sobre el radio WiFi 2.4 GHz. |
| **Broadcast** | Envío de un paquete a todos los dispositivos en el radio, sin especificar destinatario. Dirección `FF:FF:FF:FF:FF:FF`. |
| **Web Serial API** | Función de Chrome/Edge que permite leer puertos USB desde JavaScript sin instalar drivers adicionales. |
| **JSON** | Formato de texto para intercambiar datos. Ejemplo: `{"t":25.3,"h":60.1}` |
| **Principal / Receptor** | Arquitectura donde un dispositivo genera datos y otros los reciben. También llamado productor/consumidor. |

### Alcance de ESP-NOW

| Escenario | Distancia aproximada |
|-----------|---------------------|
| Salón de clases (con obstáculos) | 30 – 50 m |
| Pasillo interior | 50 – 100 m |
| Campo abierto | hasta 200 m |

---