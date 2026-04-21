#include <WiFi.h>

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
  Serial.println("   ESCANER DE REDES WiFi - ESP32");
  Serial.println("===========================================");
  Serial.println("Listo. Iniciando escaneo cada 10 segundos...\n");
}

void loop() {
  Serial.println("Buscando redes WiFi...");

  int cantRedes = WiFi.scanNetworks();

  if (cantRedes == 0) {
    Serial.println("  No se encontraron redes WiFi.");
  } else {
    Serial.printf("  Se encontraron %d redes:\n\n", cantRedes);
    Serial.println("  N  | SSID (Nombre de red)     | RSSI  | Seguridad       | Canal");
    Serial.println("  ---|-------------------------|-------|-----------------|------");

    for (int i = 0; i < cantRedes; i++) {
      String ssid      = WiFi.SSID(i);
      int    rssi      = WiFi.RSSI(i);
      String seguridad = obtenerSeguridad(WiFi.encryptionType(i));
      int    canal     = WiFi.channel(i);

      if (ssid.length() > 23) ssid = ssid.substring(0, 20) + "...";

      Serial.printf("  %2d | %-23s | %4d  | %-15s | %d\n",
                    i + 1, ssid.c_str(), rssi, seguridad.c_str(), canal);
    }
  }

  WiFi.scanDelete();
  Serial.println("\n  Proximo escaneo en 10 segundos...");
  Serial.println("-------------------------------------------\n");
  delay(10000);
}

String obtenerSeguridad(wifi_auth_mode_t tipo) {
  switch (tipo) {
    case WIFI_AUTH_OPEN:          return "Abierta (sin clave)";
    case WIFI_AUTH_WEP:           return "WEP";
    case WIFI_AUTH_WPA_PSK:       return "WPA";
    case WIFI_AUTH_WPA2_PSK:      return "WPA2";
    case WIFI_AUTH_WPA_WPA2_PSK:  return "WPA/WPA2";
    case WIFI_AUTH_WPA3_PSK:      return "WPA3";
    case WIFI_AUTH_WPA2_WPA3_PSK: return "WPA2/WPA3";
    default:                      return "Desconocida";
  }
}
