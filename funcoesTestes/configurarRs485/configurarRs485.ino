#include <HardwareSerial.h>

// Definição dos pinos
#define RS485_DE_PIN_DEVICE_1 2    // Pino DE (Data Enable) para controle do transceptor RS-485 do Dispositivo 1
#define RS485_DE_PIN_DEVICE_2 3    // Pino DE (Data Enable) para controle do transceptor RS-485 do Dispositivo 2
#define RS485_RX_PIN 16   // Pino RX do ESP32 conectado ao pino A da linha RS-485
#define RS485_TX_PIN 17   // Pino TX do ESP32 conectado ao pino B da linha RS-485
#define ENABLE_DEVICE_1 18 // Pino de habilitação para o dispositivo 1
#define ENABLE_DEVICE_2 19 // Pino de habilitação para o dispositivo 2

// Definindo alguns parâmetros de comunicação RS-485
#define BAUD_RATE 9600

void setup() {
  Serial.begin(9600);

  // Inicializa a comunicação RS-485
  Serial1.begin(BAUD_RATE, SERIAL_8N1, RS485_RX_PIN, RS485_TX_PIN);

  // Inicializa os pinos de habilitação
  pinMode(ENABLE_DEVICE_1, OUTPUT);
  pinMode(ENABLE_DEVICE_2, OUTPUT);

  // Inicializa os pinos DE do transceptor RS-485
  pinMode(RS485_DE_PIN_DEVICE_1, OUTPUT);
  pinMode(RS485_DE_PIN_DEVICE_2, OUTPUT);

  // Define o modo de transmissão (LOW = transmitir, HIGH = receber)
  digitalWrite(RS485_DE_PIN_DEVICE_1, LOW);
  digitalWrite(RS485_DE_PIN_DEVICE_2, LOW);

  // Aguarda um momento para garantir que o Monitor Serial esteja pronto
  delay(2000);

  Serial.println("Iniciando o teste de comunicação RS-485...");
}

void sendCommandAndReceiveResponse(int enablePin, int dePin, const char* command, int waitTime) {
  // Habilita o dispositivo correspondente
  digitalWrite(enablePin, HIGH);

  // Transmite o comando
  digitalWrite(dePin, HIGH);  // Transmissão
  Serial1.write(command);
  Serial1.flush();  // Aguarda a transmissão ser concluída
  digitalWrite(dePin, LOW);   // Recebimento

  // Aguarda o tempo especificado antes de tentar receber uma resposta
  delay(waitTime);

  // Desabilita o dispositivo
  digitalWrite(enablePin, LOW);
}

void loop() {
  // Envia comando para o primeiro dispositivo RS-485 com um tempo de espera de 200ms (pisca rápido)
  Serial.println("Enviando comando para o primeiro dispositivo RS-485 (pisca rápido)...");
  sendCommandAndReceiveResponse(ENABLE_DEVICE_1, RS485_DE_PIN_DEVICE_1, "Comando Rápido para Dispositivo 1", 100);

  // Envia comando para o segundo dispositivo RS-485 com um tempo de espera de 1000ms (pisca mais devagar)
  Serial.println("Enviando comando para o segundo dispositivo RS-485 (pisca mais devagar)...");
  sendCommandAndReceiveResponse(ENABLE_DEVICE_2, RS485_DE_PIN_DEVICE_2, "Comando Mais Devagar para Dispositivo 2", 2000);

  // Aguarda um momento antes de repetir o loop
  //delay(100); // Ajuste conforme necessário
}