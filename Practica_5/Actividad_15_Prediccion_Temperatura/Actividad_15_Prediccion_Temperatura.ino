/*
 * Actividad 15 — Predicción de Temperatura con Regresión Lineal
 *
 * esta es una EXTENSIÓN de la Actividad 14.
 * El ESP32 Receptor recibe T° y H% del ESP32 Principal via ESP-NOW
 * y aplica REGRESIÓN LINEAL sobre las últimas lecturas para
 * predecir cómo estará la temperatura en el futuro.
 *
 * ── ¿Qué es regresión lineal? ────────────────────────────────────
 * Dado un conjunto de puntos (x0,y0), (x1,y1)...(xn,yn),
 * la regresión lineal encuentra la recta  y = m*x + b  que mejor
 * se ajusta a esos datos (mínimos cuadrados).
 *
 * En esta actividad:
 *   x = índice de tiempo (0, 1, 2, ... N-1)
 *   y = temperatura medida en cada instante
 *
 * Con la recta obtenida se predice:
 *   pred_2min = m * (N-1 + pasos_2min) + b
 *   pred_5min = m * (N-1 + pasos_5min) + b
 *
 * el SON que envía al dashboard la sig info
 * {"t":25.3,"h":60.1,"m":0.12,"b":24.1,
 *  "pred_2min":25.5,"pred_5min":25.9,"n":10}
 *
 *   t        → temperatura actual (°C)
 *   h        → humedad actual (%)
 *   m        → pendiente de la recta (°C por paso)
 *   b        → intercepto de la recta
 *   pred_2min → predicción a 2 minutos
 *   pred_5min → predicción a 5 minutos
 *   n        → cuántas muestras se usaron para la regresión
 *
 * Lo que se debe implementar
 *   Fórmula 1 → Fórmula de la pendiente m
 *   Fórmula 2 → Fórmula del intercepto b
 *   Fórmula 3 → Calcular pred_2min y pred_5min usando m y b
 */

#include <esp_now.h>
#include <WiFi.h>

typedef struct {
  float temperatura;
  float humedad;
  bool  lectura_ok;
} SensorData;

#define N_MUESTRAS   10      // cuántas lecturas usar para la regresión
#define INTERVALO_S   2      // segundos entre lecturas del Principal

// A 2 minutos → 120s / 2s = 60 pasos adelante
// A 5 minutos → 300s / 2s = 150 pasos adelante
#define PASOS_2MIN   60
#define PASOS_5MIN  150

float bufferTemp[N_MUESTRAS];
int   contadorMuestras = 0;    // cuántas muestras se han guardado
int   indiceActual     = 0;

void agregarMuestra(float temp) {
  bufferTemp[indiceActual] = temp;
  indiceActual = (indiceActual + 1) % N_MUESTRAS;
  if (contadorMuestras < N_MUESTRAS) contadorMuestras++;
}

float obtenerMuestra(int i) {
  if (contadorMuestras < N_MUESTRAS) {
    return bufferTemp[i];
  } else {
    return bufferTemp[(indiceActual + i) % N_MUESTRAS];
  }
}

// ── FUNCIÓN DE REGRESIÓN LINEAL ──────────────────────────────────
// Calcula m (pendiente) y b (intercepto) de la recta
// que mejor se ajusta a los datos.
//
// Fórmulas de mínimos cuadrados:
//
//        n * Σ(xi * yi)  −  Σxi * Σyi
//   m = ─────────────────────────────────
//        n * Σ(xi²)  −  (Σxi)²
//
//        Σyi  −  m * Σxi
//   b = ──────────────────
//               n
//
// donde xi = 0, 1, 2, ..., n-1  (índice de tiempo)
//       yi = temperatura en el instante i
void regresionLineal(float &m, float &b) {
  int n = contadorMuestras;
  if (n < 2) { m = 0; b = obtenerMuestra(0); return; }

  float suma_x  = 0;
  float suma_y  = 0;
  float suma_xy = 0;
  float suma_x2 = 0;

  for (int i = 0; i < n; i++) {
    float xi = (float)i;
    float yi = obtenerMuestra(i);
    suma_x  += xi;
    suma_y  += yi;
    suma_xy += xi * yi;
    suma_x2 += xi * xi;
  }

  // ── Fórmula 1 ───────────────────────────────────────────────────
  // Calcula la pendiente m usando la fórmula de mínimos cuadrados.
  // usa las variables suma_x, suma_y, suma_xy, suma_x2 y n.
  //
  // m = ( n*suma_xy - suma_x*suma_y ) / ( n*suma_x2 - suma_x^2 )
  //
  // ¿Qué pasa si el denominador es 0? Maneja ese caso.
  //
  m = 0.0;  // ← REEMPLAZAR con la fórmula correcta
  // ─────────────────────────────────────────────────────────────

  // ── Fórmula 2 ───────────────────────────────────────────────────
  // Calcula el intercepto b.
  // despeja b de la fórmula  Σyi = m*Σxi + n*b
  //
  b = 0.0;  // ← REEMPLAZAR con la fórmula correcta
  // ─────────────────────────────────────────────────────────────
}

void onDataRecv(const esp_now_recv_info_t *info,
                const uint8_t *data, int len) {
  if (len != sizeof(SensorData)) return;

  SensorData d;
  memcpy(&d, data, sizeof(d));
  if (!d.lectura_ok) return;

  agregarMuestra(d.temperatura);

  float m, b;
  regresionLineal(m, b);

  // Fórmula 3
  // Usa la recta  y = m*x + b  para predecir la temperatura
  // en el futuro.
  //
  // El "x" para la predicción es:
  //   (contadorMuestras - 1) + PASOS_2MIN   → para 2 minutos
  //   (contadorMuestras - 1) + PASOS_5MIN   → para 5 minutos
  //
  // si la recta es  y = m*x + b
  //        ¿cuál es la y cuando x = (n-1) + pasos?
  //
  float pred_2min = 0.0;  // ← REEMPLAZAR
  float pred_5min = 0.0;  // ← REEMPLAZAR
  // ─────────────────────────────────────────────────────────────

  // Este JSON se envía al dashboard y ya se puede visualizar mejor.
  Serial.print("{\"t\":");          Serial.print(d.temperatura, 1);
  Serial.print(",\"h\":");          Serial.print(d.humedad, 1);
  Serial.print(",\"m\":");          Serial.print(m, 4);
  Serial.print(",\"b\":");          Serial.print(b, 2);
  Serial.print(",\"pred_2min\":"); Serial.print(pred_2min, 1);
  Serial.print(",\"pred_5min\":"); Serial.print(pred_5min, 1);
  Serial.print(",\"n\":");          Serial.print(contadorMuestras);
  Serial.println("}");
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != ESP_OK) {
    Serial.println("{\"error\":\"ESP-NOW init failed\"}");
    return;
  }

  esp_now_register_recv_cb(onDataRecv);
  Serial.println("{\"status\":\"listo\"}");
}

void loop() {
  delay(100);
}
