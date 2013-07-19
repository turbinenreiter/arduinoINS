#include <MPU6050.h>
#include <I2Cdev.h>
#include <Wire.h>
#include <Servo.h>

Servo myservo;
MPU6050 accelgyro;

int ax, ay, az;
int gx, gy, gz;
int pushButton = 2;
int led = 13;
int pos = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  pinMode(led, OUTPUT);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  Wire.begin();
  accelgyro.initialize();

}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(pushButton);
  // print out the state of the button:
  Serial.println(buttonState);
  delay(1);        // delay in between reads for stability

  if (buttonState == 1){
    digitalWrite(led, HIGH);
    myservo.write(180);              // tell servo to go to position in variable 'pos' 
    delay(20);
  }
  else{
    digitalWrite(led, LOW);
    myservo.write(0);              // tell servo to go to position in variable 'pos' 
    delay(20);
  }

  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  Serial.print("a/g:\t");
  Serial.print((ax/514));
  Serial.print("\t");
  Serial.print(ay);
  Serial.print("\t");
  Serial.print(az);
  Serial.print("\t");
  Serial.print(gx);
  Serial.print("\t");
  Serial.print(gy);
  Serial.print("\t");
  Serial.println(gz);


}





