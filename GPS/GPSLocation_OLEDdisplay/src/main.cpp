#include <Arduino.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <Wire.h>
#include <U8g2lib.h>

// UART - NEO-6M GPS
int RXPin = 20;
int TXPin = 21;
// Software serial port
SoftwareSerial gpsSerial(RXPin, TXPin);
// TinyGPS++ object
TinyGPSPlus gps;
int GPSBaud = 9600;

// I2C - OLED Display
U8G2_SH1106_128X64_NONAME_F_HW_I2C display(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Variables
double latitude = 0.0;
double longitude = 0.0;
String date = "N/A";
String time_GPS = "N/A";
int satelliteCount = 0;

// Satellite icon bitmap
const unsigned char satelliteBitMap [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x40, 0x02, 0x00, 0x00, 0x20, 0x04, 0x00, 0x00, 
	0x30, 0x0e, 0x00, 0x00, 0x48, 0x13, 0x00, 0x00, 0x84, 0x31, 0x00, 0x00, 0xc4, 0x59, 0x00, 0x00, 
	0x68, 0x8e, 0x80, 0x00, 0x30, 0xc6, 0x78, 0x00, 0x20, 0x6b, 0x67, 0x00, 0xc0, 0xb1, 0x44, 0x00, 
	0x80, 0x78, 0x48, 0x00, 0x00, 0x2d, 0x30, 0x00, 0x00, 0x16, 0x20, 0x00, 0x00, 0x08, 0x20, 0x00, 
	0x00, 0x08, 0xd0, 0x00, 0xf0, 0x19, 0x68, 0x01, 0x0c, 0x2e, 0x3c, 0x02, 0x02, 0x48, 0x1a, 0x07, 
	0x02, 0xf0, 0xad, 0x09, 0x04, 0x20, 0xc6, 0x18, 0x08, 0x20, 0xe2, 0x2c, 0x18, 0x40, 0x34, 0x47, 
	0x28, 0x40, 0x18, 0x43, 0x48, 0x40, 0x90, 0x25, 0xa8, 0x40, 0xe0, 0x18, 0x1c, 0x41, 0x40, 0x08, 
	0xfc, 0x23, 0x80, 0x04, 0x1c, 0x24, 0x00, 0x03, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 144)
const int bitmapallArray_LEN = 1;
const unsigned char* bitmapallArray[1] = {
	satelliteBitMap
};

// Function
void readGPS();
void displayOLED();

void setup()
{
  // Start the software serial port at the GPS's default baud
  gpsSerial.begin(GPSBaud);

  // OLED
  Wire.begin();
  display.begin();

  // Welcome Message
  display.clearBuffer();
  display.setFont(u8g2_font_ncenB10_tr);
  display.drawStr(0, 24, "Device Startig...");
  display.sendBuffer();
  delay(2000);
}

void loop()
{
  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read())){
      readGPS();
      displayOLED();
    }

  // Check connection to GPS
  if(millis() > 5000 && gps.charsProcessed() < 10) {
    display.clearDisplay();
    do {
    display.setFont(u8g2_font_5x7_tr);
    display.drawStr(0,21,"No GPS Detected");
    display.drawStr(0, 42, "Check connections and");
    display.drawStr(0, 63, "reset board.");
    display.nextPage();
    } while (true);
  }
}

void readGPS() {
  // Location Data
  if(gps.location.isValid()) {
    latitude = gps.location.lat();
    longitude = gps.location.lng();
    satelliteCount = gps.satellites.value();
  } else {
    latitude = 0.0; 
    longitude = 0.0; 
    satelliteCount = 0;
  }
  // Date Data
  if(gps.date.isValid()){
    date = String(gps.date.month()) + "/" + String(gps.date.day()) + "/" + String(gps.date.year());
  } else {
    date = "N/A";
  }
  // Time Data
  if(gps.time.isValid()){
    time_GPS = ((gps.time.hour() < 10)? "0" : "") + String(gps.time.hour()) + ":" + ((gps.time.minute() < 10)? "0" : "") + String(gps.time.minute()) + ":" + ((gps.time.second() < 10)? "0" : "") + String(gps.time.second());
  } else {
    time_GPS = "N/A";
  }
}

void displayOLED() {
  display.clearBuffer(); // Clear display buffer

  // Display satellite icon in top left corner
  display.drawXBMP(0, 0, 32, 32, satelliteBitMap);

  // Display date and time at top in small font
  display.setFont(u8g2_font_profont10_mr);
  display.drawStr(40, 20, time_GPS.c_str());
  display.drawStr(80, 30, date.c_str());

  // Display latitude and longitude in the middle
  display.setFont(u8g2_font_ncenB08_tr);
  display.drawStr(0, 45, "Lat: ");
  if (latitude != 0.0) {
    display.drawStr(35, 45, String(latitude, 6).c_str());
  } else {
    display.drawStr(35, 45, "No Signal");
  }
  display.drawStr(0, 55, "Lon: ");
  if (longitude != 0.0) {
    display.drawStr(35, 55, String(longitude, 6).c_str());
  } else {
    display.drawStr(35, 55, "No Signal");
  }

  // Display satellite count at bottom in small font
  display.setFont(u8g2_font_profont10_mr);
  display.drawStr(0, 62, "Sat: ");
  if (satelliteCount != 0) {
    display.setCursor(20, 62);
    display.print(satelliteCount);
  } else {
    display.drawStr(20, 62, "No satellites found");
  }

  display.sendBuffer(); // Send data to display
}