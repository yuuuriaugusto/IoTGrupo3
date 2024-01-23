
//#include <ArduinoRS485.h> // ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoModbus.h>
byte gSlaveID = 0x01;

void setup() {
  Serial.begin(9600);
  //while (!Serial);

  Serial.println("Modbus RTU demo controlling 16 relay board");

  // start the Modbus RTU client
  if (!ModbusRTUClient.begin(9600)) {
    Serial.println("Failed to start Modbus RTU Client!");
    //while (1);
  }
}

void loop() {
  Serial.println("Turning on all relays");
  for(int i =1;i<=16;i++){
    if (!ModbusRTUClient.holdingRegisterWrite(gSlaveID, i, 0x0100)) {// 0x0100 relay on
      Serial.print("Failed to turn on coil ");
      Serial.println(i);
      Serial.println(ModbusRTUClient.lastError());
    }else{
      Serial.print("Turned on coil ");
      Serial.println(i);
    }
    delay(500);
  }
  delay(1000);// wait for 1 second
  Serial.println("Turning all relays off");
for(int i =1;i<=16;i++){
    if (!ModbusRTUClient.holdingRegisterWrite(gSlaveID, i, 0x0200)) {// 0x0100 relay off
      Serial.print("Failed to turn off coil ");
      Serial.println(i);
      Serial.println(ModbusRTUClient.lastError());
    }else{
      Serial.print("Turned off coil ");
      Serial.println(i);
    }
    delay(500);
  }
  delay(1000);// wait for 1 second
  Serial.println("Toggling relays on or off randomly");
for(int i =1;i<=16;i++){
  int randRelay = random(1, 17);
    if (!ModbusRTUClient.holdingRegisterWrite(gSlaveID, randRelay, 0x0300)) {// 0x0300 toggle relay
      Serial.print("Failed to toggle coil ");
      Serial.println(randRelay);
      Serial.println(ModbusRTUClient.lastError());
    }else{
      Serial.print("Toggled coil ");
      Serial.println(randRelay);
    }
    delay(500);
  }
  delay(1000);
}
