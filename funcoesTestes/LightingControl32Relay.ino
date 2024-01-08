// This sketch controls a board with 16 relays and another with 8 relays. It needs to be run on an Arduino Mega
// Relays are toggled on and off momentary switches in the rooms where the lights are or by centralized keypads.
// The 16 relay board uses Modbus RTU over RS485 serial so a serial to RS485 board needs to be attached to the Mega
// serial port.

//The keypad code in the loop() is currently commented so the code does not check the analog ports. If the keypads are not hooked up the analog ports float and lights turn on and off at random times.

// Complete instructions are available at _________to be added_______
#include "OneButton.h"
#include <AnalogKeypad.h>
#include <ArduinoRS485.h> // ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoModbus.h>
#include <Adafruit_SleepyDog.h>//watchdog timer
int gButtonNum =0; // just to keep track of which button has been pressed because we attach singleClick() to each OneButton instance and can't pass a parameter to it
//gButtonNum gets set when checking the buttons for a click before singleClick() gets called.
const byte direct = 8; //This could be anything other than the values on the two lines below
const byte RS485_1 = 0x01;
const byte RS485_2 = 0x02;
int inputPin =   0;
int oneButtonArrayNum =1;
int outputPin =  2;
int relayType =  3;
int relayNumber =4;
int keypadPin =  5;
int keypadNum =  6;
const uint8_t KeypadAnalogPin1 = A1;
const uint8_t KeypadAnalogPin2 = A2;

//Set up an array to hold input pin, oneButton_I, output pin, relay board type, relay number
const int pins[][7] = {
  {3,0,23,direct,2,KeypadAnalogPin2,1}, //relay board with one Arduino output per relay
  {4,1,24,direct,3,KeypadAnalogPin2,2},
  {5,2,25,direct,4,KeypadAnalogPin2,3},
  {6,3,26,direct,5,KeypadAnalogPin2,4},
  {7,4,27,direct,6,KeypadAnalogPin2,5},
  {8,5,28,direct,7,KeypadAnalogPin2,6},
  {9,6,29,direct,8,KeypadAnalogPin2,7},
  {10,7,30,direct,1,KeypadAnalogPin2,8}, //KeypadAnalogPin2 has 4 more buttons that are not being used

  {31, 8,0,RS485_1,1,KeypadAnalogPin1,1},//relay board #1 with 16 relays and controled over RS485 serial
  {32, 9,0,RS485_1,2,KeypadAnalogPin1,2},
  {33,10,0,RS485_1,3,KeypadAnalogPin1,3},
  {34,11,0,RS485_1,4,KeypadAnalogPin1,4},
  {35,12,0,RS485_1,5,KeypadAnalogPin1,5},
  {36,13,0,RS485_1,6,KeypadAnalogPin1,6},
  {37,14,0,RS485_1,7,KeypadAnalogPin1,7},
  {38,15,0,RS485_1,8,KeypadAnalogPin1,8},
  {39,16,0,RS485_1,9,KeypadAnalogPin1,9},
  {40,17,0,RS485_1,10,KeypadAnalogPin1,10},
  {41,18,0,RS485_1,11,KeypadAnalogPin1,11},
  {42,19,0,RS485_1,12,KeypadAnalogPin1,12},
  {43,20,0,RS485_1,13,KeypadAnalogPin1,13},
  {44,21,0,RS485_1,14,KeypadAnalogPin1,14},
  {45,22,0,RS485_1,15,KeypadAnalogPin1,15},
  {46,23,0,RS485_1,16,KeypadAnalogPin1,16}
  //if a second relay board is added make rows for it also below
  };
  const int numOfInputs = countof(pins);
//-------------keypad stuff -------------------
// the following table is for this Banggood Analog Keypad
// https://usa.banggood.com/5V-Button-Keypad-4x4-Module-Assembled-Keyboard-p-1645007.html?utm_source=googleshopping&utm_medium=cpc_organic&gmcCountry=US&utm_content=minha&utm_campaign=minha-usg-pc&currency=USD&createTmp=1&cur_warehouse=CN
// see the AnalogKeypad_CreateConfig.ino sketch example on how to create this table
// The following are the readings from lowest to highest which is backwards from the silk screened numbers on the keypad.
const int KeypadMap1[] = {0,232,270,324,402,440,460,481,505,565,598,635,677,790,855,932,1023}; 
const int KeypadMap2[] = {0,487,511,538,568,601,639,682,731,787,855,930,1023};

const uint16_t KeypadHoldTimeMs = 5000;

AnalogKeypad keypad1(KeypadAnalogPin1, KeypadMap1, countof(KeypadMap1), KeypadHoldTimeMs);
AnalogKeypad keypad2(KeypadAnalogPin2, KeypadMap2, countof(KeypadMap2), KeypadHoldTimeMs);
// the button event callback
// this will be called when buttons are pressed and released
void ButtonHandler1(const ButtonParam& param)// for the 4x4 keypad
{
  if(param.state == ButtonState_Up && param.button != 0)
  {
    
    int asMarkedBtn = 17 -param.button;
    Serial.println("");
    Serial.print("button marked #");
    Serial.print(asMarkedBtn);
    Serial.println(" on keypad 1 pressed");
    
    for(int i= 0; i < numOfInputs; i++){
      if(pins[i][keypadPin] == KeypadAnalogPin1 && pins[i][keypadNum] == asMarkedBtn){ 
        Serial.println("Found a match for this keypad button");
      gButtonNum = pins[i][oneButtonArrayNum];
      singleClick();
      }
    }
  }
}
void ButtonHandler2(const ButtonParam& param) // for the 3x4 keypad
{
  if(param.state == ButtonState_Up && param.button != 0)
  {
    int asMarkedBtn = 13 -param.button;
    Serial.println("");
    Serial.print("button marked #");
    Serial.print(asMarkedBtn);
    Serial.println(" on keypad 2 pressed");
    for(int i= 0; i < numOfInputs; i++){
      if(pins[i][keypadPin] == KeypadAnalogPin2 && pins[i][keypadNum] == asMarkedBtn){
        Serial.println("Found a match for this keypad button");
      gButtonNum = pins[i][oneButtonArrayNum];
      singleClick();
      }
    }
  }
}
//------------------end keypad stuff --------------

// Setup a new OneButton on pins 1 to 32
// I could not get these set up in a for loop so each is written out.
OneButton button[numOfInputs]{
  OneButton(3, true),//30amp relay for outlets pins 3-10. Pin 2 didn't work
  OneButton(4, true),
  OneButton(5, true),
  OneButton(6, true),
  OneButton(7, true),
  OneButton(8, true),
  OneButton(9, true),
  OneButton(10, true),
  OneButton(31, true),//pins 31 - 46 for 16 relay board that uses Modbus and RS485
  OneButton(32, true),
  OneButton(33, true),
  OneButton(34, true),
  OneButton(35, true),
  OneButton(36, true),
  OneButton(37, true),
  OneButton(38, true),
  OneButton(39, true),
  OneButton(40, true),
  OneButton(41, true),
  OneButton(42, true),
  OneButton(43, true),
  OneButton(44, true),
  OneButton(45, true),
  OneButton(46, true)
  
//  OneButton(, true),//left over pins for second 16 relay board RS485 if one is added
//  OneButton(27, true),
//  OneButton(28, true),
//  OneButton(29, true),
//  OneButton(30, true),
//  OneButton(31, true),
//  OneButton(32, true),
};


// setup code here, to run once:
void setup() {
  Serial.begin(9600);
    // start the Modbus RTU client before trying to print to the serial.
  if (!ModbusRTUClient.begin(9600)) {
    Serial.println("Failed to start Modbus RTU Client!");
    //while (1);
  }
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("Starting up light controls, version 3/3/2021");
  Serial.println("After Modbus begin");
  
  Serial.println("Before attaching OneButtons");
  for(int i=0; i< numOfInputs; i++){
         button[i].attachClick(singleClick);
          // set 80 msec. debouncing time. Default is 50 msec.
          //button[i].setDebounceTicks(80);
         if(pins[i][relayType]== direct){
          //Serial.print("Setting as output pin ");
          //Serial.println(pins[i][outputPin]);
          pinMode(pins[i][outputPin],OUTPUT);//set as outputs
          //If the Arduino is reset this line would turn the outlets off which might not be what is wanted
          //digitalWrite(pins[i][outputPin],LOW); //turn them off at startup
         }else{
          //Serial.print("Not a direct pin, i = ");
          //Serial.println(i);
         }
  }
  //--------------print out configuration array ------------------
    Serial.println("");
    Serial.println("");
    Serial.println("const int pins[][7] = {");
    for(int i= 0; i < numOfInputs; i++){
      Serial.print("  {");
      Serial.print(pins[i][0]);
      Serial.print(",");
      Serial.print(pins[i][1]);
      Serial.print(",");
      Serial.print(pins[i][2]);
      Serial.print(",");
      switch (pins[i][3]) {
        case direct:
          Serial.print("direct");
          break;
        case RS485_1:
          Serial.print("RS485_1");
          break;
        case RS485_2:
          Serial.print("RS485_2");
          break;
       default:
         Serial.print("unknown relay");
         break;
       }
      Serial.print(",");
      Serial.print(pins[i][4]);
      Serial.print(",");

      switch (pins[i][5]) {
        case KeypadAnalogPin1:
          Serial.print("KeypadAnalogPin1");
          break;
        case KeypadAnalogPin2:
          Serial.print("KeypadAnalogPin2");
          break;
       default:
         Serial.print("unknown keypad");
         break;
       }
      Serial.print(",");
      Serial.print(pins[i][6]);
      if(i == numOfInputs -1){
        Serial.println("}"); // the last one there should not have a comma
      }else{
        Serial.println("},");
      }
    }
    Serial.println("};");
    Serial.println("");
    Serial.println("");
    //--------------end of print out configuration array ------------------
    // setup for watchdog timer
     int countdownMS = Watchdog.enable(4000);
  Serial.println("End of setup. Waiting for lights or outlets to be turned on");
  
   
} // end setup
  

// main code here, to run repeatedly: 
void loop() {
  // keep watching the switches
  for(int i=0; i< numOfInputs; i++){
     gButtonNum = i; //This value is used in singleClick() so we know which button was pressed
     button[i].tick();//check buttons 0 to 23
  }
  // uncomment the two lines below to make the keypads work
  // comment the two lines below if the keypads are not hooked up as the floating analog pins will trigger button press events
  //keypad1.loop(ButtonHandler1);//check 4x4 keypad for presses
  //keypad2.loop(ButtonHandler2);//check 4x3 keypad for presses

  // You can implement other code in here or just wait a while 
  delay(0);
   // Reset watchdog with every loop to make sure the sketch keeps running.
    // If you comment out this call watch what happens in about 4 iterations!
    Watchdog.reset();
} // loop


// this function will be called when any of the "numOfInputs" buttons were pressed.
void singleClick() {
  //send message to appropriate relay board to toggle the switch
  //get which button was pressed from the global variable gButtonNum
  
  Serial.print("Switch on pin ");
  Serial.print( pins[gButtonNum][inputPin]);
  Serial.println(" pressed");
  //check the pins array to figure out what to do here
  
  if(pins[gButtonNum][relayType]== direct){
    //toggle the pin associate with this button 
    Serial.print("30 amp relay number ");
    Serial.print(pins[gButtonNum][relayNumber]);
    Serial.println(" toggled");
    Serial.print("Output pin number ");
    Serial.print(pins[gButtonNum][outputPin]);
    Serial.println(" toggled");
    Serial.print("outputPin is ");
    Serial.println(digitalRead(pins[gButtonNum][outputPin]));
    Serial.print("setting outputPin to ");
    Serial.println(!digitalRead(pins[gButtonNum][outputPin]));
    digitalWrite(pins[gButtonNum][outputPin], !digitalRead(pins[gButtonNum][outputPin]));//set this pin to the oppisite of what it current is set at.
    
  } else if(pins[gButtonNum][relayType]== RS485_1 ||pins[gButtonNum][relayType]== RS485_2){
    //Code to send a toggle to a relay on the relay board via Modbus
   byte slaveAddress = pins[gButtonNum][relayType];
   int relayAddress = pins[gButtonNum][relayNumber];
   //0x0300 is the code to toggle the relay
  if (!ModbusRTUClient.holdingRegisterWrite(slaveAddress, relayAddress, 0x0300)) {
    Serial.print("Failed to toggle relay #");
    Serial.println(relayAddress);
    Serial.println(ModbusRTUClient.lastError());
  }
  }else{
    // keypad buttons that are not set up might end up here
    Serial.println("button not associated with a relay board");
  }
  Serial.println("-------done with single click code---------");
} //click
