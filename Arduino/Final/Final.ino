

/**
*  @file final.ino
*  @brief PFC de Jorge Regidor - UAH con 
* 
*  Software que recoge la informacion de 12 Sensores MPU6050 mediante y manda la 
*  informacion en forma de quaternion por puerto serie.
* 
*  @author Jorge Regidor
*  @date 10/2013
*  @Version 1.0
*/



/// Libreria I2C de Arduino que es usada por I2Cdev.h
#include "Wire.h"

/// I2Cdev libreria que realiza la comunicacion I2C con el sensor
#include "I2Cdev.h"

/// libreria que hackea el MPU6050 y hace que este calcule y devuelva los quaterniones
#include "MPU6050_6Axis_MotionApps20.h"



/// Inicializa un sensor con la direccion I2C por defecto que es la 0x68
MPU6050 mpu;
/// Inicializa un sensor con la direccion I2C 0x69 que es la unica otra posible (pin ADO activo)
MPU6050 mpu2(0x69);


double ant=0;
/// Vector donde se recogen todos los datos antes de imprimirlos
float datos[48] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};


/// Valores Offset para calibrar los sensores (gx,gy,gz,ax,ay,az)
int Calibrar0[6]= {76,-11,35,-865,2285,1585}; // Sensor0
int Calibrar1[6]= {68,3,23,-1690,1400,1345};  // Sensor1
int Calibrar2[6]= {25,-95,40,-1550,1800,910}; // Sensor2
int Calibrar3[6]= {95,-35,9,1500,-1130,2030}; // Sensor3
int Calibrar4[6]= {-102,-60,50,-1600,1470,1250}; // Sensor4
int Calibrar5[6]= {80,-5,0,-492,-2500,507}; // Sensor4
int Calibrar6[6]= {22,-25,6,-300,392,900}; // Sensor6
//int Calibrar6[6]= {22,-25,6,-300,-1500,2677}; // Sensor6
int Calibrar7[6]= {120,20,-5,-3139,-1388,268}; // Sensor7
//int Calibrar7[6]= {120,20,-5,-3139,-3165,2025}; // Sensor7
int Calibrar8[6]= {120,-75,23,-2328,198,507}; // Sensor8
//int Calibrar8[6]= {120,-75,23,-2328,-1579,2284}; // Sensor8
int CalibrarA[6]= {45,-60,38,-2400,-5655,1050}; // Sensor9
int Calibrar9[6]= {63,115,55,984,-13,1962}; // SensorA
int CalibrarB[6]= {45,0,38,-3324,-211,845}; // SensorB

// Variables de control/estado del DMP
uint8_t devStatus;      ///< Devuelve el estado despues de cada operacion, muestra si hay errores(0 = success, !0 = error)
uint16_t packetSize;    ///< Tamaño de los paquetes del DMP
uint16_t fifoCount;     ///< Contador del FIFOBuffer
uint8_t fifoBuffer[64]; ///< FIFOBUffer es el vector que utiliza el DMP para enviar los datos
uint8_t mpuIntStatus; ///< Recoge las interrupciones que se pudieran producir en el sensor

/// Contenedor del Quaternion [w, x, y, z]
Quaternion q;           



/// Pines de Seleccion
#define Cam_pin 8
#define Cam_pin2 9
#define Cam_inh_1 10
#define Cam_inh_2 11

/// Pines de Test de conexion
#define ENC0_pin 23
#define ENC1_pin 25
#define ENC2_pin 27

#define ENC3_pin 31
#define ENC4_pin 33
#define ENC5_pin 35

#define ENC6_pin 39
#define ENC7_pin 41
#define ENC8_pin 43

#define ENC9_pin 47
#define ENCA_pin 49
#define ENCB_pin 51


// ================================================================
// ===                       FUNCIONES                          ===
// ================================================================


/**
* @brief Inicializa los sensores y su DMP
*
*  La funcion Inicializa los sensores comprobando si la conexion es correcta y despues
*  inicializa el DMP
*
*  @param sensor es el objeto que contiene los datos del sensor que estamos utilizando
*  @param offset es un vector con los datos del Offset para calibrar el sensor
*  @param pin indica cual es el pin que se tiene que encender si todo es correcto
*/
void inicializartodo (MPU6050 sensor, int* offset,int pin)
    
    {

       delay(2);// Espera dos Milisengundos
       sensor.initialize(); ///< Inicializa el sensor                                                                        
       devStatus = sensor.dmpInitialize();///< Inicializa el DMP
    
       /// Si la conexion es correcta enciende el pin de test
       if (sensor.testConnection())  
           {  
               digitalWrite(pin, HIGH);
           }//fin if
   
      /// Si no hay errores al inicializar activa el sensor
      if (devStatus == 0) 
          {
               sensor.setDMPEnabled(true);
               mpuIntStatus = sensor.getIntStatus(); // Recoge si hay interrupciones en el sensor
               packetSize = sensor.dmpGetFIFOPacketSize(); // Recoge el tamaño del paquete
               
          }// fin if
     
      /// Calibra el sensor con datos predefinidos
      sensor.setXGyroOffset(offset[0]);
      sensor.setYGyroOffset(offset[1]);
      sensor.setZGyroOffset(offset[2]);     
      sensor.setXAccelOffset(offset[3]);
      sensor.setYAccelOffset(offset[4]);
      sensor.setZAccelOffset(offset[5]);

      delay(2);//Espera dos milisegundos
      
    }// fin Inicializartodo





/**
*  @brief Recoge los datos del DMP
*
*  La funcion pide al DMP del sensor los datos y este se los devuelve en forma de 
*  quaternion. Despues los guardamos en el vector para imprimirlos
*
*  @param sensor es el objeto que contiene los datos del sensor que estamos utilizando
*  @param pin indica cual es el pin que se tiene que encender si todo es correcto
*  @param num es la posicion de los datos en el vector
*/
void CogerDatos(MPU6050 sensor, int pin, int num)

    {

        /// Si la conexion no se correcta en tiempo de ejecucion apaga el led de test
        if (!sensor.testConnection())  
            { 
                digitalWrite(pin, LOW);
            }

        mpuIntStatus = sensor.getIntStatus();///< Recoge si el sensor tiene interrupciones
        fifoCount = sensor.getFIFOCount();///< Recoge el contador del bus FIFO

        /// si el bus FIFO esta lleno o hay alguna interrupcion se resetea el bus
        if ( (mpuIntStatus & 0x10) || (fifoCount == 1024))
            {
                sensor.resetFIFO();
               // Serial.println("+ ");
            }// final if 
            
            /// sino espera a que el tamaño sea el adecuado y recoge los datos
           else 
               if (mpuIntStatus & 0x02)
                   {
                       
                        Quaternion qu;
                        
                        while (fifoCount < packetSize) fifoCount = sensor.getFIFOCount();
                      // Espera hasta que el tamaño sea el adecuado
                    
                        sensor.getFIFOBytes(fifoBuffer, packetSize); // lee el paquete del bus FIFO
                        fifoCount -= packetSize; // actualiza el fifocount
 
                        /// Saca el quaternion del paquete recivido
                        sensor.dmpGetQuaternion(&qu, fifoBuffer);
            
                        /// Guarda el quaternion en el vector principal
                        datos[num]=qu.w;
                        datos[num+1]=qu.x;
                        datos[num+2]=qu.y;
                        datos[num+3]=qu.z;
                      //  ant=tiem(ant);
                   }// final if y else
              //  else Serial.println("- ");
    }//Final CogerDatos










/**
*  @brief Imprime los datos por Serial
*
*  Recoge el vector de los datos y lo recorre imprimiendo todos los valores
*
*  @param vector contiene todos los datos a imprimir
*  @param tam es el tamaño del vector
*/
void imprimir(float* vector, int tam)
    {
        
        int cont=0;///< Variable contador
        
        
        /// Recorre el vector imprimiendo todo con una coma de separacion
        
        while (cont<tam)
           {
               Serial.print(vector[cont]);
               Serial.print(" , "); 
               cont ++;
           }//Final while
       
       Serial.println(vector[tam]);///< Imprime el ultimo dato con un salto de linea
    
    }// Final imprimir

double tiem(double ante)
{
  double aux;
  aux = (millis() - ante)/1000; 
Serial.println(aux);
return millis();

}





/**
*  @brief Cocola los pines en la posicion correcta
*
*  Segun la posicion que se desee, coloca los pines para poder acceder al sensor deseado
*
*  @param pos indica la posicion a la que se desea acceder
*/
void posicion(int pos)
    {
        
      delay(5);
      /// Segun la posicion coloca los pines de seleccion
        switch (pos) 
            {
   
                case 1:  // Posicion 1
                    digitalWrite(Cam_pin, LOW);
                    digitalWrite(Cam_pin2, LOW);
                    digitalWrite(Cam_inh_1,LOW); // en low activa U1
                    digitalWrite(Cam_inh_2,HIGH); // en High desactiva U2
                break;
  
                case 2:  // Posicion 2
                    digitalWrite(Cam_pin, HIGH);
                    digitalWrite(Cam_pin2, LOW);
                    digitalWrite(Cam_inh_1,LOW); // en low activa U1
                    digitalWrite(Cam_inh_2,HIGH); // en High desactiva U2
                break;
  
                case 3:  // Posicion 3
                    digitalWrite(Cam_pin, LOW);
                    digitalWrite(Cam_pin2, HIGH);
                    digitalWrite(Cam_inh_1,LOW); // en low activa U1
                    digitalWrite(Cam_inh_2,HIGH); // en High desactiva U2
                break;
            
              case 4:  // Posicion 4
                    digitalWrite(Cam_pin, LOW);
                    digitalWrite(Cam_pin2, LOW);
                    digitalWrite(Cam_inh_1,HIGH); // en low activa U1
                    digitalWrite(Cam_inh_2,LOW); // en High desactiva U2
                break;
              case 5:  // Posicion 5
                    digitalWrite(Cam_pin, HIGH);
                    digitalWrite(Cam_pin2, LOW);
                    digitalWrite(Cam_inh_1,HIGH); // en low activa U1
                    digitalWrite(Cam_inh_2,LOW); // en High desactiva U2
                break;   
               case 6:  // Posicion 6
                    digitalWrite(Cam_pin, LOW);
                    digitalWrite(Cam_pin2, HIGH);
                    digitalWrite(Cam_inh_1,HIGH); // en low activa U1
                    digitalWrite(Cam_inh_2,LOW); // en High desactiva U2
                break;    
                
            } // final switch
  
        delay(5);     

    } // final posicion














// ================================================================
// ===                         SETUP                            ===
// ================================================================

void setup() 
    {
    
        Wire.begin();///< Se Inicializa la comunicacion I2C
        
        Serial.begin(115200); ///< Se inicializa la comunicacion Serie
    
        while (!Serial); ///< Espera hasta que se tenga una comunicacion serie

        /// Se definen los pines de seleccion
        pinMode(Cam_pin, OUTPUT);
        pinMode(Cam_pin2, OUTPUT);
        pinMode(Cam_inh_1, OUTPUT);
        pinMode(Cam_inh_2, OUTPUT);
        
        /// Se definen los pines de test
        pinMode(ENC0_pin, OUTPUT);
        pinMode(ENC1_pin, OUTPUT);
        pinMode(ENC2_pin, OUTPUT); 
        pinMode(ENC3_pin, OUTPUT);
        pinMode(ENC4_pin, OUTPUT);
        pinMode(ENC5_pin, OUTPUT);
        pinMode(ENC6_pin, OUTPUT);
        pinMode(ENC7_pin, OUTPUT);
        pinMode(ENC8_pin, OUTPUT);
        pinMode(ENC9_pin, OUTPUT);
        pinMode(ENCA_pin, OUTPUT);
        pinMode(ENCB_pin, OUTPUT);
        
        /// Se inicializan los pines de test apagados
        digitalWrite(ENC0_pin, LOW);
        digitalWrite(ENC1_pin, LOW);
        digitalWrite(ENC2_pin, LOW);  
        digitalWrite(ENC3_pin, LOW);
        digitalWrite(ENC4_pin, LOW);
        digitalWrite(ENC5_pin, LOW);
        digitalWrite(ENC6_pin, LOW);
        digitalWrite(ENC7_pin, LOW);
        digitalWrite(ENC8_pin, LOW);
        digitalWrite(ENC9_pin, LOW);
        digitalWrite(ENCA_pin, LOW);
        digitalWrite(ENCB_pin, LOW);
        
  // -------------------------------  Sensor 0 - Brazo Derecho - Pos 1 -----------------------------------
 
 
        //digitalWrite(Cam_pin, LOW);
        //digitalWrite(Cam_pin2, LOW);
        posicion(1);
    
        inicializartodo(mpu,Calibrar0,ENC0_pin);
    

  // -------------------------------  Sensor 1 - Codo Derecho - Pos 1 ------------------------------------ 
 
 
        //digitalWrite(Cam_pin, HIGH);
        //digitalWrite(Cam_pin2, LOW);
        // posicion(2);
    
        inicializartodo(mpu2,Calibrar1,ENC1_pin);


  // -------------------------------  Sensor 2 - Mano Derecha - Pos 2 ------------------------------------ 
 
 
        //digitalWrite(Cam_pin, LOW);
        //digitalWrite(Cam_pin2, HIGH);
        posicion(2);
    
        inicializartodo(mpu,Calibrar2,ENC2_pin);
    
     

  // -------------------------------  Sensor 3 - Brazo Izquierdo - Pos 2 ------------------------------------- 
  
        inicializartodo(mpu2,Calibrar3,ENC3_pin);
        
        
        
  // -------------------------------  Sensor 4 - Codo izquierdo - Pos 3 ------------------------------------ 
 
 
        //digitalWrite(Cam_pin, LOW);
        //digitalWrite(Cam_pin2, HIGH);
        posicion(3);
    
        inicializartodo(mpu,Calibrar4,ENC4_pin);
    
     

  // -------------------------------  Sensor 3 - Mano Izquierda - Pos 3 ------------------------------------- 
  
        inicializartodo(mpu2,Calibrar5,ENC5_pin);

  
       
  // -------------------------------  Sensor 4 - Codo izquierdo - Pos 3 ------------------------------------ 
 
 

        posicion(4);
    
        inicializartodo(mpu,Calibrar6,ENC6_pin);
        inicializartodo(mpu2,Calibrar7,ENC7_pin);
        
        
         posicion(5);
    
        inicializartodo(mpu,Calibrar8,ENC8_pin);
        inicializartodo(mpu2,CalibrarA,ENCA_pin);
        
        posicion(6); 
        
        inicializartodo(mpu,Calibrar9,ENC9_pin); // solo prueba
        inicializartodo(mpu2,CalibrarB,ENCB_pin);


  } // Final Setup






// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() 
    {        
 
  // -------------------------------  Sensor 0 - Brazo Derecho - Pos 1 ----------------------------------- 
        
        
         //digitalWrite(Cam_pin, LOW);
         //digitalWrite(Cam_pin2, LOW);
          posicion(1);
          
         CogerDatos(mpu,ENC0_pin,0);

     
  // -------------------------------  Sensor 1 - Codo derecho - Pos 1 ------------------------------------ 
     
     
         //digitalWrite(Cam_pin, HIGH);
         //digitalWrite(Cam_pin2, LOW);
        //posicion(2);
         CogerDatos(mpu2,ENC1_pin,4);    
          
          
  // -------------------------------  Sensor 2 - Mano derecha - Pos 2 ------------------------------------ 
     
     
         //digitalWrite(Cam_pin, LOW);
         //digitalWrite(Cam_pin2, HIGH);
         posicion(2);
         
         CogerDatos(mpu,ENC2_pin,8);       
    
    
  // -------------------------------  Sensor 3 - Brazo izquierdo - Pos 2 -------------------------------------- 
 
    
         CogerDatos(mpu2,ENC3_pin,12);  
   
 
         
  // -------------------------------  Sensor 4 - Codo izquierdo - Pos 3 ------------------------------------ 
     
     
         //digitalWrite(Cam_pin, LOW);
         //digitalWrite(Cam_pin2, HIGH);
         posicion(3);
         
         CogerDatos(mpu,ENC4_pin,16);       
    
    
  // -------------------------------  Sensor 5 - Mano izquierda - Pos 3 -------------------------------------- 
 
    
         CogerDatos(mpu2,ENC5_pin,20);  
  // -------------------------------  Sensor 4 - Codo izquierdo - Pos 3 ------------------------------------ 
     
     

         posicion(4);
         
         CogerDatos(mpu,ENC6_pin,24); 
         
         CogerDatos(mpu2,ENC7_pin,28);
         
         
         
          posicion(5);
         
         CogerDatos(mpu,ENC8_pin,32);
         CogerDatos(mpu2,ENCA_pin,36);
        
          posicion(6);
          
         CogerDatos(mpu,ENC9_pin,40);
         CogerDatos(mpu2,ENCB_pin,44); 
  // -----------------------------------------  imprimir -----------------------------------------------------  

         imprimir(datos,47); // 15


         delay(30);   
      
    }// Final loop

