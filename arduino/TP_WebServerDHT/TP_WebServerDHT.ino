//This example will set up a static IP - in this case 192.168.1.99
 
#include <ESP8266WiFi.h>
#include "DHT.h"

DHT dht;
 
const char* ssid = "PrDIALLO";
const char* password = "PrDIALLO";
 
int ledPin = 5;
WiFiServer server(80);
IPAddress ip(192, 168, 1, 2); // where xx is the desired IP Address
IPAddress gateway(192, 168, 1, 1); // set gateway to match your network
 
void setup() {
  Serial.begin(9600);
  delay(10);
  dht.setup(2); // data pin 2
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  Serial.print(F("Setting static ip to : "));
  Serial.println(ip);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your network
  WiFi.config(ip, gateway, subnet); 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();

  Serial.print("dht ");
  Serial.print(humidity);
  Serial.print(" ");
  Serial.println(temp);
  if (!client) {
    return;
  }
 
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  float humidity = 0.0;
  float temp = 0.0;
  int etat= 0;
  if (request.indexOf("/dht=hu") != -1) {
    //digitalWrite(ledPin, HIGH);
    humidity = dht.getHumidity();
    etat = 0;
  } 
  if (request.indexOf("/dht=te") != -1){
    //digitalWrite(ledPin, LOW);
    temp = dht.getTemperature();
    etat = 1;
  }
 
 
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Dht =  ");
 
  if(etat == 0) {
    client.print("l'humidité ambiante est de :"); 
    client.print(humidity); 
  } else {
    client.print("la temperature est de :");
    client.print(String(temp, 2));
  }
  client.println("<br><br>");
  client.println("Cliquer <a href=\"/dht=hu\">ici</a> pour Humidité<br>");
  client.println("cliquer <a href=\"/dht=te\">ici</a> pour Temperature<br>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
  delay(dht.getMinimumSamplingPeriod());
 
}
