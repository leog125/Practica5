#include <WiFi.h>
#include <HTTPClient.h>

#define SOUND_SPEED 0.034  // Velocidad del sonido en el aire ≈ 343 m/s
#define ECHO_PIN_1 12      // Pin del trigger del sensor  Ok
#define TRIGGER_PIN_1 13   // Pin del eco del sensor      Ok
#define ECHO_PIN_2 32      // Pin del trigger del sensor  Ok
#define TRIGGER_PIN_2 33   // Pin del eco del sensor      Ok
#define ECHO_PIN_3 2      // Pin del trigger del sensor   Ok
#define TRIGGER_PIN_3 15   // Pin del eco del sensor      Ok
#define ECHO_PIN_4 27      // Pin del trigger del sensor  Ok
#define TRIGGER_PIN_4 14   // Pin del eco del sensor      Ok

const char *ssid = "LAPTOP-5BUGCH90";
const char *password = "123456789";
const char *serverUrl = "http://172.71.11.76:5000/api/receive_data_US4";

void setup() {
  Serial.begin(115200);
  pinMode(TRIGGER_PIN_1, OUTPUT); 
  pinMode(ECHO_PIN_1, INPUT);
  pinMode(TRIGGER_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);
  pinMode(TRIGGER_PIN_3, OUTPUT);
  pinMode(ECHO_PIN_3, INPUT);
  pinMode(TRIGGER_PIN_4, OUTPUT);
  pinMode(ECHO_PIN_4, INPUT);

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
  float sensor1 = calculateDistance_1();
  float sensor2 = calculateDistance_2();
  float sensor3 = calculateDistance_3();
  float sensor4 = calculateDistance_4();
  delay(1000);
  //Serial.println("return1: "+ String(sensor1));
  RequestPost(String(sensor1), String(sensor2), String(sensor3), String(sensor4));

  // delay(200);
  // calculateDistance_2();
  // delay(200);
  // calculateDistance_3();
  // delay(200);
  // calculateDistance_4();
  // delay(200);
}

float calculateDistance_1() {
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
  return distance_cm;
}

float calculateDistance_2() {
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
  return distance_cm;
}

float calculateDistance_3() {
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
  return distance_cm;
}

float calculateDistance_4() {
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
  return distance_cm;
}

void RequestPost(String Data1, String Data2, String Data3, String Data4){
    // Construir el JSON
  String json = "{\"SensorValue1\":" + String(Data1) + ", \"SensorValue2\":"+ String(Data2) + ", \"SensorValue3\":"+ String(Data3) + ", \"SensorValue4\":"+ String(Data4) +"}";

  Serial.println("JSON: "+ json);
  // Iniciar la conexión HTTP
  HTTPClient http;

  // Configurar la URL y los encabezados
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/json");

  // Realizar la solicitud POST
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
}