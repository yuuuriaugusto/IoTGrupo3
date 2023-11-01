#include <SPI.h>
#include <Ethernet.h>

IPAddress ip(192, 168, 1, 100); // Define o endereço IP desejado pode ser o seu
EthernetServer server(80);      // Define a porta HTTP padrão

void ConfigurarEthernet() {
  byte mac[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05}; // Define o endereço MAC exclusivo

  Serial.begin(9600); // Inicializa a porta serial para depuração

  //  inicializar a Ethernet com o endereço MAC se nao deve retorna uma mensagem
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Erro na inicialização da Ethernet. Verifique a conexão e os cabos.");
  } else {
    server.begin(); // Inicializa o servidor na porta 80
    Serial.print("Endereço IP: ");
    Serial.println(Ethernet.localIP()); // Imprime o endereço IP na tela
  }
}

void setup() {
  ConfigurarEthernet(); // Chamada da função de configuração da Ethernet no início do programa
}





//Define um endereço MAC exclusivo para o dispositivo.  deve substituir a matriz mac[] por um endereço 
//MAC exclusivo para o seu dispositivo. Isso é importante para garantir que cada dispositivo na rede tenha um endereço MAC exclusivo.