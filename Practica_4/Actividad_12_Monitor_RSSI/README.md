# Actividad 12 — Monitor de Señal WiFi (RSSI en tiempo real)

## Objetivo
El ESP32 escanea continuamente las redes WiFi cercanas y muestra la intensidad de señal (RSSI) con un gráfico de barras ASCII en el Monitor Serie. No se conecta a ninguna red. Se puede usar el celular como fuente de señal y moverlo a distintas distancias para observar cómo varía el RSSI.

## Materiales
- ESP32
- Cable USB
- Computadora con Arduino IDE
- (Opcional) Celular con WiFi activado para observar cómo cambia el RSSI con la distancia

---

## Configuración del código
Esta actividad **no requiere modificar ningún valor** en el código. El ESP32 solo escanea señales, no emite ninguna red propia.

## ¿Interfiere con otros grupos?
**No.** Esta actividad es completamente pasiva: el ESP32 solo recibe señales de radio y no transmite nada. Múltiples grupos pueden ejecutarla al mismo tiempo sin ningún conflicto.

---

## Conceptos clave

### ¿Qué es el RSSI?
RSSI (Received Signal Strength Indicator) es la intensidad de la señal WiFi recibida, medida en **dBm** (decibeles-miliwatt). Es siempre un número negativo porque representa la potencia de la señal comparada con 1 mW de referencia: ninguna señal real en WiFi alcanza ese nivel de potencia.

| Valor RSSI | Calidad de señal | Uso típico |
|-----------|-----------------|-----------|
| -30 dBm | Excelente | Muy cerca de la fuente |
| -60 dBm | Buena | Uso normal fluido |
| -70 dBm | Regular | Aceptable con posibles demoras |
| -80 dBm | Débil | Conexión inestable |
| -90 dBm o menos | Muy mala | Posibles desconexiones frecuentes |

### ¿Por qué el RSSI es siempre negativo?
Se mide en escala logarítmica relativa a 1 mW de potencia. Cualquier señal WiFi real tiene una potencia muchísimo menor a 1 mW, lo que en escala logarítmica resulta en valores negativos. Cuanto más negativo, más débil es la señal.

---

## Pasos para ejecutar
1. Abrir el sketch en Arduino IDE y subirlo al ESP32.
2. Abrir el Monitor Serie a **115200 baudios**.
3. Observar el gráfico de barras que aparece cada 5 segundos.
4. Activar el WiFi en el celular (sin conectarse a ninguna red) para que el ESP32 lo detecte.
5. Acercar y alejar el celular del ESP32 y registrar cómo cambia el valor RSSI.

---

## Preguntas para registrar en el documento Word

Responde cada pregunta con lo que observaste. Incluye una captura del Monitor Serie con la tabla de barras.

1. ¿Cuántas redes detectó el ESP32? ¿Cuál tiene la mejor señal y cuál la peor?
2. Mide el RSSI de una misma red a tres distancias distintas (cerca, medio, lejos). Anota los valores en una tabla y explica el patrón que observas.
3. ¿Cambia el RSSI si pones la mano entre el celular y el ESP32? ¿Por qué? ¿Qué material del cuerpo humano afecta la señal?
4. ¿Por qué el RSSI es siempre negativo? Explicá con tus palabras qué significa dBm.
5. Si dos grupos ejecutan esta actividad al mismo tiempo con sus ESP32, ¿se interfieren entre sí? ¿Por qué?
6. ¿Qué relación hay entre el valor de RSSI y la calidad de una videollamada o streaming por WiFi?
7. ¿Qué materiales o barreras físicas crees que bloquean más la señal WiFi (paredes, vidrio, metal)? ¿Cómo podrías comprobarlo con este setup?
8. Las barras del gráfico van de 0 a 5 de forma lineal, pero el RSSI varía en escala logarítmica. ¿Qué implicancia tiene esa diferencia para la representación visual?

---

## Desafío opcional
Modificar el código para que registre el RSSI mínimo y máximo detectado durante toda la sesión y los muestre al final de cada escaneo, debajo de la tabla.
