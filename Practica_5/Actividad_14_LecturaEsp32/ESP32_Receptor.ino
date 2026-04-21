#include <esp_now.h>
#include <WiFi.h>

typedef struct {
  float temperatura;
  float humedad;
  bool  lectura_ok;
} SensorData;

void onDataRecv(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
  if (len != sizeof(SensorData)) return;

  SensorData d;
  memcpy(&d, data, sizeof(d));

  if (d.lectura_ok) {
    // envia un JSON por el puerto serial y lo lee el dashboard.html
    // formato a leer: {"t":25.3,"h":60.1} ; donde t es temperatura(C) y h es humedad(%)
    Serial.print("{\"t\":");
    Serial.print(d.temperatura, 1);
    Serial.print(",\"h\":");
    Serial.print(d.humedad, 1);
    Serial.println("}");
  }
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
