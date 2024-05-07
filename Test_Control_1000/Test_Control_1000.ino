#include "math.h"
int Y = 0,Yconv;
int C[6] = {-1000, -410.2, 0, 0, 410.2, 1000};
float Kn[6];//Arreglo donde se almacenara los valores de K
float ydefuzzden[6];
float ydefuzznum[6];
float yden,ynum;
int ydefuzz;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  Y = 5;
  Serial.println("Valor Y");
  Serial.println(Y);
  if (Y <= 180){//Y=180 hasta 0
    Yconv = Y;
  } else {//-180-0
    Yconv = Y-360;
  }
  Serial.println("Valor convertido");
  Serial.println(Yconv);
  Fuzzy(Yconv);

  //Y = Y+20;

  if(Y>360){
    Y=0;
  }
  Serial.println("----------------------------------------------------------------------------------------------");
  delay(2500);


}


//Funciones----------------------------



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
  //if (ydefuzz >=0){ //En función del tiempo, si este es positivo girará en sentido horario 
    //H(ydefuzz);
  //} else{//Si por el contrario es negativo, girará en sentido antihorario, y el tiempo ingresado a esta función se hará positivo por medio de abs(), evitando así que el universo colapse
    //anti_H(abs(ydefuzz));
  //}


}
