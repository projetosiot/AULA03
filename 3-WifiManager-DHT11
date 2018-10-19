/*
  Conexão wifimanager - WebServer
  com Reset DHT11
  IOT na prática com o ESP8266
  https://github.com/esp8266/Arduino/tree/master/doc/esp8266wifi
  http://tomeko.net/online_tools/cpp_text_escape.php?lang=en
*/

#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

#include <SimpleDHT.h>

// Definir o Trigger Pin

#define TRIGGER_PIN D3

const char *ssid = "pelicano"; //Node do SSID a ser transmitido
const char *password = "pelicano"; //Senha

WiFiServer servidor(80);


int pinDHT11 = D1; // Pino onte está conectado o DHT11
SimpleDHT11 dht11(pinDHT11);

void setup() {
  
  Serial.begin(115200);
  pinMode(D4, OUTPUT); // Incializa o D4  como saída

  WiFiManager wifiManager;
  wifiManager.autoConnect(ssid, password);

  /*Start WebServer*/
  servidor.begin();
  
}

void loop() {


  // is configuration portal requested?
  if ( digitalRead(TRIGGER_PIN) == LOW ) {
    WiFiManager wifiManager;
    //reset settings 
    wifiManager.resetSettings();
    delay(10);
    ESP.restart();
  }

   WiFiClient client = servidor.available();
  
  if (client){

      Serial.println("Novo Cliente");

      
      // Incio das Leituras do DHT11
      Serial.println("=================================");
      Serial.println("Leitura do DHT11...");
      
      digitalWrite(D4, HIGH); //Pisca
      delay(500);
      
      //Variáveis
      byte temperatura = 20;
      byte umidade = 50;
      int err = SimpleDHTErrSuccess;

      
      
      if ((err = dht11.read(&temperatura, &umidade, NULL)) != SimpleDHTErrSuccess) {
        Serial.print("Leitua DHT11 com falha, err="); 
        Serial.println(err);
        client.println("<!DOCTYPE HTML>");
        client.println("<html>");
        client.print("Leitua DHT11 com falha, err="); 
        client.println(err);
        client.println("</html>");
        delay(1000);
        return;
      }
      
      Serial.print("Leitura OK: ");
      Serial.print((int)temperatura); Serial.print(" *C, "); 
      Serial.print((int)umidade); Serial.println(" %");

      
      
      digitalWrite(D4, LOW);//Pisca
      delay(500);

      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("<head><meta http-equiv='refresh' content='5'></head><body><h1>ESP8266 - Temperatura e Umidade</h1><h3>Temperatura: ");
      client.println(temperatura);
      client.println("*C</h3><h3>Umidade: ");
      client.println(umidade);
      client.println("%</h3><h3>");
      client.println("</body></html>"); 
      delay(100);
      client.flush();
      client.stop();
      Serial.println("Client disconnected.");    
  }

}



