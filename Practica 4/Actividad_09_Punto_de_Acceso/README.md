# Actividad 9 — ESP32 como Punto de Acceso WiFi

## Objetivo
El ESP32 crea su propia red WiFi (como si fuera un router) sin necesitar internet ni un router real. Otros dispositivos como celulares o tablets pueden conectarse a esa red y el ESP32 reporta quién se conecta o desconecta.

## Materiales
- ESP32
- Cable USB
- Computadora con Arduino IDE
- Celular o tablet (para conectarse a la red del ESP32)

---

## Configuración de red — LEER ANTES DE SUBIR EL SKETCH

### El problema de usar el mismo nombre de red en clase

Si todos los grupos usan el mismo SSID (`"ESP32-Clase"`) y la misma contraseña (`"arduino123"`), ocurre lo siguiente:

- El celular ve **múltiples redes con el mismo nombre** y se conecta automáticamente a la de mayor señal, que puede ser la de otro grupo.
- Es imposible saber a qué ESP32 está conectado cada dispositivo.
- El Monitor Serie de un ESP32 puede mostrar conexiones de celulares que no pertenecen a ese grupo.
- Si dos ESP32 usan el mismo canal WiFi, pueden interferir entre sí y degradar la señal de ambos.

### Solución: cada grupo debe configurar valores únicos

Antes de subir el sketch, modificar estas líneas al inicio del código:

```cpp
const char* NOMBRE_RED = "ESP32-Clase";  // ← CAMBIAR por un nombre único
const char* CONTRASENA = "arduino123";   // ← CAMBIAR si quieres
const int   CANAL      = 6;             // ← CAMBIAR según la tabla de abajo
```

**Ejemplos de nombres únicos (SSID):**
- `"ESP32-Juan-G1"` → nombre del alumno + número de grupo
- `"ESP32-Grupo3"` → solo el grupo
- `"AP-2B-Maria"` → curso + nombre del alumno

### Canales WiFi recomendados por grupo (sin interferencia entre sí)

Los canales 1, 6 y 11 en la banda 2.4 GHz son los únicos que **no se superponen**. Usarlos reduce la interferencia entre grupos.

| Grupo | Canal sugerido |
|-------|---------------|
| Grupo 1 | 1 |
| Grupo 2 | 6 |
| Grupo 3 | 11 |
| Grupo 4 | 1 (si está lejos del Grupo 1) |
| Grupo 5 | 6 (si está lejos del Grupo 2) |

### Contraseña
- Mínimo **8 caracteres**, obligatorio para WPA2.
- Si se deja vacía (`""`), la red es abierta (sin contraseña). Se puede probar como experimento.

### ¿Hay conflicto de IP entre grupos?
**No.** La IP del ESP32 siempre es **192.168.4.1**, pero eso no genera conflicto porque cada grupo tiene su **propia red separada e independiente**. Un dispositivo en la red del Grupo 1 no puede ver ni comunicarse con el ESP32 del Grupo 2.

---

## Pasos para ejecutar
1. Modificar `NOMBRE_RED` y `CANAL` con los valores únicos de tu grupo.
2. Subir el sketch al ESP32.
3. Abrir el Monitor Serie a **115200 baudios**.
4. En el celular, ir a **Configuración → WiFi** y buscar el nombre de red que configuraste.
5. Conectarse con la contraseña elegida.
6. Observar en el Monitor Serie cómo aparece el mensaje de conexión.
7. Desconectar el celular y ver el mensaje de desconexión.

---

## Preguntas para registrar en el documento Word

Responde cada pregunta con lo que observaste. Puedes incluir capturas del Monitor Serie y de la pantalla del celular.

1. ¿Qué nombre de red (SSID) configuró tu grupo y por qué eligieron ese nombre?
2. ¿Cuántos dispositivos se conectaron a tu ESP32 durante la actividad?
3. ¿Qué IP le asignó el ESP32 al celular? (buscarlo en Configuración → WiFi → detalles de la red conectada en el celular)
4. ¿Qué diferencia hay entre un Access Point creado con el ESP32 y un router hogareño?
5. ¿Qué pasaría exactamente si otro grupo usara el mismo SSID que el tuyo? Describe el escenario.
6. ¿Por qué la IP del ESP32 siempre es 192.168.4.1 sin importar el SSID? ¿Qué protocolo asigna esa dirección?
7. Prueba crear la red sin contraseña (poniendo `CONTRASENA = ""`). ¿Qué observas? ¿Qué riesgo de seguridad implica una red WiFi abierta?
8. ¿El ESP32 tiene acceso a internet en este modo? ¿Por qué sí o por qué no?

---

## Desafío opcional
Cambiar `MAX_CLIENTES` a 1 y observar qué pasa cuando un segundo celular intenta conectarse a la red mientras ya hay uno conectado.
