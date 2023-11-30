#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <WiFi.h>
#include <HTTPClient.h>

Adafruit_MPU6050 mpu;

const char *ssid = "LAPTOP-5BUGCH90";
const char *password = "123456789";
const char *serverUrl = "http://172.71.11.76:5000/api/receive_data_G";

void setup(void) {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Conectando a WiFi...");
  }

  Serial.println("Conectado a la red WiFi");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);
}

void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  // Serial.print("Acceleration X: ");
  // Serial.print(a.acceleration.x);
  // Serial.print(", Y: ");
  // Serial.print(a.acceleration.y);
  // Serial.print(", Z: ");
  // Serial.print(a.acceleration.z);
  // Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");
  RequestPost(String(g.gyro.x), String(g.gyro.y), String(g.gyro.z));
  // Serial.print("Temperature: ");
  // Serial.print(temp.temperature);
  // Serial.println(" degC");

  Serial.println("");
  delay(500);
}

void RequestPost(String Data1, String Data2, String Data3){
    // Construir el JSON
  String json = "{\"SensorValue1\":" + String(Data1) + ", \"SensorValue2\":"+ String(Data2) + ", \"SensorValue3\":"+ String(Data3) + "}";

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