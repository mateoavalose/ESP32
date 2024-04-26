#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "***REMOVED***";//"***REMOVED***";
const char* password = "***REMOVED***";//"***REMOVED***";
const char* host = "httprequest.free.beeceptor.com"; // Host without the  HTTPS protocol

WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
}

void loop() {
  // Send the data to the server
  if (client.connect(host, 80)) { // Connect to the host
    Serial.println("Connected to server");
    Serial.print("Enter Data:");
    while (!Serial.available()) {}
    String data = Serial.readStringUntil('\n');
    
    // Start the POST request - Start of headers
    client.println("POST /data HTTP/1.1");
    client.println("Host: " + String(host));
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println(); // End of headers
    client.println(data); // Send the actual data
  } else {
    Serial.println("Connection failed");
  }
  delay(1000);
}