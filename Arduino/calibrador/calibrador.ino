

/**
*  @file calibrador.ino
*  @brief PFC de Jorge Regidor - UAH con 
* 
*  Software que modifica los valores OffSet de los sensores
*  E imprime los valores crudos

*  @author Jorge Regidor
*  @date 10/2013
*  @Version 1.0
*/

/// Incluye la libreria Wire usada en I2Cdev
#include "Wire.h"

/// Incluye la Libreria I2Cdev usada en MPU6050
#include "I2Cdev.h"

/// Incluye la Libreria MPU6050 
#include "MPU6050.h"

/// inicializamos el objeto 
//MPU6050 accelgyro(0x69);
MPU6050 accelgyro;

/// Incializamos las variables
int16_t ax, ay, az; // variables acelerometro
int16_t gx, gy, gz; // variables giroscopo

// ================================================================
// ===                         SETUP                            ===
// ================================================================


void setup() {
    
    Wire.begin(); ///< Inicializamos la comunicacion I2C

    Serial.begin(57600); ///< Inicializamos la comunicacion Serie

    /// Inicializamos el sensor y lo imprimimos
    accelgyro.initialize();
    Serial.println("Initializing I2C devices...");
   
    /// Confirmamos si la comunicacion es correcta
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

   
   /// Añadimos los valores Offset al sensor
   
                accelgyro.setXGyroOffset(22);  // gx
    		accelgyro.setYGyroOffset(-25); // gy
    		accelgyro.setZGyroOffset(6);   // gz
            
    		accelgyro.setXAccelOffset(-300); // ax
    		accelgyro.setYAccelOffset(-1396);// ay
    		accelgyro.setZAccelOffset(2677); // az

} // fin setup

// ================================================================
// ===                         LOOP                             ===
// ================================================================


void loop() {
    /// Pedimos al sensor los valores raw
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
   
   /// Imprimimos los valores raw
    
   Serial.print(gx); Serial.print("\t"); // gx
   Serial.print(gy); Serial.print("\t"); // gy
   Serial.print(gz); Serial.print("\t"); // gz

   Serial.print(ax); Serial.print("\t"); // ax
   Serial.print(ay); Serial.print("\t"); // ay
   Serial.println(az);                   // az




} // final loop
