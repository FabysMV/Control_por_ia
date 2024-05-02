//////////////////VARIABLES PARA EL IMU//////////////////////////////////////////////////
#include "quaterniones_angles.h"
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
int boton = 14; //pin para BOTON 
int estate_b = 0;


void setup() {
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

}

void loop() {
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

//      Serial.print(R);
//      Serial.print(',');
      Serial.print(Y);
      Serial.print("\t");
  
  

}
