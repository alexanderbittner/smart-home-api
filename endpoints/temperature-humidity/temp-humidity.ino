#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHT.h"
#include "wifi-credentials.h"
#define DHTTYPE DHT22

const char *ssid = WIFISSID;
const char *password = WIFIPASSWORD;

ESP8266WebServer server(80);

uint8_t DHTPin = D2;

// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);
 
void setup() {
  //initialize Serial console
  Serial.begin(115200);
  delay(100);

  //initialize DHT22 sensor
  pinMode(DHTPin, INPUT);
  dht.begin();              

  //initialize WiFi connection, print status updates to serial monitor
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("IP: ");  Serial.println(WiFi.localIP());

  //initialize web server paths, then start the server
  server.on("/", handle_root);
  server.on("/state", handle_state);
  server.onNotFound(handle_notFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

//the root directory redirects to /state
void handle_root() {
  server.sendHeader("Location","/state");
  server.send(301, "text/plain", "");
}

//returns the current temperature and humidity in json format.
void handle_state() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  String message = "{";
  
  message += "\n  \"temperature\":{\n";
  message += "    \"value\": ";
  message += temperature;
  message += "\n  },";

  message += "\n  \"humidity\":{\n";
  message += "    \"value\": ";
  message += humidity;
  message += "\n  }";
  
  message += "\n}";
  server.send(200, "application/json", message);
}

//return a 404 page
void handle_notFound(){
  server.send(404, "text/plain", "Not found");
}