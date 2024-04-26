/*
 http://www.bajdi.com
 L9110 motor driver controlling 2 small DC motors 
 */
 int i = 0;
const int AIA = 11;  // (pwm) pin 9 connected to pin A-IA 
const int AIB = 10;  // (pwm) pin 5 connected to pin A-IB 
const int BIA = 8; // (pwm) pin 10 connected to pin B-IA  
const int BIB = 9;  // (pwm) pin 6 connected to pin B-IB 
 
byte speed = 255;  // change this (0-255) to control the speed of the motors 
 
void setup() {
//  pinMode(AIA, OUTPUT); // set pins to output
//  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
  Serial.begin(9600);
}
 
void loop() {
//  a_h();
//  delay(5000);
//  h();
//  delay(1500);
//  stop();
//  delay(1000);
//-----------------------------------------
//// ::: MOVIMIENTO UN POCO MÁS CONTROLADO, SOLO QUE SE REGRESA :: //////////
/*
  delay(1000);
  anti_H();
  Serial.println("Antihorario");
  //delay(500);
  stop();
  Serial.println("STOPU");
  //delay(500);
  H();
  */
  //g_180();
  //g_90();

  H(4000);
  
  


////////////////////////////////////////////////////////////////////////////////////  
//  Serial.println("Esperando 5 segundos");
//  do{
//      h();
//      delay(1500);
//      stop();
//      delay(100);
//      a_h();
//      delay(1000);
//      stop();
//      delay(1500);
//      i = i +1;
//    }while(i = 20);
//     i = 0;


  //-------------------------------------------
  //_------------------------Test_1: Ambos motores giran en sentido horario juntos durante tres segundos, y se detienen durante 3 segundos
//  Serial.println("Ambos motores giran en sentido horario juntos durante tres segundos, y se detienen durante 3 segundos");
//  h();//¿Hacia donde gira?
//  delay(5000);
//  stop();//¿Qué hace al detenerse, cambia su giro, que tanto?
//  delay(1500);
//  //Al reinciar el giro horario, ¿vuelve a girar como al principio?
//  //----------------------------------------------------------------------------------------------------
//  //-------------------------Test_2: Ambos motores giran en sentido antihorario juntos durante 3 segundos, y se detienen durante 3 segundos
//  stop();
//  delay(5000);
//  Serial.println("Esperando 5 segundos");
//  Serial.println("Ambos motores giran en sentido antihorario juntos durante 3 segundos, y se detienen durante 3 segundos");
//  a_h();
//  delay(3000);
//  stop();
//  delay(3000);
//  //¿El comportamiento es similar al test_1, solo cambiando la dirección de giro? En principio debería serlo
//  //-------------------------------------------------------------------------------------------------------------
//  //--------------------------------------------------Test_3: Ambos motores giran en sentido horario, ¿que pasa si para frenar intercalamos entre h() y a_h() un numero x de veces?
//  stop();
//  delay(5000);
//  Serial.println("Esperando 5 segundos");
//  Serial.println("Ambos motores giran en sentido horario, ¿que pasa si para frenar intercalamos entre h() y a_h() un numero x de veces?");
//  h();
//  delay(3000);
//  for (int i = 1; i==5; i++){
//    a_h();
//    delay(200);
//    h();
//    delay(200);
//  }
//  //¿Cómo se comporta? ¿Se detiene en seco?¿Sigue girando de forma prolongada y se detiene "Suavemente"?¿hay siquiera alguna diferencia con los test anteriores?
//  //¿Variar las veces que se repite el intercalado de los motores hace algo?¿Variar el tiempo corto que hay entre las "oscilaciones" hace algo?
//  //-----------------------------------------------------------------------------------------------------------------------
//  //--------------------------------Test_4: Similar al test 3, direcciones cambiadas, en principio se debe comportar igual, es más que nada un control para ver que no pase nada raro
//  stop();
//  delay(5000);
//  Serial.println("Esperando 5 segundos");
//  Serial.println("Similar al test 3, direcciones cambiadas, en principio se debe comportar igual, es más que nada un control para ver que no pase nada raro");
//  a_h();
//  delay(3000);
//  for (int i = 1; i==5; i++){
//    h();
//    delay(200);
//    a_h();
//    delay(200);
//  }
}
 



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stop(){
  delay(500);
  digitalWrite(BIA, 0);
  digitalWrite(BIB, 0);
  digitalWrite(AIB, 0);
  digitalWrite(AIA, 0);
  
  }

 
void a_h()
{
//  digitalWrite(AIB, HIGH);
//  digitalWrite(AIA, 0);
  digitalWrite(BIA, 0);
  digitalWrite(BIB, HIGH);
}
 
void h()
{
//  digitalWrite(AIB, 0);
//  digitalWrite(AIA, HIGH);
  digitalWrite(BIA, HIGH);
  digitalWrite(BIB, 0);
}


  void H(int t){
    a_h();
  delay(t); // tiempo en el que se a a quedar funcionando el motor
  //Entre más tiempo sea, más rápido irá el motor. El tiempo lo pasamos como variable
    for (int i = 1; i==3; i++){
     h(); //hace movimiento horario como freno
    delay(850); //lo hace por este tiempo
    a_h(); // y amortiguamos el frenado con este movimiento
    delay(250);
  }
  stop();
  delay(1000);
  }

  
void anti_H(int t) //hace lo mismo que H pero en sentido contrario
{
    h();
  delay(t);
    for (int i = 1; i==3; i++){
     a_h();
    delay(850);
    h();
    delay(250);
  }
  stop();
  delay(1000);
  }




  void H(int t){
    a_h();
  delay(t); // tiempo en el que se a a quedar funcionando el motor
  //Entre más tiempo sea, más rápido irá el motor. El tiempo lo pasamos como variable
    for (int i = 1; i==3; i++){
     h(); //hace movimiento horario como freno
    delay(850); //lo hace por este tiempo
    a_h(); // y amortiguamos el frenado con este movimiento
    delay(250);
  }
  stop();
  delay(1000);
  }
