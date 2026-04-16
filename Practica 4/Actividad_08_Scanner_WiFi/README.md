# Actividad 8 — Escáner de Redes WiFi

## Objetivo
El ESP32 escanea todas las redes WiFi cercanas y muestra en el Monitor Serie una tabla con el nombre, intensidad de señal, tipo de seguridad y canal de cada red. **No se conecta a ninguna red.**

## Materiales
- ESP32
- Cable USB
- Computadora con Arduino IDE instalado

---

## Pasos para ejecutar
1. Abrir `Actividad_01_Scanner_WiFi.ino` en Arduino IDE.
2. Conectar el ESP32 por USB a la computadora.
3. En el menú **Herramientas**, seleccionar:
   - Placa: `ESP32 Dev Module`
   - Puerto: el que aparece al conectar el ESP32
4. Subir el sketch con el botón **→**.
5. Abrir el Monitor Serie (**Ctrl + Shift + M**) y seleccionar **115200 baudios** abajo a la derecha.
6. Observar la tabla de redes. Se actualiza cada 10 segundos.

---

## Configuración del código
Esta actividad **no requiere modificar ningún valor** en el código. El ESP32 solo escucha señales, no emite ninguna red propia.

## ¿Interfiere con otros grupos?
No. Esta actividad es completamente pasiva. Múltiples grupos pueden ejecutarla al mismo tiempo sin ningún problema ni conflicto.

---

## Conceptos clave

| Término | Significado |
|---------|------------|
| **SSID** | Nombre visible de la red WiFi |
| **RSSI** | Intensidad de señal recibida (siempre negativo, en dBm) |
| **Canal** | Número de canal de frecuencia del WiFi (1 al 13 en 2.4 GHz) |
| **Cifrado** | Protocolo de seguridad que protege la red (WPA2, WPA3, etc.) |

### Escala de calidad de señal RSSI

| Rango | Calidad |
|-------|---------|
| -30 a -50 dBm | Excelente |
| -51 a -60 dBm | Buena |
| -61 a -70 dBm | Regular |
| -71 a -80 dBm | Débil |
| Menos de -80 dBm | Muy mala |

---

## Preguntas para registrar en el documento Word

Responde cada pregunta con lo que observaste. Puedes incluir capturas de pantalla del Monitor Serie.

1. ¿Cuántas redes WiFi detectó el ESP32 en el aula?
2. ¿Cuál es la red con mejor señal (RSSI más cercano a 0)? Anota su nombre y valor exacto.
3. ¿Cuál es la red con peor señal? Anota su nombre y valor exacto.
4. ¿Qué tipo de cifrado usa la mayoría de las redes detectadas? ¿Qué diferencia hay entre WPA2 y WPA3?
5. ¿Hay alguna red abierta (sin contraseña)? ¿Qué riesgo implica conectarse a una red abierta?
6. ¿Por qué el RSSI es siempre un número negativo? Investiga qué significa "dBm".
7. Si apagas el WiFi de tu celular y lo vuelves a encender, ¿el ESP32 lo detecta en el escaneo? ¿Por qué sí o por qué no?
8. ¿Qué es un canal WiFi? ¿Por qué hay varios canales disponibles y por qué importa cuál usa cada red?

---

## Desafío opcional
Modificar el código para que solo muestre en la tabla las redes con RSSI mayor a -70 dBm (señal aceptable o mejor). Las redes más débiles deben ignorarse.
