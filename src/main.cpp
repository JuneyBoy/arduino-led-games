#include <Arduino.h>

const int blueLEDPin = 13;
int blueLEDState = 0;
const int blueButtonPin = PIN_A2;
int blueButtonState = 0;

const int blueLEDPin = 12;
int blueLEDState = 0;
const int blueButtonPin = PIN_A3;
int blueButtonState = 0;

const int blueLEDPin = 11;
int blueLEDState = 0;
const int blueButtonPin = PIN_A4;
int blueButtonState = 0;

const int blueLEDPin = 10;
int blueLEDState = 0;
const int blueButtonPin = PIN_A5;
int blueButtonState = 0;

int piezoPin = 9;

void setup() {
  DDRD = B11111111;
  // pinMode(ledPin, OUTPUT);  // sets the digital pin 13 as output
  // pinMode(inPin, INPUT);    // sets the digital pin 7 as input
}

int flashlight(int inPin, int newState, int oldState, int ledState, int ledPin){
  newState = digitalRead(inPin);

  if(newState && newState != oldState){
    ledState = !ledState;
    digitalWrite(ledPin,ledState);
    delay(100);
  }

  return newState;

}

//Takes hex number 0-F and returns binary # for displaying on 7 segment
int displayNum(int num) {

  //case for display values 0-9
  switch(num) {

    case 0:
    return B11100111;

    case 1:
    return B10000100;

    case 2:
    return B11001011;
    
    case 3:
    return B01101011; 

    case 4:
    return B00101101;

    case 5:
    return B01101110;

    case 6:
    return B11101110;
    
    case 7:
    return B00100011;

    case 8:
    return B11101111;

    case 9:
    return B00101111;

    //A
    case 10:
    return B10101111;

    //B
    case 11:
    return B11101100;

    //C
    case 12:
    return B11000110;

    //D
    case 13:
    return B11101001;

    //E
    case 14:
    return B11001110;

    //F
    case 15:
    return B10001110;

  }

}

void loop() {
  for (int i = 0; i < 16; ++i) {
    PORTD &= 0X00;
    PORTD |= displayNum(i);
    delay(1500);
  }
}