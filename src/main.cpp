#include <Arduino.h>

int ledPin = 0;  // LED connected to digital pin 13
int inPin = 7;    // pushbutton connected to digital pin 7
// int buttonPressed = 0;      // variable to store the read value
int ledState = 0;
int oldState = 0;
int newState = 0;

void setup() {
  pinMode(ledPin, OUTPUT);  // sets the digital pin 13 as output
  pinMode(inPin, INPUT);    // sets the digital pin 7 as input
}

void flashlight(){
  newState = digitalRead(inPin);

  if(newState && newState != oldState){
    ledState = !ledState;
    digitalWrite(ledPin,ledState);
    delay(100);
  }

  oldState = newState;

}

void loop() {

}