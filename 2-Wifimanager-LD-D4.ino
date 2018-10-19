/*
  Conexão wifimanager - WebServer
  com Reset
  IOT na prática com o ESP8266
  https://github.com/esp8266/Arduino/tree/master/doc/esp8266wifi
  http://tomeko.net/online_tools/cpp_text_escape.php?lang=en
*/

#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

// Definir o Trigger Pin

#define TRIGGER_PIN D3

const char *ssid = "******"; //Node do SSID a ser transmitido
const char *password = "*****"; //Senha

WiFiServer servidor(80);


void setup() {
  pinMode(TRIGGER_PIN, INPUT);
  pinMode(D4, OUTPUT); // Incializa o ledPin  como saída
  
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configurando o AP ...");
  
  
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
     
      String pagina = "";
    
      /* Página HTML */
    
      pagina += "<!doctype html>\n<html lang=\"pt-BR\">\n    <head>\n        <meta charset=\"utf-8\">\n        <title>Curso ESP8266 na Prática</title>\n    </head>\n\n    <body>\n        <h1>Comando Liga/Desliga LED</h1>\n\t\t<p>LED D4\n\t\t\t<a href=?function=d4_on><button>LIGA</button></a>\n\t\t\t<a href=?function=d4_off><button>DESLIGA</button></a>\n\t\t</p>\n\t\t\t\n    </body>\n</html>";
      client.print(pagina);
      
      String req = client.readStringUntil('\r');
      if (req.indexOf("d4_on") != -1) digitalWrite(D4, LOW);
      if (req.indexOf("d4_off") != -1) digitalWrite(D4, HIGH);
    
      
  }
  
}
