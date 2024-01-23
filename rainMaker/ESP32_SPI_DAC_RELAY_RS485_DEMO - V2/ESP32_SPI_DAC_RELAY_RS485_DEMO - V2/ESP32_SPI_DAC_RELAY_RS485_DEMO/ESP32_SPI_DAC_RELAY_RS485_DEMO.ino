//#include <SPI.h>
//#include <WiFi.h>
//#include <Modbus.h>
//#include <ModbusMaster.h>
//#include <HardwareSerial.h>
//HardwareSerial MySerial(1);

#include "Header.h"

void setup() {
  Serial.begin(9600);
//  MySerial.begin(9600, SERIAL_8N1, 21, 22);
//  SerialModbus.begin(9600);
//  node1.begin(2, SerialModbus);
  
  pinMode(STATUS, OUTPUT);    // Khai bao chan ngo vao ra
  pinMode(RL_1, OUTPUT);
  pinMode(RL_2, OUTPUT);
  pinMode(RL_3, OUTPUT);
  pinMode(RL_4, OUTPUT);
  pinMode(RL_5, OUTPUT);
  pinMode(RL_6, OUTPUT);
  pinMode(BTN_SET, INPUT_PULLUP);
  pinMode(BTN_BOT, INPUT_PULLUP);

  for(int i = 0; i < 5; i++) {
    RL_1_ON; RL_2_ON; RL_3_ON; RL_4_ON; RL_5_ON; RL_6_ON; STATUS_ON;    
    delay(1000);  
    RL_1_OFF; RL_2_OFF; RL_3_OFF; RL_4_OFF; RL_5_OFF; RL_6_OFF; STATUS_OFF;   
    delay(1000);  
  } 
  
  Timer_Led = millis();
}

void loop()
{ 
  if((millis() - Timer_Led) > 500) {
    VL = ~VL;
    digitalWrite(STATUS, VL);
    Timer_Led = millis();
  }

  int State_SET = digitalRead(BTN_SET);
  int State_BOT = digitalRead(BTN_BOT);

//  Read_TempBT_RS485(0x4700);
  Serial.print(State_SET); Serial.print(State_BOT);
  Serial.print(" __ ");
  Serial.println(Temperature__BT);
  Serial.println();
}
