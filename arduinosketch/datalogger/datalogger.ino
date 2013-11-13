#include <SD.h>
#include <EEPROM.h>
#include <MPU6050.h>
#include <I2Cdev.h>
#include <Wire.h>

File myLOG;
MPU6050 accelgyro;

int k = 0;
int n = 1025;
int ax, ay, az;
int gx, gy, gz;
int pushButton = 6;
int led = 5;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.print("Initializing SD card...");
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  pinMode(10, OUTPUT);
  Wire.begin();
  accelgyro.initialize();
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  myLOG = SD.open("LOG.csv", FILE_WRITE);
  accelgyro.setFullScaleAccelRange(3);
}

// the loop routine runs over and over again forever:
void loop() {

  while(n==1025){
    int buttonState = digitalRead(pushButton);
    if (buttonState == 1){
      n = 0;
      digitalWrite(led, HIGH);
      myLOG.print("freefall,ax,ay,az,gx,gy,gz\n");
    }
    delay(3);
  }

  while(n<1024){
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    if ( (ax < 300) and (ay < 300) and (az < 300) ){
      myLOG.print(0);
    }
    else{
      myLOG.print(1);
    }
    myLOG.print(",");
    myLOG.print(ax);
    myLOG.print(",");
    myLOG.print(ay);
    myLOG.print(",");
    myLOG.print(az);
    myLOG.print(",");
    myLOG.print(gx);
    myLOG.print(",");
    myLOG.print(gy);
    myLOG.print(",");
    myLOG.println(gz);
    n = n + 1;
    delay(10);
  }

  myLOG.close();
  digitalWrite(led, LOW);
}

