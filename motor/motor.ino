/*
 http://www.bajdi.com
 L9110 motor driver controlling 2 small DC motors 
 */
 
const int AIA = 11;  // (pwm) pin 9 connected to pin A-IA 
const int AIB = 10;  // (pwm) pin 5 connected to pin A-IB 
const int BIA = 8; // (pwm) pin 10 connected to pin B-IA  
const int BIB = 9;  // (pwm) pin 6 connected to pin B-IB 
 
byte speed = 255;  // change this (0-255) to control the speed of the motors 
 
void setup() {
  pinMode(AIA, OUTPUT); // set pins to output
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
}
 
void loop() {
//  a_h();
//  delay(5000);
//  h();
//  delay(1500);
//  stop();
//  delay(1000);
  h();
  delay(4000);
  a_h();
  delay(1500);
  stop();
  delay(1000);

}
 
//void backward()
//{
////  digitalWrite(AIA, 0);
////  digitalWrite(AIB, speed);
//  digitalWrite(BIA, 0);
//  digitalWrite(BIB, speed);
//}
// 
//void forward()
//{
//  digitalWrite(AIA, speed);
//  digitalWrite(AIB, 0);
//  digitalWrite(BIA, speed);
//  digitalWrite(BIB, 0);
//}

void stop(){

  digitalWrite(BIA, 0);
  digitalWrite(BIB, 0);
  digitalWrite(AIB, 0);
  digitalWrite(AIA, 0);
  
  }
  void left1()
{
  digitalWrite(AIA, HIGH);
  digitalWrite(AIB, 0);
//  digitalWrite(BIA, 0);
//  digitalWrite(BIB, HIGH);
}
 
void right1()
{
  digitalWrite(AIA, 0);
  digitalWrite(AIB, HIGH);
//  digitalWrite(BIA, HIGH);
//  digitalWrite(BIB, 0);
}
 
void a_h()
{
  digitalWrite(AIA, HIGH);
  digitalWrite(AIB, 0);
  digitalWrite(BIA, 0);
  digitalWrite(BIB, HIGH);
}
 
void h()
{
  digitalWrite(AIA, 0);
  digitalWrite(AIB, HIGH);
  digitalWrite(BIA, HIGH);
  digitalWrite(BIB, 0);
}
