#include <ESP8266WiFi.h>

const char* ssid     = "Orange_81139C"; // ssid du reseau wifi
const char* password = "83846847";     // le mot de passe du wifi

const char* host = "192.168.1.101"; //adresse ip du serveur web


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
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;//888;  //le port 80 par defaut
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  else{
    
    
    // This will send the request to the server
    client.print("GET /TP2/traitement.php HTTP/1.1\r\n");
    client.print("Host: ");
    client.print(host);
    client.print("\r\n");
    client.print("Connection: close\r\n\r\n");
    client.println();
   int nbligne=0;
    while(client.available()){
      String line = client.readStringUntil('\r');
      if(nbligne==8)
        Serial.print(line);
      nbligne++;
    }
    client.stop();
    Serial.println();
    Serial.println("closing connection");
  }
  delay(5000);
}

