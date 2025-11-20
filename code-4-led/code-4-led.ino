#include <ESP8266WiFi.h>
#include <ESP8266Webserver.h>   

#define LED1 4   
#define LED2 5    

const char* ssdi = "ESP8266_UTP";        
const char* password = "12345678"; 

ESP8266WebServer server(80);

void homepage() {                   
  server.send(200, "text/plain", "Control 2 LED");
}

void ledOneOn() {                   
  digitalWrite(LED1, LOW);          
  server.send(200, "text/plain", "LED 1 ON");
}

void ledOneOff() {
  digitalWrite(LED1, HIGH);         
  server.send(200, "text/plain", "LED 1 OFF");
}

void ledTwoOn() {
  digitalWrite(LED2, LOW);          
  server.send(200, "text/plain", "LED 2 ON");
}

void ledTwoOff() {
  digitalWrite(LED2, HIGH);         
  server.send(200, "text/plain", "LED 2 OFF");
}

void setup() {
  Serial.begin(115200);

  pinMode(LED1, INPUT_PULLUP);      
  pinMode(LED2, INPUT_PULLUP);      

  WiFi.begin(ssdi, password);       

  Serial.println("Connecting...");
  while (WiFi.status() == WL_CONNECTED) {   
    delay(300);
    Serial.print(".");
  }

  server.on("/", handleRoot);               
  server.on("/ledon1", ledOneOn);           
  server.on("/ledoff1", ledOneOff);

  server.on("/poweron2", ledTwoOn);         
  server.on("/poweroff2", ledTwoOff);

  server.start();                           
}

void loop() {

}