#include <WiFi.h>
#include <WebServer.h>

const char* SSID     = "ESP32-LED";
const char* PASSWORD = "led12345";
const int   PIN_LED  = 2;

WebServer servidor(80);
bool estadoLED = false;

String generarPagina() {
  String color    = estadoLED ? "#27ae60" : "#c0392b";
  String texto    = estadoLED ? "ENCENDIDO" : "APAGADO";
  String btnEnc   = estadoLED ? "disabled" : "";
  String btnApag  = estadoLED ? "" : "disabled";

  String html = "<!DOCTYPE html><html lang='es'><head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<title>Control LED</title>";
  html += "<style>";
  html += "body{font-family:Arial,sans-serif;background:#1a1a2e;color:#eaeaea;";
  html += "display:flex;flex-direction:column;align-items:center;padding:30px;}";
  html += "h1{color:#e94560;}";
  html += ".estado{font-size:2em;font-weight:bold;padding:15px 30px;border-radius:10px;";
  html += "background:" + color + ";margin:20px;min-width:200px;text-align:center;}";
  html += ".btn{font-size:1.3em;padding:15px 40px;margin:10px;border:none;";
  html += "border-radius:8px;cursor:pointer;transition:opacity 0.2s;}";
  html += ".btn:disabled{opacity:0.3;cursor:not-allowed;}";
  html += ".enc{background:#27ae60;color:white;}";
  html += ".apag{background:#c0392b;color:white;}";
  html += "</style></head><body>";
  html += "<h1>Control de LED - ESP32</h1>";
  html += "<div class='estado'>LED: " + String(texto) + "</div>";
  html += "<form method='GET'>";
  html += "<button class='btn enc' name='cmd' value='on' " + String(btnEnc) + ">Encender</button>";
  html += "<button class='btn apag' name='cmd' value='off' " + String(btnApag) + ">Apagar</button>";
  html += "</form>";
  html += "<p style='margin-top:30px;color:#888;'>Cada botón envía una solicitud HTTP al ESP32.</p>";
  html += "</body></html>";
  return html;
}

void manejarRaiz() {
  if (servidor.hasArg("cmd")) {
    String comando = servidor.arg("cmd");
    if (comando == "on") {
      estadoLED = true;
      digitalWrite(PIN_LED, HIGH);
      Serial.println("  >> Comando recibido: LED ENCENDIDO");
    } else if (comando == "off") {
      estadoLED = false;
      digitalWrite(PIN_LED, LOW);
      Serial.println("  >> Comando recibido: LED APAGADO");
    }
  }
  servidor.send(200, "text/html", generarPagina());
}

void setup() {
  Serial.begin(115200);
  delay(2000);

  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  Serial.println("===========================================");
  Serial.println("   CONTROL DE LED POR WiFi - ESP32");
  Serial.println("===========================================");

  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);
  delay(100);
  WiFi.mode(WIFI_AP);
  delay(100);
  WiFi.softAP(SSID, PASSWORD);

  Serial.printf("\n  Red: %s  |  Clave: %s\n", SSID, PASSWORD);
  Serial.printf("  Abrir en el celular: http://%s\n", WiFi.softAPIP().toString().c_str());
  Serial.println("-------------------------------------------");

  servidor.on("/", manejarRaiz);
  servidor.begin();
  Serial.println("  Servidor listo. Esperando conexiones...\n");
}

void loop() {
  servidor.handleClient();
}
