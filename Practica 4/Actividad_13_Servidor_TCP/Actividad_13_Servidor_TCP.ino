#include <WiFi.h>

const char* SSID     = "ESP32-Chat";
const char* PASSWORD = "chat1234";
const int   PUERTO   = 8080;
const int   PIN_LED  = 2;

WiFiServer servidorTCP(PUERTO);
bool estadoLED = false;

String procesarMensaje(String mensaje) {
  mensaje.trim();
  mensaje.toLowerCase();

  Serial.printf("  >> Recibido: \"%s\"\n", mensaje.c_str());

  if (mensaje == "hola" || mensaje == "hola!") {
    return "Hola desde el ESP32\n";

  } else if (mensaje == "led on") {
    estadoLED = true;
    digitalWrite(PIN_LED, HIGH);
    return "LED encendido ✓\n";

  } else if (mensaje == "led off") {
    estadoLED = false;
    digitalWrite(PIN_LED, LOW);
    return "LED apagado ✓\n";

  } else if (mensaje == "estado") {
    String estado = estadoLED ? "ENCENDIDO" : "APAGADO";
    return "Estado del LED: " + estado + "\n";

  } else if (mensaje == "tiempo") {
    unsigned long seg = millis() / 1000;
    unsigned long min = seg / 60;
    seg = seg % 60;
    return "Tiempo activo: " + String(min) + " min " + String(seg) + " seg\n";

  } else if (mensaje == "ping") {
    return "pong\n";

  } else if (mensaje.length() == 0) {
    return "";

  } else {
    return "Echo: " + mensaje + "\n";
  }
}

void setup() {
  Serial.begin(115200);
  delay(2000);

  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  Serial.println("===========================================");
  Serial.println("   SERVIDOR TCP / CHAT WiFi - ESP32");
  Serial.println("===========================================");

  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);
  delay(100);
  WiFi.mode(WIFI_AP);
  delay(100);
  WiFi.softAP(SSID, PASSWORD);

  servidorTCP.begin();

  Serial.printf("\n  Red WiFi  : %s\n", SSID);
  Serial.printf("  Clave     : %s\n", PASSWORD);
  Serial.printf("  IP        : %s\n", WiFi.softAPIP().toString().c_str());
  Serial.printf("  Puerto TCP: %d\n\n", PUERTO);
  Serial.println("  Comandos disponibles:");
  Serial.println("    hola | led on | led off | estado | tiempo | ping");
  Serial.println("    (cualquier otro texto es devuelto como eco)");
  Serial.println("-------------------------------------------");
  Serial.println("  Esperando conexión TCP...\n");
}

void loop() {
  WiFiClient cliente = servidorTCP.available();

  if (cliente) {
    Serial.printf("  >> Cliente conectado desde: %s\n", cliente.remoteIP().toString().c_str());
    cliente.println("Chat desde el ESP32 Activo.");

    String bufferLinea = "";
    unsigned long ultimoCaracter = millis();

    while (cliente.connected()) {
      if (cliente.available()) {
        char c = cliente.read();
        ultimoCaracter = millis();

        if (c == '\n' || c == '\r') {
          if (bufferLinea.length() > 0) {
            String respuesta = procesarMensaje(bufferLinea);
            if (respuesta.length() > 0) {
              cliente.print(respuesta);
            }
            bufferLinea = "";
          }
        } else {
          bufferLinea += c;

          if (bufferLinea.length() > 200) {
            cliente.println("Error: mensaje demasiado largo.");
            bufferLinea = "";
          }
        }
      } else {
        if (bufferLinea.length() > 0 && (millis() - ultimoCaracter > 300)) {
          String respuesta = procesarMensaje(bufferLinea);
          if (respuesta.length() > 0) {
            cliente.print(respuesta);
          }
          bufferLinea = "";
        }
      }
      delay(1);
    }

    cliente.stop();
    Serial.println("  << Cliente desconectado.\n");
  }
}
