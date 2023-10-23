/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-relay-module-ac-web-server/
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

const int relay1 = 25;
const int relay2 = 33;
const int relay3 = 32;
const int relay4 = 14;

void setup() {
  Serial.begin(115200);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
}

void loop() {
  //1
  digitalWrite(relay1, LOW);
  Serial.println("Current Flowing");
  delay(500); 
  
  digitalWrite(relay1, HIGH);
  Serial.println("Current not Flowing");
  delay(500);

  //2
  digitalWrite(relay2, LOW);
  Serial.println("Current Flowing");
  delay(500); 
  
  digitalWrite(relay2, HIGH);
  Serial.println("Current not Flowing");
  delay(500);

  //3
  digitalWrite(relay3, LOW);
  Serial.println("Current Flowing");
  delay(500); 
  
  digitalWrite(relay3, HIGH);
  Serial.println("Current not Flowing");
  delay(500);

  //4
  digitalWrite(relay4, LOW);
  Serial.println("Current Flowing");
  delay(500); 
  
  digitalWrite(relay4, HIGH);
  Serial.println("Current not Flowing");
  delay(500);
}