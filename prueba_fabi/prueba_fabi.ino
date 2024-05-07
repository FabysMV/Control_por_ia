#include <analogWrite.h>
#include "sumo_acciones.h"
#include "fis_header.h"
#include "quaterniones_angles.h"
//***********************************************************************
// Matlab .fis to arduino C converter v2.0.1.25122016                   
// - Karthik Nadig, USA                                                  
// Please report bugs to:                                                
// https://github.com/karthiknadig/ArduinoFIS/issues                     
// If you don't have a GitHub account mail to karthiknadig@gmail.com     
//***********************************************************************


// Number of inputs to the fuzzy inference system
const int fis_gcI = 1;
// Number of outputs to the fuzzy inference system
const int fis_gcO = 1;
// Number of rules to the fuzzy inference system
const int fis_gcR = 6;
int salida;
int Yconv = 0;
FIS_TYPE g_fisInput[fis_gcI];
FIS_TYPE g_fisOutput[fis_gcO];

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
sumo_acciones motor;
//-------------------------------------------------------------------------------------

// Setup routine runs once when you press reset:
void setup()
{
  motor.SetUp();

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

// Loop routine runs over and over again forever:
void loop()
{

  tiempo = millis();

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


      
    // Read Input: input1
    g_fisInput[0] = Yconv;

    g_fisOutput[0] = 0;

    fis_evaluate();

    // Set output vlaue: output1
   salida = g_fisOutput[0];
     if (salida >=0){ //En función del tiempo, si este es positivo girará en sentido horario 
    motor.retroceder(salida);
  } else{//Si por el contrario es negativo, girará en sentido antihorario, y el tiempo ingresado a esta función se hará positivo por medio de abs(), evitando así que el universo colapse
    motor.avanzar(abs(salida));
  }
      Serial.print(salida);
      Serial.print("\t");
      Serial.println(Yconv);
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

//***********************************************************************
// Support functions for Fuzzy Inference System                          
//***********************************************************************
// Gaussian Member Function
FIS_TYPE fis_gaussmf(FIS_TYPE x, FIS_TYPE* p)
{
    FIS_TYPE s = p[0], c = p[1];
    FIS_TYPE t = (x - c) / s;
    return exp(-(t * t) / 2);
}

FIS_TYPE fis_min(FIS_TYPE a, FIS_TYPE b)
{
    return min(a, b);
}

FIS_TYPE fis_max(FIS_TYPE a, FIS_TYPE b)
{
    return max(a, b);
}

FIS_TYPE fis_array_operation(FIS_TYPE *array, int size, _FIS_ARR_OP pfnOp)
{
    int i;
    FIS_TYPE ret = 0;

    if (size == 0) return ret;
    if (size == 1) return array[0];

    ret = array[0];
    for (i = 1; i < size; i++)
    {
        ret = (*pfnOp)(ret, array[i]);
    }

    return ret;
}


//***********************************************************************
// Data for Fuzzy Inference System                                       
//***********************************************************************
// Pointers to the implementations of member functions
_FIS_MF fis_gMF[] =
{
    fis_gaussmf
};

// Count of member function for each Input
int fis_gIMFCount[] = { 4 };

// Count of member function for each Output 
int fis_gOMFCount[] = { 5 };

// Coefficients for the Input Member Functions
FIS_TYPE fis_gMFI0Coeff1[] = { 45, -180 };
FIS_TYPE fis_gMFI0Coeff2[] = { 22, -45 };
FIS_TYPE fis_gMFI0Coeff3[] = { 22, 45 };
FIS_TYPE fis_gMFI0Coeff4[] = { 45, 180 };
FIS_TYPE* fis_gMFI0Coeff[] = { fis_gMFI0Coeff1, fis_gMFI0Coeff2, fis_gMFI0Coeff3, fis_gMFI0Coeff4 };
FIS_TYPE** fis_gMFICoeff[] = { fis_gMFI0Coeff };

// Coefficients for the Output Member Functions
FIS_TYPE fis_gMFO0Coeff1[] = { 65.85, -310 };
FIS_TYPE fis_gMFO0Coeff2[] = { 28.18, 97.83 };
FIS_TYPE fis_gMFO0Coeff3[] = { 65.85, 310 };
FIS_TYPE fis_gMFO0Coeff4[] = { 28.18, -97.83 };
FIS_TYPE fis_gMFO0Coeff5[] = { 4.509, 0 };
FIS_TYPE* fis_gMFO0Coeff[] = { fis_gMFO0Coeff1, fis_gMFO0Coeff2, fis_gMFO0Coeff3, fis_gMFO0Coeff4, fis_gMFO0Coeff5 };
FIS_TYPE** fis_gMFOCoeff[] = { fis_gMFO0Coeff };

// Input membership function set
int fis_gMFI0[] = { 0, 0, 0, 0 };
int* fis_gMFI[] = { fis_gMFI0};

// Output membership function set
int fis_gMFO0[] = { 0, 0, 0, 0, 0 };
int* fis_gMFO[] = { fis_gMFO0};

// Rule Weights
FIS_TYPE fis_gRWeight[] = { 1, 1, 1, 1, 1, 1 };

// Rule Type
int fis_gRType[] = { 1, 1, 1, 1, 1, 1 };

// Rule Inputs
int fis_gRI0[] = { 1 };
int fis_gRI1[] = { 2 };
int fis_gRI2[] = { 3 };
int fis_gRI3[] = { 4 };
int fis_gRI4[] = { 2 };
int fis_gRI5[] = { 3 };
int* fis_gRI[] = { fis_gRI0, fis_gRI1, fis_gRI2, fis_gRI3, fis_gRI4, fis_gRI5 };

// Rule Outputs
int fis_gRO0[] = { 1 };
int fis_gRO1[] = { 4 };
int fis_gRO2[] = { 2 };
int fis_gRO3[] = { 3 };
int fis_gRO4[] = { 5 };
int fis_gRO5[] = { 5 };
int* fis_gRO[] = { fis_gRO0, fis_gRO1, fis_gRO2, fis_gRO3, fis_gRO4, fis_gRO5 };

// Input range Min
FIS_TYPE fis_gIMin[] = { -180 };

// Input range Max
FIS_TYPE fis_gIMax[] = { 180 };

// Output range Min
FIS_TYPE fis_gOMin[] = { -310 };

// Output range Max
FIS_TYPE fis_gOMax[] = { 310 };

//***********************************************************************
// Data dependent support functions for Fuzzy Inference System           
//***********************************************************************
FIS_TYPE fis_MF_out(FIS_TYPE** fuzzyRuleSet, FIS_TYPE x, int o)
{
    FIS_TYPE mfOut;
    int r;

    for (r = 0; r < fis_gcR; ++r)
    {
        int index = fis_gRO[r][o];
        if (index > 0)
        {
            index = index - 1;
            mfOut = (fis_gMF[fis_gMFO[o][index]])(x, fis_gMFOCoeff[o][index]);
        }
        else if (index < 0)
        {
            index = -index - 1;
            mfOut = 1 - (fis_gMF[fis_gMFO[o][index]])(x, fis_gMFOCoeff[o][index]);
        }
        else
        {
            mfOut = 0;
        }

        fuzzyRuleSet[0][r] = fis_min(mfOut, fuzzyRuleSet[1][r]);
    }
    return fis_array_operation(fuzzyRuleSet[0], fis_gcR, fis_max);
}

FIS_TYPE fis_defuzz_centroid(FIS_TYPE** fuzzyRuleSet, int o)
{
    FIS_TYPE step = (fis_gOMax[o] - fis_gOMin[o]) / (FIS_RESOLUSION - 1);
    FIS_TYPE area = 0;
    FIS_TYPE momentum = 0;
    FIS_TYPE dist, slice;
    int i;

    // calculate the area under the curve formed by the MF outputs
    for (i = 0; i < FIS_RESOLUSION; ++i){
        dist = fis_gOMin[o] + (step * i);
        slice = step * fis_MF_out(fuzzyRuleSet, dist, o);
        area += slice;
        momentum += slice*dist;
    }

    return ((area == 0) ? ((fis_gOMax[o] + fis_gOMin[o]) / 2) : (momentum / area));
}

//***********************************************************************
// Fuzzy Inference System                                                
//***********************************************************************
void fis_evaluate()
{
    FIS_TYPE fuzzyInput0[] = { 0, 0, 0, 0 };
    FIS_TYPE* fuzzyInput[fis_gcI] = { fuzzyInput0, };
    FIS_TYPE fuzzyOutput0[] = { 0, 0, 0, 0, 0 };
    FIS_TYPE* fuzzyOutput[fis_gcO] = { fuzzyOutput0, };
    FIS_TYPE fuzzyRules[fis_gcR] = { 0 };
    FIS_TYPE fuzzyFires[fis_gcR] = { 0 };
    FIS_TYPE* fuzzyRuleSet[] = { fuzzyRules, fuzzyFires };
    FIS_TYPE sW = 0;

    // Transforming input to fuzzy Input
    int i, j, r, o;
    for (i = 0; i < fis_gcI; ++i)
    {
        for (j = 0; j < fis_gIMFCount[i]; ++j)
        {
            fuzzyInput[i][j] =
                (fis_gMF[fis_gMFI[i][j]])(g_fisInput[i], fis_gMFICoeff[i][j]);
        }
    }

    int index = 0;
    for (r = 0; r < fis_gcR; ++r)
    {
        if (fis_gRType[r] == 1)
        {
            fuzzyFires[r] = FIS_MAX;
            for (i = 0; i < fis_gcI; ++i)
            {
                index = fis_gRI[r][i];
                if (index > 0)
                    fuzzyFires[r] = fis_min(fuzzyFires[r], fuzzyInput[i][index - 1]);
                else if (index < 0)
                    fuzzyFires[r] = fis_min(fuzzyFires[r], 1 - fuzzyInput[i][-index - 1]);
                else
                    fuzzyFires[r] = fis_min(fuzzyFires[r], 1);
            }
        }
        else
        {
            fuzzyFires[r] = FIS_MIN;
            for (i = 0; i < fis_gcI; ++i)
            {
                index = fis_gRI[r][i];
                if (index > 0)
                    fuzzyFires[r] = fis_max(fuzzyFires[r], fuzzyInput[i][index - 1]);
                else if (index < 0)
                    fuzzyFires[r] = fis_max(fuzzyFires[r], 1 - fuzzyInput[i][-index - 1]);
                else
                    fuzzyFires[r] = fis_max(fuzzyFires[r], 0);
            }
        }

        fuzzyFires[r] = fis_gRWeight[r] * fuzzyFires[r];
        sW += fuzzyFires[r];
    }

    if (sW == 0)
    {
        for (o = 0; o < fis_gcO; ++o)
        {
            g_fisOutput[o] = ((fis_gOMax[o] + fis_gOMin[o]) / 2);
        }
    }
    else
    {
        for (o = 0; o < fis_gcO; ++o)
        {
            g_fisOutput[o] = fis_defuzz_centroid(fuzzyRuleSet, o);
        }
    }
}
