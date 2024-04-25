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
//-----------------------------------------
  h();
  delay(4000);
  a_h();
  delay(1500);
  stop();
  delay(1000);
  //-------------------------------------------
  //_------------------------Test_1: Ambos motores giran en sentido horario juntos durante tres segundos, y se detienen durante 3 segundos
  h();//¿Hacia donde gira?
  delay(3000);
  stop();//¿Qué hace al detenerse, cambia su giro, que tanto?
  delay(3000);
  //Al reinciar el giro horario, ¿vuelve a girar como al principio?
  //----------------------------------------------------------------------------------------------------
  //-------------------------Test_2: Ambos motores giran en sentido antihorario juntos durante 3 segundos, y se detienen durante 3 segundos
  a_h();
  delay(3000);
  stop();
  delay(3000);
  //¿El comportamiento es similar al test_1, solo cambiando la dirección de giro? En principio debería serlo
  //-------------------------------------------------------------------------------------------------------------
  //--------------------------------------------------Test_3: Ambos motores giran en sentido horario, ¿que pasa si para frenar intercalamos entre h() y a_h() un numero x de veces?
  h();
  delay(3000);
  for (int i = 1; i==5; i++){
    a_h();
    delay(200);
    h();
    delay(200);
  }
  //¿Cómo se comporta? ¿Se detiene en seco?¿Sigue girando de forma prolongada y se detiene "Suavemente"?¿hay siquiera alguna diferencia con los test anteriores?
  //¿Variar las veces que se repite el intercalado de los motores hace algo?¿Variar el tiempo corto que hay entre las "oscilaciones" hace algo?
  //-----------------------------------------------------------------------------------------------------------------------
  //--------------------------------Test_4: Similar al test 3, direcciones cambiadas, en principio se debe comportar igual, es más que nada un control para ver que no pase nada raro
  a_h();
  delay(3000);
  for (int i = 1; i==5; i++){
    h();
    delay(200);
    a_h();
    delay(200);
  }
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