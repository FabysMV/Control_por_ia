#include <analogWrite.h>

class sumo_acciones{
  private:
  //Puente H
const int PH1 = 13;    //Puente H1 PWMB
const int PH2 = 12;   //Puente H2 MB2
const int PH3 = 14;   //Puente H3 MB1
const int PH4 = 2;   //Puente H4 EN
//const int PH5 = 4;    //Puente H5 MA2
//const int PH6 = 2;    //Puente H6 MA1
//const int PH7 = 3;    //Puente H7 PWMA
  //CODIGO PARA PRUEBAS
  const int velocidad=0;
  const int velocidad_instruccion=0;
  public:
/////////////////////////////////////////////////////////
    void avanzar(int velocidad_instruccion){
    
        setVelocidad(velocidad_instruccion);
        digitalWrite(PH4,HIGH);
        //:::Motor A:::
//        digitalWrite(PH6,LOW);
//        digitalWrite(PH5,HIGH);
      
        //:::Motor B:::
        digitalWrite(PH3,LOW);
        digitalWrite(PH2,HIGH);
        
      }
/////////////////////////////////////////////////////////
     void retroceder(int velocidad_instruccion){
     digitalWrite(PH4,HIGH);
        setVelocidad(velocidad_instruccion);
        
    /*    //:::Motor A:::
        digitalWrite(PH6,HIGH);//retroceder
        digitalWrite(PH5,LOW);*/

        //:::Motor B:::
        digitalWrite(PH3,HIGH);//retroceder
        digitalWrite(PH2,LOW);
        delay(100);
      }
/////////////////////////////////////////////////////////
//     void derecha_fast(int velocidad_instruccion){
//      digitalWrite(PH4,HIGH);
//        setVelocidad(velocidad_instruccion);
//        
////        //:::Motor A:::
////        digitalWrite(PH6,LOW);
////        digitalWrite(PH5,HIGH);
//      
//        //:::Motor B::: 
//        digitalWrite(PH3,HIGH);//retroceder
//        digitalWrite(PH2,LOW);
//        
//      }
/////////////////////////////////////////////////////////
//     void izquierda_fast(int velocidad_instruccion){
//     digitalWrite(PH4,HIGH);
//        setVelocidad(velocidad_instruccion);
//        
//        //:::Motor A:::
//        digitalWrite(PH6,HIGH);
//        digitalWrite(PH5,LOW);
//
//        //:::Motor B:::
//        digitalWrite(PH3,LOW);
//        digitalWrite(PH2,HIGH);
//
//      }
///////////////////////////////////////////////////////////
//     void ret_izquierda(int velocidad_instruccion){         //------------>ARREGLAR
//     digitalWrite(PH4,HIGH);
//        setVelocidad(velocidad_instruccion);
//        
//        //:::Motor A:::
//        digitalWrite(PH6,HIGH);
//        digitalWrite(PH5,LOW);
//
//        //:::Motor B:::
//        digitalWrite(PH3,LOW);
//        digitalWrite(PH2,HIGH);
//
//      }
///////////////////////////////////////////////////////////
//     void ret_derecha(int velocidad_instruccion){           //------------>ARREGLAR
//     digitalWrite(PH4,HIGH);
//        setVelocidad(velocidad_instruccion);
//        
//        //:::Motor A:::
//        digitalWrite(PH6,LOW);
//        digitalWrite(PH5,HIGH);
//
//        //:::Motor B:::
//        digitalWrite(PH3,HIGH);//retro
//        digitalWrite(PH2,LOW);
//
//      }
//
///////////////////////////////////////////////////////////
//     void detenerse(){
//     digitalWrite(PH4,HIGH);
//       analogWrite(PH7,0); //velocidad de giro del motor A
//        analogWrite(PH1,0); //velocidad de giro del motor B
//        
//        //:::Motor A:::
//        digitalWrite(PH6,LOW);
//        digitalWrite(PH5,LOW);
//        
//        //:::Motor B:::
//        digitalWrite(PH3,LOW);
//        digitalWrite(PH2,LOW);
//      
//      }
//
//
///////////////////////////////////////////////////////////////
//void ret_izq_90(){
//     digitalWrite(PH4,HIGH);
//        setVelocidad(200); //depende de prueba
//        
//         //:::Motor A:::
//       digitalWrite(PH6,LOW);//Avanza
//        digitalWrite(PH5,LOW);
//      
//        //:::Motor B::: 
//      digitalWrite(PH3,HIGH);
//        digitalWrite(PH2,LOW);
//       delay(350); //depende de cuando lo probemos 
//      }
//
////////////////////////////////////////////////////////////////////
//
// void ret_der_90(){
//     digitalWrite(PH4,HIGH);
//        setVelocidad(200);//depende de prueba
//        
//      //:::Motor A:::
//         digitalWrite(PH6,HIGH);//retroceder
//        digitalWrite(PH5,LOW);
//
//
//        //:::Motor B:::
//          digitalWrite(PH3,LOW);
//        digitalWrite(PH2,LOW);
//        delay(350); //depende de cuando lo probemos 
// }

 //////////////////////////////////////////////////////////////////


 /////////////////////////////////////////////////////////
    void setVelocidad(int velocidad){
        //analogWrite(PH7,velocidad); //velocidad de giro del motor A
        analogWrite(PH1,velocidad); //velocidad de giro del motor B
      }

    void SetUp(){
         
          pinMode(PH1, OUTPUT);
          pinMode(PH2, OUTPUT);
          pinMode(PH3, OUTPUT);
          pinMode(PH4, OUTPUT);
//          pinMode(PH5, OUTPUT);
//          pinMode(PH6, OUTPUT);
//          pinMode(PH7, OUTPUT);
     
      }
/////////////////////////////////////////////////////////
//     void izquierda(int velocidad){
//     digitalWrite(PH4,HIGH);
//        setVelocidad(velocidad); //depende de prueba
//        
//         //:::Motor A:::
//       digitalWrite(PH6,LOW);//Avanza
//        digitalWrite(PH5,LOW);
//      
//        //:::Motor B::: 
//      digitalWrite(PH3,LOW);
//      digitalWrite(PH2,HIGH);
//
//      }
/////////////////////////////////////////////////////////
//     void derecha(int velocidad){
//     digitalWrite(PH4,HIGH);
//        setVelocidad(velocidad);//depende de prueba
//        
//      //:::Motor A:::
//         digitalWrite(PH6,LOW);//retroceder
//        digitalWrite(PH5,HIGH);
//
//
//        //:::Motor B:::
//          digitalWrite(PH3,LOW);
//        digitalWrite(PH2,LOW);
//       
//      }
//      void derecha_cerrado(int velocidad){
//              //:::Motor A:::
//         digitalWrite(PH6,LOW);//avanza
//        digitalWrite(PH5,HIGH);
//
//        //:::Motor B:::
//        digitalWrite(PH3,HIGH);//retroce
//        digitalWrite(PH2,LOW);
//      }
//      void izquierda_cerrado(int velocidad){
//              //:::Motor A:::
//         digitalWrite(PH6,HIGH);//avanza
//        digitalWrite(PH5,LOW); 
//
//             //:::Motor B:::
//        digitalWrite(PH3,LOW);//retroce
//        digitalWrite(PH2,HIGH);    
//      }
        };
  
