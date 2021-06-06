#include <Arduino.h>
#include <math.h>
/**
🥺
⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠛⠛⠛⠋⠉⠈⠉⠉⠉⠉⠛⠻⢿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⡿⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⢿⣿⣿⣿⣿
⣿⣿⣿⣿⡏⣀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠙⢿⣿⣿
⣿⣿⣿⢏⣴⣿⣷⠀⠀⠀⠀⠀⢾⣿⣿⣿⣿⣿⣿⡆⠀⠀⠀⠀⠀⠀⠀⠈⣿⣿
⣿⣿⣟⣾⣿⡟⠁⠀⠀⠀⠀⠀⢀⣾⣿⣿⣿⣿⣿⣷⢢⠀⠀⠀⠀⠀⠀⠀⢸⣿
⣿⣿⣿⣿⣟⠀⡴⠄⠀⠀⠀⠀⠀⠀⠙⠻⣿⣿⣿⣿⣷⣄⠀⠀⠀⠀⠀⠀⠀⣿
⣿⣿⣿⠟⠻⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠶⢴⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀⣿
⣿⣁⡀⠀⠀⢰⢠⣦⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⣿⣿⣿⣿⣿⡄⠀⣴⣶⣿⡄⣿
⣿⡋⠀⠀⠀⠎⢸⣿⡆⠀⠀⠀⠀⠀⠀⣴⣿⣿⣿⣿⣿⣿⣿⠗⢘⣿⣟⠛⠿⣼
⣿⣿⠋⢀⡌⢰⣿⡿⢿⡀⠀⠀⠀⠀⠀⠙⠿⣿⣿⣿⣿⣿⡇⠀⢸⣿⣿⣧⢀⣼
⣿⣿⣷⢻⠄⠘⠛⠋⠛⠃⠀⠀⠀⠀⠀⢿⣧⠈⠉⠙⠛⠋⠀⠀⠀⣿⣿⣿⣿⣿
⣿⣿⣧⠀⠈⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠟⠀⠀⠀⠀⢀⢃⠀⠀⢸⣿⣿⣿⣿
⣿⣿⡿⠀⠴⢗⣠⣤⣴⡶⠶⠖⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡸⠀⣿⣿⣿⣿
⣿⣿⣿⡀⢠⣾⣿⠏⠀⠠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠉⠀⣿⣿⣿⣿
⣿⣿⣿⣧⠈⢹⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣿⣿⣿⣿
⣿⣿⣿⣿⡄⠈⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⣾⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣦⣄⣀⣀⣀⣀⠀⠀⠀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡄⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀⠀⠀⠙⣿⣿⡟⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀⠁⠀⠀⠹⣿⠃⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⢐⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⠿⠛⠉⠉⠁⠀⢻⣿⡇⠀⠀⠀⠀⠀⠀⢀⠈⣿⣿⡿⠉⠛⠛⠛⠉⠉
⣿⡿⠋⠁⠀⠀⢀⣀⣠⡴⣸⣿⣇⡄⠀⠀⠀⠀⢀⡿⠄⠙⠛⠀⣀⣠⣤⣤⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀
 **/
//p12 on 74HC595
const int latchPin = 3;
//p11 on 74HC595
const int clockPin = 4;
//p14 on 74HC595
const int dataPin = 2;

const int numOfLeds = 4;

const int blueLEDPin = 11;
int blueLEDState = 0;
const int blueButtonPin = PIN_A0;
int blueButtonState = 0;

const int greenLEDPin = 10;
int greenLEDState = 0;
const int greenButtonPin = PIN_A1;
int greenButtonState = 0;

const int yellowLEDPin = 9;
int yellowLEDState = 0;
const int yellowButtonPin = PIN_A2;
int yellowButtonState = 0;

const int redLEDPin = 8;
int redLEDState = 0;
const int redButtonPin = PIN_A3;
int redButtonState = 0;

const int maxArraySize = 50;
int roundNum = 0;
int ledSequence[maxArraySize];

int piezoPin = 6;

void setup()
{
	Serial.begin(9600);

	pinMode(blueLEDPin, OUTPUT);
	pinMode(greenLEDPin, OUTPUT);
	pinMode(yellowLEDPin, OUTPUT);
	pinMode(redLEDPin, OUTPUT);

	// digitalWrite(blueLEDPin, LOW);
	// digitalWrite(greenLEDPin, LOW);
	// digitalWrite(yellowLEDPin, LOW);
	// digitalWrite(redLEDPin, LOW);

	pinMode(blueButtonPin, INPUT);
	pinMode(greenButtonPin, INPUT);
	pinMode(yellowButtonPin, INPUT);
	pinMode(redButtonPin, INPUT);

	pinMode(latchPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
}

int flashlight(int inPin, int newState, int oldState, int ledState, int ledPin)
{
	newState = digitalRead(inPin);

	if (newState && newState != oldState)
	{
		ledState = !ledState;
		digitalWrite(ledPin, ledState);
		delay(100);
	}

	return newState;
}

//Takes hex number 0-F and returns binary string for displaying on 7 segment (clears display on -1)
int getSegmentString(int num)
{
	int returnString;

	//case for display values 0-F
	switch (num)
	{

	case -1:
		returnString = 0x00;
		break;

	case 0:
		returnString = B11111010;
		break;

	case 1:
		returnString = B01100000;
		break;

	case 2:
		returnString = B11011100;
		break;

	case 3:
		returnString = B11110100;
		break;

	case 4:
		returnString = B01100110;
		break;

	case 5:
		returnString = B10110110;
		break;

	case 6:
		returnString = B10111110;
		break;

	case 7:
		returnString = B11100000;
		break;

	case 8:
		returnString = B11111110;
		break;
	case 9:
		returnString = B11110110;
		break;

	//A
	case 10:
		returnString = B11101110;
		break;

	//B
	case 11:
		returnString = B00111110;
		break;

	//C
	case 12:
		returnString = B10011010;
		break;

	//D
	case 13:
		returnString = B01111100;
		break;

	//E
	case 14:
		returnString = B10011110;
		break;

	//F
	case 15:
		returnString = B10001110;
		break;
	}
	return returnString;
}

void displaySymbol(int num)
{
	//clears display
	// digitalWrite(latchPin, LOW);
	// shiftOut(dataPin, clockPin, MSBFIRST, 0x00);
	// digitalWrite(latchPin, HIGH);
	// delayMicroseconds(10);
	//parallel data not being sent out
	digitalWrite(latchPin, LOW);
	//gets binary string to display symbol on 7-segment display
	int segmentString = getSegmentString(num);
	//shifts out the bits of segmentString to the register, starting with the most significant bit
	shiftOut(dataPin, clockPin, MSBFIRST, segmentString);
	//parallel data sent to 7-segment display
	digitalWrite(latchPin, HIGH);
}

//generates random LED to turn on and adds it to existing sequence
void addToSequence()
{
	ledSequence[roundNum] = random(redLEDPin, blueLEDPin + 1);
	roundNum++;
}

bool getUserInput()
{
	int inputs = 0;
	int buttonPressed;
	while (inputs < roundNum)
	{
		buttonPressed = PINC & 0xF;
		if (buttonPressed == 0)
		{
			continue;
		}
		if (ledSequence[inputs] != (log10(buttonPressed) / log10(2) + redLEDPin))
		{
			Serial.println("Loser!");
			return true;
		}
		delay(500);
		inputs++;
	}
	Serial.println("Sequence Matched!");
	return false;
}

//MAIN
void loop()
{

	displaySymbol(-1);
	// //used to randomize sequence each game
	randomSeed(analogRead(A4));
	bool playerLost = false;

	while (roundNum < maxArraySize && !playerLost)
	{
		addToSequence();
		for (int i = 0; i < roundNum; i++)
		{
			digitalWrite(ledSequence[i], HIGH);
			delay(1000);
			digitalWrite(ledSequence[i], LOW);
		}
		playerLost = getUserInput();
	}
	if (roundNum == maxArraySize)
	{
		Serial.println("You won!");
	}
	else
	{
		Serial.println("You lost!");
	}
	for (;;)
	{
	}
}