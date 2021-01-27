//theiotprojects.com
#include <Ultrasonic.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <Wire.h>
// Instantiate trig and echo pins for ultrasonic sensors

const int input5 = 5;
const int input4 = 4;


  

Ultrasonic ultrasonic (input5, input4);
// Replace with your network credentials
const char* ssid = "VodafoneTech4byte";
const char* password = "Eternalove65!";
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String getDistance() {
  // Read Distance
  float d = ultrasonic.read();
  if (isnan(d)) {
    Serial.println("Failed to read from HC-SR04 sensor!");
    return "";
  }
  else {
    Serial.println(d);
    return String(d);
  }
}
void setup () {
    pinMode(input5, OUTPUT);
  pinMode(input4, OUTPUT);
  // Serial port for debugging purposes
  Serial.begin (115200);

  // Initialize SPIFFS
  if (! SPIFFS.begin ()) {
    Serial.println ("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for web page
  server.on ("/", HTTP_GET, [] (AsyncWebServerRequest * request) {
    request-> send (SPIFFS, "/index.html");
  });
  server.on ("/distance", HTTP_GET, [] (AsyncWebServerRequest * request) {
    request-> send_P (200, "text / plain", getDistance(). c_str ());
  });

  // start server
  server.begin ();
}
void loop() {
}
