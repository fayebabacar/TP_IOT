#include <ESP8266WiFi.h>

const char* ssid     = "administration"; // ssid du reseau wifi
const char* password = "admintest";     // le mot de passe du wifi

const char* host = "10.2.5.156"; //adresse ip du serveur web


void setup() {
  Serial.begin(115200);
  delay(10);

  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void loop() {
  Serial.print("connecting to ");
  Serial.println(host);
  WiFiClient client;
  const int httpPort = 8888;  //le port 80 par defaut
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  else{

    long valeur = random(500);
    client.print("GET /TP3/index.php?valeur=");
    client.print(String(valeur));
    client.print(" HTTP/1.1\r\n");
    client.print("Host: ");
    client.print(host);
    client.print("\r\n");
    client.print("Connection: close\r\n\r\n");
    client.println();
   
    while(client.available()){
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
    client.stop();
    Serial.println();
    Serial.println("closing connection");
  }
  delay(5000);
}

