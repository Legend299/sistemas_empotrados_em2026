// Pin del LED (conecta el ánodo del LED + resistencia al pin, cátodo a GND)
const int ledPin = 2;

// Parámetros PWM (LEDC)
const int freq = 5000;       // Frecuencia PWM en Hz (5-5000Hz)
const int resolution = 8;    // Resolución en bits (8 bits -> 0..255 , 9 bits -> 0..511)

void setup() {
  // Asocia el pin al PWM configurando automáticamente frecuencia y resolución
  ledcAttach(ledPin, freq, resolution);
}

void loop() {
  // 128 representa un 50% de duty cycle o brillo medio en un Led.
  ledcWrite(ledPin, 128);
}