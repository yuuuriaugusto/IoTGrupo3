#include <ArduinoOTA.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>  
#include <WiFi.h>

const char* ssid = "Yuri"; // Coloque a rede WIFI
const char* password = "33236257"; // Aqui vai a senha da rede

const char* host = "ESP32-C6"; // Pode alterar o nome

const char* update_path = "/update";

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando...");

  // Conectar-se à rede WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");

  // Inicializa OTA
  ArduinoOTA.begin();
  ArduinoOTA.setHostname(host);

  // Inicializa o servidor web
  AsyncWebServer server(80);
  server.begin();
  server.on(update_path, HTTP_GET, [](AsyncWebServerRequest *request){
    request->redirect("/update");
  });

  ArduinoOTA.begin();
  Serial.println("OTA pronta");
}

void loop() {
  ArduinoOTA.handle(); //Lida com as atualizações OTA

  // Nosso código principal pode ir aqui
}
