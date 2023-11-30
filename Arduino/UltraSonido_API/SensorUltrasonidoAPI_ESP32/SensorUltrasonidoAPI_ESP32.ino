#include <WiFi.h>
#include <HTTPClient.h>

#define SOUND_SPEED 0.034  // Velocidad del sonido en el aire ≈ 343 m/s
#define ECHO_PIN 27        // Pin del eco del sensor
#define TRIGGER_PIN 14     // Pin del trigger del sensor

const char *ssid = "LAPTOP-5BUGCH90";
const char *password = "123456789";
const char *serverUrl = "http://192.168.10.2:5000/api/receive_data";

void setup() {
  Serial.begin(115200);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Conectando a WiFi...");
  }

  Serial.println("Conectado a la red WiFi");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

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

  // Construir el JSON
  String json = "{\"SensorValue\":" + String(distance_cm) + "}";

  // Iniciar la conexión HTTP
  HTTPClient http;

  // Configurar la URL y los encabezados
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/json");

  // Realizar l1a solicitud POST
  int httpResponseCode = http.POST(json);

  // Verificar la respuesta del servidor
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    
    String response = http.getString();
    Serial.println(response);
  } else {
    Serial.print("Error en la solicitud. HTTP Response code: ");
    Serial.println(httpResponseCode);
  }

  // Liberar recursos
  http.end();

  // Imprime la distancia en la consola serial
  Serial.print("Distancia en cm: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(5000);
}
