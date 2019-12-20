/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>

// valeurs pour le WiFi
const char* ssid     = "paveau";
const char* password = "STRAWBERRYFIELDSFOREVER!!!";

// valeurs pour le serveur Web
const char* host     = "api.tom.tools";

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.print("Connexion au WiFi ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);    // On se connecte
  
  while (WiFi.status() != WL_CONNECTED) { // On attend
    delay(500);
    Serial.print(".");
  }

  Serial.println("");  // on affiche les paramÃ¨tres 
  Serial.println("WiFi connecté");  
  Serial.print("Adresse IP du module EPC: ");  
  Serial.println(WiFi.localIP());
  Serial.print("Adresse IP de la box : ");
  Serial.println(WiFi.gatewayIP());
}


void loop() {
  Serial.print("Connexion au serveur : ");
  Serial.println(host);
  
  // On se place dans le rÃ´le ndu  client en utilisant WifiClient
  WiFiClient client;

  // le serveur Web attend tradionnellement sur le port 80
  const int httpPort = 80;

  // Si la connexio Ã©choue ca sera pour la prochaine fois
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  
  // La connexion a rÃ©ussie on forme le chemin 
  String url = String("/hits/");
  
  Serial.print("demande URL: ");
  Serial.println(url);
  
  // On l'envoie au serveur sur plusieurs lignes
  // GET /compteur.php HTTP/1.1
  // Hosts: outils.plido.net
  // Connection: close
  // 
  // La premiÃ¨re ligne prÃ©cise Ã  la fin version du protocole attendu
  // La deuxiÃ¨me rappelle au serveur sous quel nom on l'appelle, en
  // effet, Ã  une mÃªme adresse IP on peut avoire diffÃ©rents serveurs
  // repondant Ã  des noms diffÃ©rents.
  // La troisiÃ¨me ligne indique que le serveur doit fermer la 
  // connexion apres la rÃ©ponse et ne pas attendre d'autres requÃªtes.
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");

  // On attend 10 mili-secondes
  delay(1000);
  
  // On lit les donnÃ©es reÃ§ues, s'il y en a
  while(client.available()){
    String line = client.readStringUntil('\r'); // dÃ©coupe ligne par ligne
    Serial.print(line);
  }

   // plus de donnÃ©es
  Serial.println();
  Serial.println("connexion fermÃ©e");

  delay(30000);
}


