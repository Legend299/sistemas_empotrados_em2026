const int ledPin = 2; // GPIO / PIN donde está conectado el LED

void setup() {
	// Inicializa el pin del LED como salida
	pinMode(ledPin, OUTPUT);
	// Asegura que el LED esté apagado al inicio
	digitalWrite(ledPin, LOW);
}

void loop() {
	// Enciende el LED
	digitalWrite(ledPin, HIGH);
	delay(1000); // espera 1 segundo

	// Apaga el LED
	digitalWrite(ledPin, LOW);
	delay(1000); // espera 1 segundo
}

