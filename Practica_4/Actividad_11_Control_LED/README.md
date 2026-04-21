# Actividad 11 — Control de LED por WiFi desde el Navegador

## Objetivo
Controlar el LED integrado del ESP32 desde un navegador web usando botones en una página HTML. El ESP32 actúa como Access Point y servidor HTTP al mismo tiempo. Al presionar los botones, el LED físico del ESP32 se enciende o apaga en tiempo real.

## Materiales
- ESP32 (LED integrado en el **pin 2** en la mayoría de modelos)
- Cable USB
- Computadora con Arduino IDE
- Celular con navegador web

---

## Configuración de red — LEER ANTES DE SUBIR EL SKETCH

### El problema de usar el mismo SSID en clase

Si varios grupos usan el mismo nombre de red, el celular puede conectarse al ESP32 equivocado. En ese caso:

- Al presionar "Encender" en la pantalla del celular, el comando va al ESP32 de otro grupo.
- El LED del ESP32 propio no hace nada.
- El Monitor Serie del ESP32 propio no muestra ningún comando recibido.
- No hay ningún error visible, lo que hace el error difícil de detectar.

### Solución: modificar el SSID antes de subir

```cpp
const char* SSID     = "ESP32-LED";  // ← CAMBIAR por un nombre único de grupo
const char* PASSWORD = "led12345";   // ← CAMBIAR si quieres (mín. 8 caracteres)
```

**Ejemplos de SSID únicos:**
- `"LED-Grupo1"`
- `"ESP32LED-Ana"`
- `"Control-2B-Juan"`

### IP del servidor
Siempre es **`192.168.4.1`** (puerto 80). Abrir en el navegador del celular: `http://192.168.4.1`

No hay conflicto de IP entre grupos porque cada grupo tiene su propia red separada.

### ¿Por qué la contraseña debe tener mínimo 8 caracteres?
El protocolo WPA2 (que usa el ESP32) requiere un mínimo de 8 caracteres. Si se pone una contraseña más corta, `WiFi.softAP()` falla silenciosamente y la red no se crea.

---

## Pasos para ejecutar
1. Modificar `SSID` con el nombre único de tu grupo en el código.
2. Subir el sketch al ESP32.
3. Abrir el Monitor Serie a **115200 baudios**.
4. Conectar el celular a la red WiFi del ESP32.
5. Abrir en el navegador del celular: `192.168.4.1`
6. Presionar los botones **Encender** y **Apagar**.
7. Verificar que el LED físico del ESP32 responde y que el Monitor Serie registra cada comando.

---

## Preguntas para registrar en el documento Word

Responde cada pregunta con lo que observaste. Incluye capturas del navegador, del Monitor Serie y (si puedes) del LED encendido.

1. ¿Qué aparece en el Monitor Serie cada vez que presionas un botón desde el celular?
2. ¿Qué método HTTP usa el formulario de los botones: GET o POST? ¿Cómo puedes verlo en la barra de direcciones del navegador?
3. ¿Qué ves exactamente en la barra de direcciones del navegador cuando presionas "Encender"? ¿Y cuando presionas "Apagar"?
4. ¿Puedes controlar el LED desde dos celulares al mismo tiempo? Pruébalo. ¿Qué problema puede surgir?
5. Si el celular pierde la conexión WiFi mientras el LED está encendido, ¿qué le pasa al LED? ¿Por qué?
6. ¿En qué pin físico del ESP32 está conectado el LED integrado? ¿Todos los modelos de ESP32 tienen el LED en el mismo pin?
7. ¿Por qué la página deshabilita el botón que corresponde al estado actual del LED (si está encendido, deshabilita "Encender")?
8. ¿Qué concepto de **IoT (Internet de las Cosas)** se aplica en esta actividad? Busca una definición y explica la relación.

---

## Desafío opcional
Agregar un tercer botón **"Parpadear"** que haga titilar el LED 5 veces (con `delay(200)` entre encendido y apagado) antes de devolver la respuesta HTML al navegador.
