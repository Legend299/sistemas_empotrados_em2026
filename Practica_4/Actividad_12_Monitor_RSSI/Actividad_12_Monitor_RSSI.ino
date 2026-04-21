#include <WiFi.h>

const int MAX_REDES = 8;

void setup() {
  Serial.begin(115200);
  delay(2000);

  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);
  delay(100);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("===========================================");
  Serial.println("   MONITOR DE SEÑAL WiFi (RSSI) - ESP32");
  Serial.println("===========================================");
  Serial.println("  Escaneando redes...\n");
}

int rssiABarras(int rssi) {
  if (rssi >= -50) return 5;
  if (rssi >= -60) return 4;
  if (rssi >= -70) return 3;
  if (rssi >= -80) return 2;
  if (rssi >= -90) return 1;
  return 0;
}

String rssiACalidad(int rssi) {
  if (rssi >= -50) return "Excelente";
  if (rssi >= -60) return "Buena    ";
  if (rssi >= -70) return "Regular  ";
  if (rssi >= -80) return "Debil    ";
  return "Muy debil";
}

String dibujarBarra(int barras) {
  String barra = "[";
  for (int i = 0; i < 5; i++) {
    barra += (i < barras) ? "█" : "░";
  }
  barra += "]";
  return barra;
}

void loop() {
  int cantRedes = WiFi.scanNetworks();
  unsigned long segundos = millis() / 1000;

  Serial.println();
  Serial.printf("  Tiempo: %lus  |  Redes encontradas: %d\n", segundos, cantRedes);
  Serial.println("  ----------------------------------------------------------");
  Serial.println("  Señal       | RSSI   | Calidad   | Red (SSID)");
  Serial.println("  ------------|--------|-----------|------------------------");

  if (cantRedes == 0) {
    Serial.println("  (no se detectaron redes WiFi)");
  } else {
    int mostrar = min(cantRedes, MAX_REDES);
    for (int i = 0; i < mostrar; i++) {
      int    rssi   = WiFi.RSSI(i);
      String ssid   = WiFi.SSID(i);
      int    barras = rssiABarras(rssi);

      if (ssid.length() == 0) ssid = "(oculta)";
      if (ssid.length() > 22) ssid = ssid.substring(0, 19) + "...";

      Serial.printf("  %-12s | %4d   | %-9s | %s\n",
                    dibujarBarra(barras).c_str(),
                    rssi,
                    rssiACalidad(rssi).c_str(),
                    ssid.c_str());
    }
    if (cantRedes > MAX_REDES) {
      Serial.printf("  ... y %d redes más (no mostradas)\n", cantRedes - MAX_REDES);
    }
  }

  Serial.println("  ----------------------------------------------------------");

  WiFi.scanDelete();
  delay(5000);
}
