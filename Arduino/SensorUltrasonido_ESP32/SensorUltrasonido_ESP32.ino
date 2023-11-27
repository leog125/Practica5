#define SOUND_SPEED 0.034   // Velocidad del sonido en el aire ≈ 343 m/s
#define ECHO_PIN 27          // Pin del eco del sensor
#define TRIGGER_PIN 14      // Pin del trigger del sensor

void setup() {
  Serial.begin(115200);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  long duration;
  float distance_cm;

  // Genera un pulso corto en el pin del trigger para iniciar la medición
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Lee la duración del pulso en el pin del eco
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calcula la distancia en milímetros y centímetros
  distance_cm = duration * SOUND_SPEED / 2;

  // Imprime la distancia en la consola serial
  Serial.print("Distancia en cm: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(1000);
}
