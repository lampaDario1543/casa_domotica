#include <SoftwareSerial.h>
int led= 10;

SoftwareSerial BTSerial(0, 1); // RX, TX del modulo HC-05
String message = "";

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  BTSerial.begin(115200);
}

void loop() {
  while (BTSerial.available()) {
    char c = BTSerial.read();
    if(c==' ') {
      Serial.println(message);
      if (message == "Accendi"){
          digitalWrite(led, HIGH);
      }else if(message == "Spegni"){
        digitalWrite(led, LOW);
      }
      message = "";
    }else{
      message += c;
      //Serial.println(message);
    }
  }
}
