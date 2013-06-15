#include <EEPROM.h>

int m = 0;
int n = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  
  while(n<1024){
    m = EEPROM.read(n);
    n = n + 1;
    Serial.println(m);
  }

}
