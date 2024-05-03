#include "math.h"
int Y = 0,Yconv;
int C[8] = {-2900, -1000, 1000, -1000, -1000, 1000, 1000, 2900};
double Kn[8];//Arreglo donde se almacenara los valores de K
double ydefuzzden[8];
double ydefuzznum[8];
double yden,ynum;
int ydefuzz;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Valor Y");
  Serial.println(Y);
  if (Y <= 180){//Y=180 hasta 0
    Yconv = Y-180;
  } else {//-180-0
    Yconv = Y-360+180;
  }
  Serial.println("Valor convertido");
  Serial.println(Yconv);
  Fuzzy(Yconv);

  Y = Y+20;

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
  //C's Son los centros de las funciones de pertenencia de los conjuntos de salida
  //C1O1=-2900
  //C202=-1000
  //C303=1000
  //C402=-1000
  //C5O2=-1000
  //C603=1000
  //C703=1000
  //C804=2900
  ynum = 0;
  yden = 0;

  //Se calculan los distintos valores de K, usando los conjuntos de entrada
  for (int i=0; i==1;i++){
    Kn[i] = (exp(pow(-0.00024691358*(angle-(-180)),2)));
  }
  for (int i=2; i==3;i++){
    Kn[i] = (exp(pow(-0.00103305785*(angle-(-45)),2)));
  }
  for (int i=4; i==5;i++){
    Kn[i] = (exp(pow(-0.00103305785*(angle-45),2)));
  }
  for (int i=6; i==7;i++){
    Kn[i] = (exp(pow(-0.00024691358*(angle-180),2)));
  }

  for (int i=0;i<8;i++){
    ydefuzzden[i] = C[i]*Kn[i];//Los valores de el denominador de la y defuzzificada se multiplican por los centros
  }

  for (int i=0;i<8;i++){
    ydefuzznum[i] = Kn[i];// El numerador solo es igual a los valores de Kn
  }

  for (int i=0; i<8; i++){
    yden += ydefuzzden[i];// Sumatoria de el denominador
  }

  for (int i=0; i<8; i++){ // Sumatoria del numerador
    ynum += ydefuzznum[i];
  }

  Serial.println("Ángulo");
  Serial.println(angle);

  for (int i=0;i<8;i++){
    Serial.print("Ydefuzzden ");
    Serial.print(i);
    Serial.println("");
    Serial.println(ydefuzzden[i]);
  }
  for (int i=0;i<8;i++){
    Serial.print("Ydefuzznum ");
    Serial.print(i);
    Serial.println("");
    Serial.println(ydefuzznum[i]);
  }
  //Serial.println(ydefuzzden);
  //Serial.println("ydefuzznum");
  //Serial.println(ydefuzznum);
  Serial.println("Yden");
  Serial.println(yden);
  Serial.println("Ynum");
  Serial.println(ynum);

  ydefuzz = yden/ynum; //Salida defuzzificada final

  Serial.println("Ydefuzz: ");
  Serial.println(ydefuzz);

  if (ydefuzz >=0){ //En función del tiempo, si este es positivo girará en sentido horario 
    Serial.println("Giro Horario");
  } else{//Si por el contrario es negativo, girará en sentido antihorario, y el tiempo ingresado a esta función se hará positivo por medio de abs(), evitando así que el universo colapse
    Serial.println("Giro Antihorario");
  }



}
