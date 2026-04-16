# Actividad 13 — Chat TCP por WiFi

## Objetivo
El ESP32 crea su propia red WiFi y un servidor TCP en el puerto 8080. Desde un celular conectado a esa red, se pueden enviar mensajes de texto usando una app de terminal TCP y el ESP32 responde según un protocolo de comandos predefinido.

## Materiales
- ESP32
- Cable USB
- Computadora con Arduino IDE
- Celular con una app de terminal TCP instalada

### Apps recomendadas (gratuitas)

| App | Sistema | Dónde conseguirla |
|-----|---------|-------------------|
| Serial WiFi Terminal | Android | Play Store |
| TCP Terminal | Android | Play Store |
| TCP Tool | iOS | App Store |

---

## Configuración de red — LEER ANTES DE SUBIR EL SKETCH

### El problema de usar el mismo SSID en clase

Si varios grupos usan el mismo nombre de red, el celular puede conectarse al ESP32 equivocado. En ese caso:

- Los mensajes enviados desde la app van al ESP32 de otro grupo.
- El Monitor Serie del ESP32 propio no muestra ningún mensaje recibido.
- El ESP32 ajeno responderá a los comandos, controlando su propio LED.

### Solución: modificar el SSID antes de subir

```cpp
const char* SSID     = "ESP32-Chat";  // ← CAMBIAR por un nombre único de grupo
const char* PASSWORD = "chat1234";    // ← CAMBIAR si quieres (mín. 8 caracteres)
const int   PUERTO   = 8080;          // ← Puede quedar igual (no hay conflicto entre redes distintas)
```

**Ejemplos de SSID únicos:**
- `"Chat-Grupo1"`
- `"TCP-Juan-2B"`
- `"ESP32TCP-Ana"`

### ¿Hay conflicto si dos grupos usan el mismo puerto 8080?
**No.** Cada grupo tiene su propia red WiFi separada. El puerto 8080 del ESP32 del Grupo 1 es completamente independiente del puerto 8080 del ESP32 del Grupo 2, porque están en redes distintas. Solo habría conflicto si dos servidores compartieran la misma red y la misma IP.

### Datos de conexión para la app del celular

| Campo | Valor |
|-------|-------|
| IP del ESP32 | `192.168.4.1` |
| Puerto | `8080` |

---

## Comandos disponibles

| Comando a enviar | Respuesta del ESP32 |
|-----------------|---------------------|
| `hola` | Saludo de bienvenida |
| `led on` | Enciende el LED del ESP32 |
| `led off` | Apaga el LED del ESP32 |
| `estado` | Informa si el LED está encendido o apagado |
| `tiempo` | Cuántos minutos y segundos lleva funcionando |
| `ping` | Responde `pong` |
| (cualquier otro texto) | Lo repite como eco |

---

## Pasos para ejecutar
1. Modificar `SSID` con el nombre único de tu grupo en el código.
2. Subir el sketch al ESP32.
3. Abrir el Monitor Serie a **115200 baudios**.
4. En el celular, conectarse a la red WiFi del ESP32.
5. Abrir la app de terminal TCP y configurarla:
   - **IP:** `192.168.4.1`
   - **Puerto:** `8080`
6. Presionar **Conectar** en la app.
7. Enviar los comandos de la tabla de arriba y observar las respuestas.
8. Comparar lo que muestra la app del celular con lo que aparece en el Monitor Serie del ESP32.

---

## Preguntas para registrar en el documento Word

Responde cada pregunta con lo que observaste. Incluye capturas de la app TCP y del Monitor Serie.

1. ¿Qué diferencia hay entre el protocolo **TCP** y el protocolo **HTTP**? ¿Por qué esta actividad no usa un navegador web?
2. ¿Qué pasa si mandas un comando que no existe, por ejemplo `apagar`? ¿Por qué el ESP32 responde de esa manera?
3. ¿Qué ocurre en el Monitor Serie del ESP32 cuando el celular cierra la app o se desconecta?
4. ¿Puedes conectar dos celulares al mismo tiempo al servidor TCP? Pruébalo. ¿Qué pasa con el segundo celular mientras el primero está conectado?
5. ¿Qué es un puerto de red? ¿Por qué se usa el 8080 en lugar del 80 (que usaban las actividades anteriores)?
6. Si dos grupos usan el mismo número de puerto (8080) pero distinto SSID, ¿se interfieren? Justifica la respuesta.
7. ¿Qué es un **protocolo de comunicación**? ¿El sistema de comandos que programamos en el ESP32 sigue un protocolo? ¿Cuáles son sus reglas?
8. ¿Qué ventaja tiene el control por TCP (texto plano) frente al control por HTTP con navegador de la Actividad 4? ¿Y qué desventaja?

---

## Desafío opcional
Agregar un comando `ayuda` que responda con la lista completa de todos los comandos disponibles y su descripción, en una sola respuesta de texto.
