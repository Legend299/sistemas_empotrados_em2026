#include <WiFi.h>

const char* NOMBRE_RED   = "ESP32-Clase";
const char* CONTRASENA   = "arduino123";
const int   CANAL        = 6;
const int   MAX_CLIENTES = 4;

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.println("===========================================");
  Serial.println("   PUNTO DE ACCESO WiFi - ESP32");
  Serial.println("===========================================");

  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);
  delay(100);
  WiFi.mode(WIFI_AP);
  delay(100);

  bool exito;
  if (String(CONTRASENA).length() == 0) {
    exito = WiFi.softAP(NOMBRE_RED, NULL, CANAL, 0, MAX_CLIENTES);
  } else {
    exito = WiFi.softAP(NOMBRE_RED, CONTRASENA, CANAL, 0, MAX_CLIENTES);
  }

  if (exito) {
    Serial.println("\n  ¡Punto de Acceso creado con éxito!\n");
    Serial.println("  ----- DATOS DE LA RED -----");
    Serial.printf("  Nombre (SSID) : %s\n", NOMBRE_RED);
    if (String(CONTRASENA).length() > 0) {
      Serial.printf("  Contraseña    : %s\n", CONTRASENA);
    } else {
      Serial.println("  Contraseña    : (ninguna - red abierta)");
    }
    Serial.printf("  Canal WiFi    : %d\n", CANAL);
    Serial.printf("  IP del ESP32  : %s\n", WiFi.softAPIP().toString().c_str());
    Serial.printf("  Máx. clientes : %d\n", MAX_CLIENTES);
    Serial.println("  ---------------------------\n");
    Serial.println("  Esperando que alguien se conecte...");
  } else {
    Serial.println("\n  ERROR: No se pudo crear el Punto de Acceso.");
  }
}

int clientesAnteriores = 0;

void loop() {
  int clientesActuales = WiFi.softAPgetStationNum();

  if (clientesActuales != clientesAnteriores) {
    if (clientesActuales > clientesAnteriores) {
      Serial.printf("  >> Nuevo dispositivo conectado! Total: %d\n", clientesActuales);
    } else {
      Serial.printf("  << Dispositivo desconectado. Total: %d\n", clientesActuales);
    }
    clientesAnteriores = clientesActuales;
  }

  delay(1000);
}
