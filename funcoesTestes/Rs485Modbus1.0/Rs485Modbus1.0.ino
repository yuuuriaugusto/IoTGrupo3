#include <ModbusMaster.h>
int  pool_size1;
#define RX2 16       //RX
#define TX2 17       //TX
ModbusMaster node1;  //ModbusRTU Relay Slave ID1

int8_t  pool_size;

void setup()
{ 
  Serial.begin(115200);
  Serial1.begin(9200, SERIAL_8N1, RX2, TX2);  //RX2=16,RO ,TX2=17, DI
  node1.begin(1, Serial1);

  Serial.println("successfully node bigining");
  delay(1000);

  pool_size = node1.writeSingleRegister(0x01, 0x0100);
  delay(1000);
  pool_size = node1.writeSingleRegister(0x02, 0x0100);
  delay(1000);
  pool_size = node1.writeSingleRegister(0x03, 0x0100);
  delay(1000);
  pool_size = node1.writeSingleRegister(0x04, 0x0100);
  delay(1000);

  delay(5000);
  Serial.println("Attempting to turn off relay");

  pool_size = node1.writeSingleRegister(0x01, 0x0200);
  delay(1000);
  pool_size = node1.writeSingleRegister(0x02, 0x0200);
  delay(1000);
  pool_size = node1.writeSingleRegister(0x03, 0x0200);
  delay(1000);
  pool_size = node1.writeSingleRegister(0x04, 0x0200);
  delay(1000);

  Serial.println("Attempting to turn on all relays");
  pool_size = node1.writeSingleRegister(0x00, 0x0700);
  delay(5000);

  Serial.println("Attempting to turn off all relays");
  pool_size = node1.writeSingleRegister(0x00, 0x0800);
  delay(5000);
}


void loop()
{
  Serial.println(pool_size);

}