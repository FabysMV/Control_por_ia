//////////////////VARIABLES PARA EL IMU//////////////////////////////////////////////////
#include "quaterniones_angles.h"
quaterniones_angles euler;  //objeto de orientacion
int diff = 0;
int Y = 0; //yaw

//::: Variables para el tiempo (aquí no usamos delay)::://
unsigned long tiempo = 0;
unsigned long tiempo_prev = 0;
unsigned long delta_t = 0;
unsigned long delta_a = 0;
unsigned long delta_imu = 0;
boolean flag = false;
boolean flag_imu = false;

/////BOTÓN/////////////
int boton = 2; //pin para BOTON 
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
    R = euler.GetRoll();
    Y = euler.GetYaw();
    
    Serial.print(R);
    Serial.print(',');
    Serial.println(Y);
    }while(estate_b == LOW);

    diff = 359 - Y;

 
  tiempo = millis();  

}

void loop() {
  // put your main code here, to run repeatedly:

}
