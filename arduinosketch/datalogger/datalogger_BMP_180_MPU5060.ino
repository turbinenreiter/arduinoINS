#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#include <SD.h>
#endif
/* This driver uses the Adafruit unified sensor library (Adafruit_Sensor),
   which provides a common 'type' for sensor data and some helper functions.
   
   To use this driver you will also need to download the Adafruit_Sensor
   library and include it in your libraries folder.

   You should also assign a unique ID to this sensor for use with
   the Adafruit Sensor API so that you can identify this particular
   sensor in any data logs, etc.  To assign a unique ID, simply
   provide an appropriate value in the constructor below (12345
   is used by default in this example).
   
   Connections
   ===========
   Connect SCL to analog 5
   Connect SDA to analog 4
   Connect VDD to 3.3V DC
   Connect GROUND to common ground
    
   History
   =======
   2013/JUN/17  - Updated altitude calculations (KTOWN)
   2013/FEB/13  - First version (KTOWN)
*/
MPU6050 accelgyro;   
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);
int16_t ax, ay, az;
int16_t gx, gy, gz;
unsigned long time;
#define OUTPUT_READABLE_ACCELGYRO
const int chipSelect = 4;
File dataFile;
int i =0;
/**************************************************************************/
/*
    Displays some basic information on this sensor from the unified
    sensor API sensor_t type (see Adafruit_Sensor for more information)
*/
/**************************************************************************/


/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************/
void setup(void) 
{
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif
  Serial.begin(9600);
  
  
  /* Initialise the sensor */
  if(!bmp.begin())
  {
    /* There was a problem detecting the BMP085 ... check your connections */
    Serial.print("BMP180 failed");
    while(1);
  }
  Serial.println("Initializing I2C devices...");
    accelgyro.initialize();
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  Serial.print("Initializing SD card...");
  pinMode(SS, OUTPUT);
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1) ;
  }
  Serial.println("card initialized.");
  dataFile = SD.open("log.csv", FILE_WRITE);
  if (! dataFile) {
    Serial.println("error opening log.csv");
    // Wait forever since we cant write data
    while (1) ;
  }
  /* Display some basic information on this sensor */
  //displaySensorDetails();
}

/**************************************************************************/
/*
    Arduino loop function, called once 'setup' is complete (your own code
    should go here)
*/
/**************************************************************************/
void loop(void) 
{
  /* Get a new sensor event */ 
  sensors_event_t event;
  bmp.getEvent(&event);
 
  /* Display the results (barometric pressure is measure in hPa) */
  if (event.pressure)
  { 
    
    time = millis();
    int hPa = event.pressure;
    float temperature;
    bmp.getTemperature(&temperature);
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    int stemp=temperature;
    
    
    /*char PufferChar1[15];
    dtostrf(temperature, 5, 2,PufferChar1);
    Serial.println(PufferChar1);*/
    /*int stemperature = temperature;
    
    String data = String(time+","+stemperature);
    
    Serial.println(data);*/
     String dataString = "";

  // read three sensors and append to the string:
  
    
    dataString += String(time);
    dataString += ",";
    dataString += String(hPa);
    dataString += ",";
    dataString += String(stemp);
    dataString += ",";
    //#ifdef OUTPUT_READABLE_ACCELGYRO
    dataString += String(ax);
    dataString += ",";
    dataString += String(ay);
    dataString += ",";
    dataString += String(az);
    dataString += ",";
    dataString += String(gx);
    dataString += ","; 
    dataString += String(gy);
    dataString += ",";
    dataString += String(gz);   
    //#endif
    dataFile.println(dataString);
    Serial.println(dataString);
    
    if(i=25){
      dataFile.flush();
      i=0;
    }
    i++;
    
    

    
  }
  else
  {
    Serial.println("Sensor error");
  }
  delay(10);
}
