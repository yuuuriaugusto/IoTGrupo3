#include <ModbusMaster.h>
#include <SoftwareSerial.h>

#define RS485_DE_PIN  2   // Pino DE (Driver Enable) para controle RS485 na ESP32
#define RS485_RX_PIN  21  // Pino RX do módulo RS485 na ESP32
#define RS485_TX_PIN  22  // Pino TX do módulo RS485 na ESP32
#define RS485_SLAVE_RX_PIN  7   // Pino RX do módulo RS485 no lado escravo
#define RS485_SLAVE_TX_PIN  8   // Pino TX do módulo RS485 no lado escravo

ModbusMaster node;
SoftwareSerial rs485SlaveSerial(RS485_SLAVE_RX_PIN, RS485_SLAVE_TX_PIN);

void setup() {
  Serial.begin(115200);
  pinMode(RS485_DE_PIN, OUTPUT);
  digitalWrite(RS485_DE_PIN, LOW);  // Coloca o módulo RS485 na ESP32 em modo de recepção
  rs485SlaveSerial.begin(9600);  // Inicializa a comunicação RS485 no lado escravo
  node.begin(1, Serial);
}

void loop() {
  // Exemplo de como enviar comandos Modbus para controlar os relés
  controlarRele(1, true);  // Ativar Relé 1
  delay(1000);  // Aguarda 1 segundo
  controlarRele(1, false);  // Desativar Relé 1
  delay(1000);  // Aguarda 1 segundo
}

// Função para enviar comandos Modbus para controlar os relés
void controlarRele(int numeroRele, bool estado) {
  int enderecoRele = numeroRele - 1;  // Os relés são numerados de 1 a 4, mas os arrays começam em 0
  uint8_t valor = estado ? 0xFF : 0x00;  // 0xFF para ligar, 0x00 para desligar

  node.writeSingleCoil(enderecoRele, valor);

  // Envia comando para o lado escravo
  switch (numeroRele) {
    case 1:
      rs485SlaveSerial.write("R1");
      break;
    case 2:
      rs485SlaveSerial.write("R2");
      break;
    case 3:
      rs485SlaveSerial.write("R3");
      break;
    case 4:
      rs485SlaveSerial.write("R4");
      break;
    default:
      // Lidar com erro ou comando inválido
      break;
  }
}