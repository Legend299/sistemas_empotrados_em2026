#include <WiFi.h>
#include <WebServer.h>

const char* SSID     = "ESP32-Web";
const char* PASSWORD = "web12345";

WebServer servidor(80);

const char PAGINA_HTML[] PROGMEM = R"(
<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Mi ESP32</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      background-color: #1a1a2e;
      color: #eaeaea;
      display: flex;
      flex-direction: column;
      align-items: center;
      padding: 30px;
    }
    h1 { color: #e94560; }
    .caja {
      background: #16213e;
      border-radius: 10px;
      padding: 20px 30px;
      margin: 10px;
      width: 80%;
      max-width: 400px;
      text-align: center;
      box-shadow: 0 4px 10px rgba(0,0,0,0.4);
    }
    .dato { font-size: 1.2em; color: #0f3460; background:#e94560;
            border-radius:5px; padding:5px 10px; display:inline-block; margin:5px; }
  </style>
</head>
<body>
  <h1>¡Hola desde el ESP32!</h1>
  <div class="caja">
    <h2>Servidor Web funcionando</h2>
    <p>Esta página fue generada por el microcontrolador ESP32.</p>
    <p>No hay internet aquí — ¡todo viene del chip!</p>
  </div>
  <div class="caja">
    <h3>Datos del Servidor</h3>
    <span class="dato">IP: 192.168.4.1</span>
    <span class="dato">Puerto: 80</span>
  </div>
  <div class="caja">
    <h3>¿Qué es esto?</h3>
    <p>El ESP32 actúa como Access Point y servidor HTTP al mismo tiempo.
       Tu celular se conectó a su WiFi y pidió esta página.</p>
  </div>
</body>
</html>
)";

void manejarRaiz() {
  servidor.send(200, "text/html", PAGINA_HTML);
  Serial.println("  >> Alguien visito la pagina principal.");
}

void manejarNoEncontrado() {
  String mensaje = "Error 404 - Pagina no encontrada\n\n";
  mensaje += "Ruta pedida: " + servidor.uri() + "\n";
  servidor.send(404, "text/plain", mensaje);
  Serial.printf("  >> Ruta no encontrada: %s\n", servidor.uri().c_str());
}

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.println("===========================================");
  Serial.println("   SERVIDOR WEB WiFi - ESP32");
  Serial.println("===========================================");

  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);
  delay(100);
  WiFi.mode(WIFI_AP);
  delay(100);
  WiFi.softAP(SSID, PASSWORD);

  Serial.println("\n  Access Point creado.");
  Serial.printf("  Red: %s  |  Clave: %s\n", SSID, PASSWORD);
  Serial.printf("  Direccion web: http://%s\n\n", WiFi.softAPIP().toString().c_str());

  servidor.on("/", manejarRaiz);
  servidor.onNotFound(manejarNoEncontrado);
  servidor.begin();
  Serial.println("  Servidor HTTP iniciado. Esperando conexiones...");
  Serial.println("-------------------------------------------");
}

void loop() {
  servidor.handleClient();
}
