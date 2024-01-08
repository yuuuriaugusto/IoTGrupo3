#include "WiFi.h"

// define the GPIO connected with Relays and switches
static uint8_t RelayPin1 = 8;  //D23
static uint8_t RelayPin2 = 0;  //D22
static uint8_t RelayPin3 = 6;  //D21
static uint8_t RelayPin4 = 4;  //D19

/* Variable for reading pin status*/
bool toggleState_1 = LOW; 
bool toggleState_2 = LOW; 
bool toggleState_3 = LOW; 
bool toggleState_4 = LOW; 

void setup()
{
  uint32_t chipId = 0;
    
    Serial.begin(115200);
    
    // Set the Relays GPIOs as output mode
    pinMode(RelayPin1, OUTPUT);
    pinMode(RelayPin2, OUTPUT);
    pinMode(RelayPin3, OUTPUT);
    pinMode(RelayPin4, OUTPUT);

    // Write to the GPIOs the default state on booting
    digitalWrite(RelayPin1, !toggleState_1);
    digitalWrite(RelayPin2, !toggleState_2);
    digitalWrite(RelayPin3, !toggleState_3);
    digitalWrite(RelayPin4, !toggleState_4);

    //Service Name
    for(int i=0; i<17; i=i+8) {
      chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
    }

    Serial.printf("\nChip ID:  %d Service Name: %s\n", chipId, service_name);
}

void loop()
{