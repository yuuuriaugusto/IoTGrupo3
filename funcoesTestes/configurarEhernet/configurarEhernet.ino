#include <Arduino.h>
#include <ETH.h>
#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Iniciando...");

  // Inicializa a Ethernet
  if (ETH.begin() == 0) {
    Serial.println("Erro na inicialização da Ethernet. Verifique a conexão e os cabos.");
    while (1);
  }

  Serial.println("Ethernet conectada com sucesso!");

  // Conecta-se à rede WiFi
  Serial.print("Conectando-se à rede WiFi...");
  if (WiFi.begin("Hyper Net Sebastien_Wi-Fi5", "Lubin175") == WL_CONNECTED) {
    Serial.println(" Conexão WiFi bem-sucedida!");
  } else {
    Serial.println(" Falha na conexão WiFi!");
    while (1);
  }

  // Mostra o endereço IP atribuído
  Serial.print("Endereço IP atribuído: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Endereço IP do Google
  IPAddress googleServer(8, 8, 8, 8);

  // Tenta fazer ping
  Serial.print("Tentando fazer ping para google.com... ");
  if (WiFi.hostByName("google.com", googleServer)) {
    Serial.println("Ping bem-sucedido!");
  } else {
    Serial.println("Falha no ping!");
  }

  // Aguarda 5 segundos antes do próximo ping
  delay(5000);
}




//Define um endereço MAC exclusivo para o dispositivo.  deve substituir a matriz mac[] por um endereço 
//MAC exclusivo para o seu dispositivo. Isso é importante para garantir que cada dispositivo na rede tenha um endereço MAC exclusivo.