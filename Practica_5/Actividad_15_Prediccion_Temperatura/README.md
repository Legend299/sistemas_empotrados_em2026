# Actividad 15 — Predicción de Temperatura con Regresión Lineal

## Objetivo
El ESP32 Receptor recibe temperatura y humedad del ESP32 Principal via ESP-NOW y aplica **regresión lineal** sobre las últimas 10 lecturas para predecir la temperatura en 2 y 5 minutos.

## Materiales

### ESP32 Principal
- En clase ya se va estár ejecutando el ESP32 Principal con el sensor DHT11 transmitiendo datos via ESP-NOW.

### ESP32 Receptor (alumno)
- ESP32
- Cable USB
- Computadora con Chrome o Edge

> No se necesita ningún sensor adicional.

---

## Concepto: ¿Qué es Regresión Lineal?

Dado un conjunto de mediciones a lo largo del tiempo, la regresión lineal encuentra la **recta que mejor se ajusta** a esos datos usando el método de **mínimos cuadrados**.

$$\hat{y} = m \cdot x + b$$

Donde:
- $x$ = índice de tiempo (0, 1, 2, ..., n-1)
- $y$ = temperatura medida en cada instante
- $m$ = pendiente (¿cuánto cambia la T° por cada paso?)
- $b$ = intercepto (valor inicial de la recta)

### Fórmulas de mínimos cuadrados

$$m = \frac{n \sum x_i y_i - \sum x_i \sum y_i}{n \sum x_i^2 - \left(\sum x_i\right)^2}$$

$$b = \frac{\sum y_i - m \sum x_i}{n}$$

### Predicción

Una vez obtenida la recta, predecir es simplemente evaluar:

$$\hat{y}_{futuro} = m \cdot x_{futuro} + b$$

---

## Implementaciones que el alumno debe completar

El código tiene **4 secciones marcadas como `Implementación`**. Las primeras 3 están en el `.ino` y la última en el `dashboard.html`.

| Implementación | Dónde | Qué completar |
|---|---|---|
| **Implementación 1** | `.ino` función `regresionLineal()` | Fórmula de la pendiente **m** |
| **Implementación 2** | `.ino` función `regresionLineal()` | Fórmula del intercepto **b** |
| **Implementación 3** | `.ino` callback `onDataRecv()` | Predicciones a 2 y 5 minutos usando **m** y **b** |
| **Implementación 4** | `dashboard.html` | Tabla HTML de historial de lecturas |

---

## JSON que envía el receptor al dashboard

```json
{"t":25.3,"h":60.1,"m":0.12,"b":24.1,"pred_2min":25.5,"pred_5min":25.9,"n":10}
```

| Campo | Descripción |
|---|---|
| `t` | Temperatura actual medida (°C) |
| `h` | Humedad actual (%) |
| `m` | Pendiente de la recta calculada |
| `b` | Intercepto de la recta calculada |
| `pred_2min` | Predicción a 2 minutos (°C) |
| `pred_5min` | Predicción a 5 minutos (°C) |
| `n` | Número de muestras usadas (máx. 10) |

---

## Estructura de archivos

```
Actividad_15_Prediccion_Temperatura/
├── Actividad_15_Prediccion_Temperatura.ino   ← Código del ESP32 Receptor
├── dashboard.html                             ← Dashboard con gráfica
└── README.md
```

---

## Pasos para ejecutar

### ESP32 Receptor
1. Abrir `Actividad_15_Prediccion_Temperatura.ino` en Arduino IDE.
2. Buscar los comentarios `Implementación 1`, `Implementación 2` e `Implementación 3` y completar las fórmulas.
3. Seleccionar la placa **ESP32 Dev Module** y el puerto COM correcto.
4. Subir el sketch.
5. Verificar en el Monitor Serie (115200 baudios):
   - Al inicio: `{"status":"listo"}`
   - Con datos: `{"t":25.3,"h":60.1,"m":0.00,"b":0.00,"pred_2min":0.0,...}`
   - Cuando las implementaciones 1–3 estén correctas, `m`, `b`, `pred_2min` y `pred_5min` tendrán valores distintos de 0.
6. **Cerrar el Monitor Serie** antes de abrir el dashboard.

### Dashboard
1. Abrir `dashboard.html` en **Chrome o Edge**.
2. Presionar **"Conectar ESP32"** y seleccionar el puerto.
3. Observar las tarjetas de datos actualizándose en tiempo real.
4. Completar la **Implementación 4**: la tabla de historial en el HTML.
5. Variar la temperatura del sensor (soplar, acercar al cuerpo) y observar cómo cambia la pendiente y las predicciones.

---

## Pistas para las implementaciones

### Implementación 1 — Pendiente m
Tienes disponibles: `suma_x`, `suma_y`, `suma_xy`, `suma_x2` y `n`.
La fórmula es:

$$m = \frac{n \cdot suma\_xy - suma\_x \cdot suma\_y}{n \cdot suma\_x2 - suma\_x^2}$$

Verifica que el denominador no sea 0.

### Implementación 2 — Intercepto b
Una vez que tienes `m`:

$$b = \frac{suma\_y - m \cdot suma\_x}{n}$$

### Implementación 3 — Predicciones
El "x futuro" para 2 minutos es `(contadorMuestras - 1) + PASOS_2MIN`.
Evalúa la recta: `pred_2min = m * x_futuro + b`.

### Implementación 4 — Tabla de historial (JavaScript)
Necesitas:
1. Agregar la tabla HTML con un `<tbody id="cuerpo-historial">` y columnas: Hora, Temp, Humedad, Pred 2min, Pred 5min, m, b, n.
2. Crear la función `agregarFilaHistorial(d)` que inserte una fila con `insertRow(0)` para que la más reciente quede arriba.
3. Llamar a `agregarFilaHistorial(d)` desde `procesarLinea()`.

---

## Conceptos clave

| Concepto | Descripción |
|---|---|
| **Regresión lineal** | Método estadístico para encontrar la recta que mejor se ajusta a un conjunto de datos |
| **Mínimos cuadrados** | Criterio que minimiza la suma de los cuadrados de los errores entre la recta y los datos reales |
| **Pendiente m** | Indica la tendencia: positiva = sube, negativa = baja, ≈0 = estable |
| **Predicción extrapolada** | Estimar valores fuera del rango conocido usando el modelo ajustado |