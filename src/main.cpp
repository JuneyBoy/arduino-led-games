#include <Arduino.h>
#include <math.h>
#include <pitches.h>

//p12 on 74HC595
const int latchPin = 3;
//p11 on 74HC595
const int clockPin = 4;
//p14 on 74HC595
const int dataPin = 2;

const int numOfLeds = 4;

const int blueLEDPin = 11;
const int blueButtonPin = PIN_A0;

const int greenLEDPin = 10;
const int greenButtonPin = PIN_A1;

const int yellowLEDPin = 9;
const int yellowButtonPin = PIN_A2;

const int redLEDPin = 8;
const int redButtonPin = PIN_A3;

const int sequenceLength = 4;

int level = 0;

int piezoPin = 7;

// notes in the melody:
int ledNotes[] = {
	NOTE_B3, NOTE_G3, NOTE_E3, NOTE_C3};

void setup()
{
	Serial.begin(9600);

	pinMode(blueLEDPin, OUTPUT);
	pinMode(greenLEDPin, OUTPUT);
	pinMode(yellowLEDPin, OUTPUT);
	pinMode(redLEDPin, OUTPUT);

	pinMode(blueButtonPin, INPUT);
	pinMode(greenButtonPin, INPUT);
	pinMode(yellowButtonPin, INPUT);
	pinMode(redButtonPin, INPUT);

	pinMode(latchPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
}

//Takes hex number 0-F and returns binary string for displaying on 7 segment
int getSegmentString(int num)
{
	int returnString;

	//case for display values 0-F
	switch (num)
	{
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

void displaySymbol(int segmentString)
{
	digitalWrite(latchPin, LOW);
	//shifts out the bits of segmentString to the register, starting with the most significant bit
	shiftOut(dataPin, clockPin, MSBFIRST, segmentString);
	//parallel data sent to 7-segment display
	digitalWrite(latchPin, HIGH);
	delayMicroseconds(100);
}

//displays score on the 7 segment display
//function extracts the digits num from right to left then calls itself recursively to display the digits, so the digits are displayed left to right
void displayScore(int num)
{
	//q stands for quotient and r stands for remainder
	int q, r;
	int absNum = abs(num);

	//moves decimal place of temp one to the left
	q = absNum / 10;
	//extracts digit in one's place
	r = absNum % 10;

	//if q is bigger than 0, then there are still more digits that need to be extracted
	if (q > 0)
	{
		//function called recursively, keeping r on the stack to display later
		displayScore(q);
	}
	//once q is not larger than 0, all the digits have been extracted and can now be displayed starting with the most significant digit
	displaySymbol(getSegmentString(r));
	//digit is displayed for 0.5 seconds
	delay(500);
	//display is cleared for 0.1 seconds before displaying subsequent digits or exiting function entirely
	displaySymbol(0);
	delay(100);
}

void flash(int led, int onTime, int game)
{
	if (game == 1)
	{
		digitalWrite(led, HIGH);
		tone(piezoPin, ledNotes[led - redLEDPin]);
		delay(onTime);
		noTone(piezoPin);
		digitalWrite(led, LOW);
		delay(50);
	}
	else
	{
	}
}

//generates random LED to turn on and adds it to existing sequence
void addToSequence(int ledSequence[])
{
	ledSequence[level] = random(redLEDPin, blueLEDPin + 1);
	level++;
}

bool getUserInput(int ledSequence[], int sequenceLength, int game)
{
	int inputs = 0;
	int buttonPressed;
	int buttonToLED;
	int constPin;
	if (game == 1) {
		constPin = redLEDPin;
	}
	else {
		constPin = 0xA;
	}
	while (inputs < sequenceLength)
	{
		buttonPressed = PINC & 0xF;
		buttonToLED = log10(buttonPressed) / log10(2) + constPin;

		if (buttonPressed == 0)
		{
			continue;
		}
		if (ledSequence[inputs] != buttonToLED)
		{
			return true;
		}
		flash(buttonToLED, 500, game);
		inputs++;
	}
	Serial.println("Sequence Matched!");
	delay(100);
	return false;
}

void endGame(bool playerLost) {
if (playerLost)
	{
		Serial.println("You lost!");
	}
	else
	{
		Serial.println("You won!");
	}
	for (;;)
	{
		displayScore(level - 1);
	}
}

void playSimonGame(int game)
{
	const int maxArraySize = 50;
	int ledSequence[maxArraySize];
	bool playerLost = false;

	while (level < maxArraySize && !playerLost)
	{
		addToSequence(ledSequence);
		for (int i = 0; i < level; i++)
		{
			flash(ledSequence[i], 500, game);
		}
		playerLost = getUserInput(ledSequence, level, game);
	}
	endGame(playerLost);
}

//MAIN
void loop()
{
	//used to randomize sequence each game
	randomSeed(analogRead(A4));

	//Picking which game:
	int game;
	int *ledSequence;
	switch (game)
	{
	//Simon
	case 1:
		playSimonGame(game);
		break;

	//Speed Memory Game
	case 2:
		break;

	//Hex to Binary Game
	case 3:
		break;
	}
}
