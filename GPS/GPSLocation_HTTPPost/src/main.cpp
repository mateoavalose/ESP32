#include <Arduino.h>
#include <WiFi.h>
#include <TinyGPS++.h> 

// TinyGPS object
TinyGPSPlus gps;
int GPSBaud = 9600;

// WiFi credentials
const char* ssid = "***REMOVED***";
const char* password = "***REMOVED***";
const char* host = "pi2gps.proxy.beeceptor.com"; // Host without the  HTTPS protocol: pi2gps.proxy.beeceptor.com proxy to sitio-buses-backend.onrender.com
// WiFi client
WiFiClient client;

// Variables
double latitude = 0.0;
double longitude = 0.0;
String data;

// Function declarations
void readGPS();
void postRequest();

void setup() {
  // Start the serial port
  Serial.begin(115200);
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi " + String(ssid));
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  // Start the GPS
  Serial2.begin(GPSBaud);
}

void loop() {
  readGPS(); // Read the GPS data
  postRequest(); // Post the data to the server
  delay(10000); // Wait for 10 seconds
}

// Function definitions
void readGPS() {
  // Read the GPS data
  while (Serial2.available() > 0) {
    if (gps.encode(Serial2.read())) {
      if (gps.location.isValid()) {
        latitude = gps.location.lat();
        longitude = gps.location.lng();
      } else {
        latitude = 0.0;
        longitude = 0.0;
      }
    }
  }
  data = "latitude: " + String(latitude, 6) + ", longitude: " + String(longitude, 6);
  Serial.println(data);
}

void postRequest() {
  if(latitude == 0.0 && longitude == 0.0) {
    Serial.println("No GPS data available");
    return;
  }
  // Send the data to the server
  if (client.connect(host, 80)) { // Connect to the host
    Serial.println("Connected to server");
    // Start the POST request - Start of headers
    client.println("POST /postendpoint/clinica HTTP/1.1"); // /data - /string
    client.println("Host: " + String(host));
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println(); // End of headers
    client.println(data); // Send the actual data
    Serial.println("Data sent to server");
  } else {
    Serial.println("Connection failed");
  }
  client.stop();
  Serial.println("Connection closed\n");
}