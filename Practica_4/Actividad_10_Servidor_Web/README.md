# Actividad 10 — Servidor Web en el ESP32

## Objetivo
El ESP32 crea su propia red WiFi **y** sirve una página web desde su memoria interna. Desde un celular conectado a esa red, se puede abrir el navegador y ver la página generada por el ESP32. No se necesita internet en ningún momento.

## Materiales
- ESP32
- Cable USB
- Computadora con Arduino IDE
- Celular con navegador web (Chrome, Firefox, Safari, etc.)

---

## Configuración de red — LEER ANTES DE SUBIR EL SKETCH

### El problema de usar el mismo SSID en clase

Si varios grupos usan el mismo nombre de red, el celular se conecta al ESP32 con mayor señal (que puede ser el de otro grupo). En ese caso:

- El celular abrirá la página web del grupo equivocado.
- El Monitor Serie del ESP32 correcto no mostrará ninguna visita.
- No habrá ningún error visible: todo parecerá funcionar, pero estará mirando el servidor equivocado.

### Solución: modificar el SSID antes de subir

```cpp
const char* SSID     = "ESP32-Web";  // ← CAMBIAR por un nombre único de grupo
const char* PASSWORD = "web12345";   // ← CAMBIAR si quieres (mín. 8 caracteres)
```

**Ejemplos de SSID únicos:**
- `"Web-Juan-G1"`
- `"ESP32Web-Grupo2"`
- `"Servidor-Ana-2B"`

### IP del servidor web
La dirección del servidor siempre es **`192.168.4.1`** (puerto 80). No cambia según el SSID. No hay conflicto entre grupos porque cada uno tiene su propia red separada.

Para abrir la página en el navegador del celular escribir: `http://192.168.4.1`

### ¿Qué pasa si dos grupos tienen el mismo SSID?
El celular se conecta al ESP32 con mayor señal. Si ese ESP32 pertenece a otro grupo, verás la página de ese grupo (con su contenido HTML). El Monitor Serie del ESP32 propio no registrará ninguna visita. No hay forma de detectar el error sin revisar el Monitor Serie.

---

## Pasos para ejecutar
1. Modificar `SSID` con el nombre único de tu grupo en el código.
2. Subir el sketch al ESP32.
3. Abrir el Monitor Serie a **115200 baudios**.
4. En el celular, conectarse a la red WiFi del ESP32.
5. Abrir el navegador del celular y escribir: `192.168.4.1`
6. Observar la página web y los mensajes que aparecen en el Monitor Serie al visitarla.
7. Probar abrir una URL inexistente como `192.168.4.1/prueba` y ver qué responde el ESP32.

---

## Preguntas para registrar en el documento Word

Responde cada pregunta con lo que observaste. Incluye capturas del navegador y del Monitor Serie.

1. ¿Qué es un servidor web? ¿Qué diferencia hay entre un servidor y un cliente web (el navegador)?
2. ¿Qué significa el código de respuesta `200` que el ESP32 envía? ¿Y el código `404`?
3. ¿Qué pasa si escribes en el navegador `192.168.4.1/pagina-que-no-existe`? Describe la respuesta.
4. ¿Cuántas personas pueden ver la página al mismo tiempo? Probarlo con dos celulares y describir qué ocurre.
5. ¿El ESP32 necesita internet para servir esta página? ¿Por qué? ¿Dónde está almacenada la página?
6. Mira el código HTML dentro del sketch (la variable `PAGINA_HTML`). ¿Puedes identificar dónde está el texto del título (`<title>`) y el encabezado principal (`<h1>`)?
7. Modifica el texto de la página (algún párrafo dentro del HTML), vuelve a subir el sketch y abre la página de nuevo. ¿Qué cambió?
8. ¿Por qué se usa el puerto 80 para el servidor web? ¿Qué es un puerto en redes y para qué sirve?

---

## Desafío opcional
Agregar una segunda ruta `/info` en el servidor que responda una página de texto plano con el tiempo que lleva funcionando el ESP32 (en segundos, usando `millis()`).
