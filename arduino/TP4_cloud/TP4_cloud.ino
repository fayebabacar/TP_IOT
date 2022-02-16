

#include <ESP8266WiFi.h>

const char* ssid = "Orange_8114C6"; // le ssid du reseau
const char* password = "30775084";  // le mot de passe du reseau

WiFiClient client; // le client wifi

// configuration de ThingSpeak 
const int channelID = 272667; 
String writeAPIKey = "2HDJEVINLOKAP9J3"; // la cle d'ecriture (write api key)
const char* server = "api.thingspeak.com";
const int postingInterval = 20 * 1000; // envoyer les donnees toutes les 20 seconde

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  //tant que le client n'est pas connecte on reessai toutes les 500 millisecondes
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {
  if (client.connect(server, 80)) {//connexion au serveur
    
    // Valeur Aleatoire en 0 - 299
    long valeur = random(300);
    // Construct API request body
    String body = "field1=";
           body += String(valeur);
    
    Serial.print("valeur: "); // affiche la valeur sur le moniteur serie
    Serial.println(valeur); 

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + writeAPIKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(body.length());
    client.print("\n\n");
    client.print(body);
    client.print("\n\n");

  }
  client.stop();

  delay(postingInterval);
}
