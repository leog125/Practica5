#define SOUND_SPEED 0.034  // Velocidad del sonido en el aire ≈ 343 m/s
#define ECHO_PIN_1 12      // Pin del trigger del sensor  Ok
#define TRIGGER_PIN_1 13   // Pin del eco del sensor      Ok
#define ECHO_PIN_2 32      // Pin del trigger del sensor  Ok
#define TRIGGER_PIN_2 33   // Pin del eco del sensor      Ok
#define ECHO_PIN_3 2      // Pin del trigger del sensor   Ok
#define TRIGGER_PIN_3 15   // Pin del eco del sensor      Ok
#define ECHO_PIN_4 27      // Pin del trigger del sensor  Ok
#define TRIGGER_PIN_4 14   // Pin del eco del sensor      Ok

void setup() {
  Serial.begin(9600);
  pinMode(TRIGGER_PIN_1, OUTPUT); 
  pinMode(ECHO_PIN_1, INPUT);
  pinMode(TRIGGER_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);
  pinMode(TRIGGER_PIN_3, OUTPUT);
  pinMode(ECHO_PIN_3, INPUT);
  pinMode(TRIGGER_PIN_4, OUTPUT);
  pinMode(ECHO_PIN_4, INPUT);
}

void loop() {
  calculateDistance_1();
  delay(200);
  calculateDistance_2();
  delay(200);
  calculateDistance_3();
  delay(200);
  calculateDistance_4();
  delay(200);
}

void calculateDistance_1() {
  long duration;
  float distance_cm;

  // Genera un pulso corto en el pin del trigger para iniciar la medición
  digitalWrite(TRIGGER_PIN_1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN_1, LOW);

  // Lee la duración del pulso en el pin del echo
  duration = pulseIn(ECHO_PIN_1, HIGH);
  // Calcula la distancia en centímetros
  distance_cm = duration * SOUND_SPEED / 2;  // Fórmula para convertir la duración del eco a cm
  Serial.print("Sensor 1");
  Serial.print(": Distancia en cm: ");
  Serial.println(distance_cm);
}

void calculateDistance_2() {
  long duration;
  float distance_cm;

  // Genera un pulso corto en el pin del trigger para iniciar la medición
  digitalWrite(TRIGGER_PIN_2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN_2, LOW);

  // Lee la duración del pulso en el pin del echo
  duration = pulseIn(ECHO_PIN_2, HIGH);
  // Calcula la distancia en centímetros
  distance_cm = duration * SOUND_SPEED / 2;  // Fórmula para convertir la duración del eco a cm
  Serial.print("Sensor 2");
  Serial.print(": Distancia en cm: ");
  Serial.println(distance_cm);
}

void calculateDistance_3() {
  long duration;
  float distance_cm;

  // Genera un pulso corto en el pin del trigger para iniciar la medición
  digitalWrite(TRIGGER_PIN_3, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN_3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN_3, LOW);

  // Lee la duración del pulso en el pin del echo
  duration = pulseIn(ECHO_PIN_3, HIGH);
  // Calcula la distancia en centímetros
  distance_cm = duration * SOUND_SPEED / 2;  // Fórmula para convertir la duración del eco a cm
  Serial.print("Sensor 3");
  Serial.print(": Distancia en cm: ");
  Serial.println(distance_cm);
}

void calculateDistance_4() {
  long duration;
  float distance_cm;

  // Genera un pulso corto en el pin del trigger para iniciar la medición
  digitalWrite(TRIGGER_PIN_4, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN_4, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN_4, LOW);

  // Lee la duración del pulso en el pin del echo
  duration = pulseIn(ECHO_PIN_4, HIGH);
  // Calcula la distancia en centímetros
  distance_cm = duration * SOUND_SPEED / 2;  // Fórmula para convertir la duración del eco a cm
  Serial.print("Sensor 4");
  Serial.print(": Distancia en cm: ");
  Serial.println(distance_cm);
}