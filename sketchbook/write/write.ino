#include <EEPROM.h>
#include <MPU6050.h>
#include <I2Cdev.h>
#include <Wire.h>

MPU6050 accelgyro;

int k = 0;
int n = 1025;
int ax, ay, az;
int gx, gy, gz;
int pushButton = 2;
int led = 13;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  Wire.begin();
  accelgyro.initialize();
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

// the loop routine runs over and over again forever:
void loop() {

  while(n==1025){
    int buttonState = digitalRead(pushButton);
    Serial.println(buttonState);
    if (buttonState == 1){
      n = 0;
      digitalWrite(led, HIGH);
      Serial.println(buttonState);
    }
    delay(3);
  }

  while(n<1024){
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    //Serial.println(ax);
    k = (ax/514)+128;
    Serial.println(k);
    EEPROM.write(n, k);
    n = n + 1;
    //Serial.println(millis()/1000);
    delay(10);
  }

}






