#include <SoftwareSerial.h>
#include <Servo.h>
#include <String.h>
#include <Stepper.h>

const int stepsPerRevolution = 2048; 
Stepper myStepper(stepsPerRevolution,13,11,12,10);    

SoftwareSerial BTSerial(9,8);   //bluetooth module Tx:Digital 2 Rx:Digital 3
Servo b1, b2, b3, b4, b5, b6;

int bPin1 = 2, bPin2 = 3, bPin3 = 4, bPin4 = 5, bPin5 = 6, bPin6 = 7;
int angle = 0; // servo position in degrees
String a = "";

void setup()
{
  Serial.begin(9600);
  BTSerial.begin(9600);
  BTSerial.println("AT");
  
  sendCommand("AT");
  sendCommand("AT+ROLE0");
  sendCommand("AT+UUID0xFFE0");
  sendCommand("AT+CHAR0xFFE1");
  sendCommand("AT+NAMEbin");

  b1.attach(bPin1);
  b2.attach(bPin2);
  b3.attach(bPin3);
  b4.attach(bPin4);
  b5.attach(bPin5);
  b6.attach(bPin6);

  initBraille();
}

void loop()
{
    if (BTSerial.available()){
      String data = BTSerial.readString();
      Serial.println(data);
    
      printBraille(char(data[0]), char(data[1]), char(data[2]), char(data[3]), char(data[4]), char(data[5]));
      delay(500);
      
      myStepper.setSpeed(14); 
      myStepper.step(stepsPerRevolution);
      delay(100);
      initBraille();
      Serial.flush();
  }
}

void sendCommand(const char * command){
  Serial.print("Command send :");
  Serial.println(command);
  BTSerial.println(command);
  //wait some time
  delay(100);
  
  char reply[100];
  int i = 0;
  while (BTSerial.available()) {
    reply[i] = BTSerial.read();
    i += 1;
  }
  //end the string
  reply[i] = '\0';
  Serial.print(reply);
  Serial.println("Reply end");
}

void initBraille()
{
  a = "";
  b1.write(30);
  delay(100);
  b2.write(30);
  delay(100);
  b3.write(30);
  delay(100);
  b4.write(30);
  delay(100);
  b5.write(30);
  delay(100);
  b6.write(30);
  delay(100);
}

void printBraille(char dot1, char dot2, char dot3, char dot4, char dot5, char dot6)
{
  if (dot1 == '1')
  {
    b1.write(90);
    delay(100);
  }
  if (dot2 == '1')
  {
    b2.write(90);
    delay(100);
  } 
  if (dot3 == '1')
  {
    b3.write(90);
    delay(100);
  }
  if (dot4 == '1')
  {
    b4.write(90);
    delay(100);
  }
  if (dot5 == '1')
  {
    b5.write(90);
    delay(100);
  }
  if (dot6 == '1')
    b6.write(90);
}



