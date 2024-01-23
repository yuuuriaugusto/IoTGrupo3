#define INTERRUPTOR_PIN 3  // Pino ao qual o interruptor está conectado
#define RELE_PIN 2         // Pino ao qual o relé está conectado

void setup() {
  pinMode(INTERRUPTOR_PIN, INPUT);
  pinMode(RELE_PIN, OUTPUT);
}


void loop() {
  if (digitalRead(INTERRUPTOR_PIN) == HIGH) {
    // Interruptor ligado
    digitalWrite(RELE_PIN, HIGH);  // Ligar o relé
    while (digitalRead(INTERRUPTOR_PIN) == HIGH) {
      delay(100);
    }
  } else {
    // Interruptor desligado
    digitalWrite(RELE_PIN, LOW);   // Desligar o relé
  }
}