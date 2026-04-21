#include <esp_now.h>
#include <WiFi.h>
#include "DHT.h"

#define DHTPIN  4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

typedef struct {
  float temperatura;
  float humedad;
  bool  lectura_ok;
} SensorData;

SensorData datosSensor;

void onDataSent(const wifi_tx_info_t *info, esp_now_send_status_t status) {
  Serial.print("Envío de datos a: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "CORRECTO " : "FALLO ");
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.mode(WIFI_STA);
  // esp_wifi_set_max_tx_power(84);

  Serial.print("Mac Address: ");
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != ESP_OK) {
    Serial.println("No se pudo inicializar ESP-NOW");
    return;
  }

  esp_now_register_send_cb(onDataSent);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("No se pudo agregar peer broadcast");
    return;
  }

  Serial.println("Transmitiendo cada 2 segundos");
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Error de lectura del DHT11");
    datosSensor.lectura_ok   = false;
    datosSensor.temperatura  = 0.0;
    datosSensor.humedad      = 0.0;
  } else {
    datosSensor.temperatura  = t;
    datosSensor.humedad      = h;
    datosSensor.lectura_ok   = true;
    Serial.printf("Temp: %.1f °C  |  Humedad: %.1f %%\n", t, h);
  }

  esp_now_send(broadcastAddress, (uint8_t *)&datosSensor, sizeof(datosSensor));

  delay(2000);
}
