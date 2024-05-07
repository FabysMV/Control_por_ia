//Librerias-------------------------------------------------------
#include "quaterniones_angles.h"
#include "math.h"

//---------------------Variables Varias------------------------
int Yconv = 0;
int C[6] = {-1000, -410.2, 0, 0, 410.2, 1000};
float Kn[6];//Arreglo donde se almacenara los valores de K
float ydefuzzden[6];
float ydefuzznum[6];
float yden,ynum;
int ydefuzz;
//---------------------Variables MPU------------------------------

quaterniones_angles euler;  //objeto de orientacion
int diff = 0;
int Y = 0; //yaw
int R = 0; // roll pero no se usa
//Valores de los angulos a los que se va a posicionar el tracker
//int anglec = 45; //angulo de cenit
int anglez = 0;  //angulo de azimut
//::: Variables para el tiempo (aquí no usamos delay)::://
unsigned long tiempo = 0;
unsigned long tiempo_prev = 0;
unsigned long delta_t = 0;
unsigned long delta_a = 0;
unsigned long delta_imu = 0;
boolean flag = false;
boolean flag_imu = false;

/////BOTÓN/////////////
int boton = 25; //pin para BOTON 
int estate_b = 0;
//----------------------------------Variables Motor----------------------------------
int i = 0;
const int AIA = 34;  // (pwm) pin 9 connected to pin A-IA 
const int AIB = 35;  // (pwm) pin 5 connected to pin A-IB 
const int BIA = 32; // (pwm) pin 10 connected to pin B-IA  
const int BIB = 33;  // (pwm) pin 6 connected to pin B-IB 
 
byte speed = 255;  // change this (0-255) to control the speed of the motors 
//-------------------------------------------------------------------------------------
 
void setup() {
  // put your setup code here, to run once:
  //-------------------Motor cosos-------------------------------------
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
  //----------------------------------------------------------------------
  //-------------------MPU Cosos---------------------------------------
  pinMode(boton, INPUT);
   Serial.begin(115200);
  // inicializamos el IMU
   euler.IMU_inicializar();
   do
   {
    // este es mi método de calibración, ya que el imu cambia los valores
    // de yaw por un rato, pero se estabiliza
    // Presionar el botón hasta que se vea que se ha estabilizado para
    // guardar ese error
    estate_b = digitalRead(boton);
    euler.calculaEulerAngles();
    //R = euler.GetRoll();
    Y = euler.GetYaw();
    
    Serial.print(R);
    Serial.print(',');
    Serial.println(Y);
    }while(estate_b == LOW);

    diff = 359 - Y;

 
  tiempo = millis();  
  //-------------------------------------------------------------------------

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("inicio de programa");
    tiempo = millis(); //se guarda el valor del tiempo en milisegundos
//     Serial.println("");
//     Serial.println(tiempo); 
//     Serial.print(anglez);
//     Serial.print(',');
//     Serial.print(anglec);
//     Serial.print(',');

     euler.calculaEulerAngles(); //obtenemos los valores del imu
     //se guardan en variables los valores de Roll y Yaw        
      // R = euler.GetRoll();
       Y = euler.GetYaw()+diff;
      if (Y >359)
       {Y = Y-360;}

       Y = 360- Y;

     if (Y <= 180){//Y=-180 hasta 0
        Yconv = Y;
      } else {//180-0
        Yconv = Y-360;
      }

//      Serial.print(R);
//      Serial.print(',');
     Serial.print(Y);
      Serial.print("\t");
      Serial.println(Yconv);
      Fuzzy(Yconv);
  

}
//Funciones motor-------------------------------------------------------------

void stop(){
  //delay(500);
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

/// :: MAYOR TIEMPO == MÁS RAPIDEZ :: ////
  void H(int t){
    a_h();
  delay(t); // tiempo en el que se a a quedar funcionando el motor
  //Entre más tiempo sea, más rápido irá el motor. El tiempo lo pasamos como variable
    for (int i = 1; i==2; i++){
     h(); //hace movimiento horario como freno
    delay(650); //lo hace por este tiempo
    a_h(); // y amortiguamos el frenado con este movimiento
    delay(250);
  }
  stop();
  delay(1000);
  }

  
void anti_H(int t) //hace lo mismo que H pero en sentido contrario
{
    h();
    //t = t*-1
  delay(t);
    for (int i = 1; i==2; i++){
     a_h();
    delay(650);
    h();
    delay(250);
  }
  stop();
  delay(1000);
  }


//Función para fuzzy-----------------------------------------------------

void Fuzzy(int angle)
{
  //***************************Valores de K's y Error**********************************
  float e1 = exp(-0.00024691358*pow((angle - (-180)), 2));
  
  float e2 = exp((-0.00103305785*pow((angle-(-45)),2)));
  
  float e3 = exp((-0.00103305785*pow((angle-45),2)));
  
  float e4 = exp((-0.00024691358*pow((angle-180),2)));
  
//************************************************************************************
  //C's Son los centros de las funciones de pertenencia de los conjuntos de salida
  //C1O1=-2900
  //C202=-1000
  //C303=1000
  //C401=-2900
  //C5O2=-1000
  //C602=-1000
  //C702=-1000
  //C803=1000
  //C9O3=1000
  //C10O4=2900
  ynum = 0;
  yden = 0;

  //Se calculan los distintos valores de K, usando los conjuntos de entrada

    //Kn[i] = (exp(pow(-0.00024691358*(angle-(-180)),2)));
    Kn[0] = e1;
    Kn[1] = e2;
    Kn[2] = e2;
    Kn[3] = e3;
    Kn[4] = e3;
    Kn[5] = e4;

  for (int i=0;i<6;i++){
    ydefuzzden[i] = C[i]*Kn[i];//Los valores de el denominador de la y defuzzificada se multiplican por los centros
  }


  Serial.println("Kn");
  for (int i=0; i<6;i++)
  {
    Serial.println(Kn[i],15);
  }

  for (int i=0;i<6;i++){
    ydefuzznum[i] = Kn[i];// El numerador solo es igual a los valores de Kn
  }

  for (int i=0; i<6; i++){
    yden += ydefuzzden[i];// Sumatoria de el denominador
  }

  for (int i=0; i<6; i++){ // Sumatoria del numerador
    ynum += ydefuzznum[i];
  }

  Serial.println("Ángulo");
  Serial.println(angle);

  for (int i=0;i<6;i++){
    Serial.print("Ydefuzzden ");
    Serial.print(i);
    Serial.println("");
    Serial.println(ydefuzzden[i],20);
  }
  for (int i=0;i<6;i++){
    Serial.print("Ydefuzznum ");
    Serial.print(i);
    Serial.println("");
    Serial.println(ydefuzznum[i],20);
  }
  //Serial.println(ydefuzzden);
  //Serial.println("ydefuzznum");
  //Serial.println(ydefuzznum);
  Serial.println("Yden");
  Serial.println(yden,10);
  Serial.println("Ynum");
  Serial.println(ynum,10);

  ydefuzz = yden/ynum; //Salida defuzzificada final

  Serial.println("Ydefuzz: ");
  Serial.println(ydefuzz);

  if (ydefuzz >=0){ //En función del tiempo, si este es positivo girará en sentido horario 
    Serial.println("Giro Horario");
  } else{//Si por el contrario es negativo, girará en sentido antihorario, y el tiempo ingresado a esta función se hará positivo por medio de abs(), evitando así que el universo colapse
    Serial.println("Giro Antihorario");
  }

  Serial.println(ydefuzz);
  if (ydefuzz >=0){ //En función del tiempo, si este es positivo girará en sentido horario 
    H(ydefuzz);
  } else{//Si por el contrario es negativo, girará en sentido antihorario, y el tiempo ingresado a esta función se hará positivo por medio de abs(), evitando así que el universo colapse
    anti_H(abs(ydefuzz));
  }


}
