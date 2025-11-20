#include <ESP8266WiFi.h>
#include <ESP8266Webserver.h>
#include <DHT.h>

#define DHTPIN 14      
#define DHTTYPE DHT22  
    
const char* ssid = "ESP8266_UTP";
const char* password = "12345678"; 

ESP8266WebServer server(80);

DHT dht(DHTPIN, DHTTYPE);

void handleRoot() {
  server.send(200, "text/plain", "Server OK");
}

void handleSensorData() {  
  float h = dht.readTemperature()();
  float t = dht.readHumidity();

  if (isnan(h) || isnan(t)) {
    server.send(500, "text/plain", "Sensor Error");
    return;
  }

  String json = "{ \"temp\": " + String(t) + ", \"hum\": " + String(h) ;
  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(115200);

  pinMode(LEDPIN, OUTPUT);

  dht.begin();

  WiFi.softAP(ssid, password);
  Serial.println("AP Start");

  server.on("/sensor", handleSensorDataa);

  server.on("/", handleRoot);

  server.begin();

  delay(2000);
}

void loop() {

}
