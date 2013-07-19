//Blink LED
int pushButton = 2;
int led = 13; //led connected to pin 13

//setup initializes on reset
void setup(){
  pinMode(led, OUTPUT);
  pinMode(pushButton, INPUT);
  Serial.begin(9600);
}

//loop is the program
void loop(){
  int buttonState = digitalRead(pushButton);
  Serial.print(buttonState);
  if (buttonState == 1){
    digitalWrite(led, HIGH);
  }
  else{
    digitalWrite(led, LOW);
  }
  delay(10);
}
