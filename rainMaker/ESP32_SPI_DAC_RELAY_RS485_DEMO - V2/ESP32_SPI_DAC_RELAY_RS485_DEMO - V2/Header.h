
char Output_Array[7] = {15, 12, 13, 32, 33, 25, 14};   // V1

#define RL_1 15
#define RL_2 12
#define RL_3 13
#define RL_4 32
#define RL_5 33
#define RL_6 25

#define STATUS  14
#define BTN_SET 4
#define BTN_BOT 0

#define RL_1_ON  digitalWrite(RL_1, HIGH)
#define RL_2_ON  digitalWrite(RL_2, HIGH)
#define RL_3_ON  digitalWrite(RL_3, HIGH)
#define RL_4_ON  digitalWrite(RL_4, HIGH)
#define RL_5_ON  digitalWrite(RL_5, HIGH)
#define RL_6_ON  digitalWrite(RL_6, HIGH)

#define RL_1_OFF digitalWrite(RL_1, LOW)
#define RL_2_OFF digitalWrite(RL_2, LOW)
#define RL_3_OFF digitalWrite(RL_3, LOW)
#define RL_4_OFF digitalWrite(RL_4, LOW)
#define RL_5_OFF digitalWrite(RL_5, LOW)
#define RL_6_OFF digitalWrite(RL_6, LOW)

#define STATUS_ON   digitalWrite(STATUS, HIGH)
#define STATUS_OFF  digitalWrite(STATUS, LOW)

#define     SerialComputer  Serial
#define     SerialModbus    Serial2

unsigned long Timer_Led = 0;
uint8_t VL = 0;
int state_stt;


float Temperature__BT = 0;
//ModbusMaster node1;

//void Read_TempBT_RS485(uint16_t Address_Temp)
//{
//  uint8_t   result = 0;
//  result = node1.readHoldingRegisters(Address_Temp, 1);
//  if (result == node1.ku8MBSuccess) Temperature__BT = node1.getResponseBuffer(0);
//  delay(10);
//}
