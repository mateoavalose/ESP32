#include <Arduino.h>
#include <WiFi.h>

// Replace with your network credentials
const char* ssid = "";  // Enter SSID here
const char* password = "";  //Enter Password here

// Static IP configuration
IPAddress staticIP(, , , ); // ESP32 static IP
IPAddress gateway(, , , );    // IP Address of your network gateway (router)
IPAddress subnet(, , , );   // Subnet mask
IPAddress primaryDNS(, , , ); // Primary DNS (optional)
IPAddress secondaryDNS(, , , );   // Secondary DNS (optional)

// Setup
/*void setup() {
  Serial.begin(115200);
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("Connected..!");
 
  Serial.print("Current ESP32 IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Gateway (router) IP: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("Subnet Mask: " );
  Serial.println(WiFi.subnetMask());
  Serial.print("Primary DNS: ");
  Serial.println(WiFi.dnsIP(0));
  Serial.print("Secondary DNS: ");
  Serial.println(WiFi.dnsIP(1));
}

void loop() {
}*/

// Test
void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Configuring static IP
  if(!WiFi.config(staticIP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("Failed to configure Static IP");
  } else {
    Serial.println("Static IP configured!");
  }
  
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());  // Print the ESP32 IP address to Serial Monitor
}

void loop() {
  // Nothing to do here
}