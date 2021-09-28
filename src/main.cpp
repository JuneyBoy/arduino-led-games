#include <Arduino.h>
#include <math.h>
#include <pitches.h>

//Testing to make sure I will now properly show up as a contributor on github

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
	case -1:
		returnString = B00000000;
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

void displaySymbol(int segmentString, int onTime)
{
	digitalWrite(latchPin, LOW);
	//shifts out the bits of segmentString to the register, starting with the most significant bit
	shiftOut(dataPin, clockPin, MSBFIRST, segmentString);
	//parallel data sent to 7-segment display
	digitalWrite(latchPin, HIGH);
	delay(onTime);
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
	displaySymbol(getSegmentString(r), 0.1);
	//digit is displayed for 0.5 seconds
	delay(500);
	//display is cleared for 0.1 seconds before displaying subsequent digits or exiting function entirely
	displaySymbol(getSegmentString(-1), 0.1);
	delay(100);
}

void flash(int thingToFlash, int onTime, int game)
{
	if (game == 1)
	{
		digitalWrite(thingToFlash, HIGH);
		tone(piezoPin, ledNotes[thingToFlash - redLEDPin]);
		delay(onTime);
		noTone(piezoPin);
		digitalWrite(thingToFlash, LOW);
		delay(50);
	}
	else
	{
		displaySymbol(getSegmentString(thingToFlash), onTime);
		// tone(piezoPin, ledNotes[thingToFlash - 0xA]);
		// delay(onTime);
		// noTone(piezoPin);
		displaySymbol(getSegmentString(-1), onTime);
	}
}

void makeSequence(int symbolSequence[], int sequenceLength)
{
	for (int i = 0; i < sequenceLength; ++i)
	{
		symbolSequence[i] = random(0xA, 0xD + 1);
	}
	level++;
}

//generates random LED to turn on and adds it to existing sequence
void addToSequence(int ledSequence[])
{
	ledSequence[level] = random(redLEDPin, blueLEDPin + 1);
	level++;
}

bool getUserInput(int sequence[], int sequenceLength, int game)
{
	int inputs = 0;
	int buttonPressed;
	int buttonToLED;
	int constPin;
	if (game == 1)
	{
		constPin = redLEDPin;
		while (inputs < sequenceLength)
		{
			buttonPressed = PINC & 0xF;
			buttonToLED = log10(buttonPressed) / log10(2) + constPin;

			if (buttonPressed == 0)
			{
				continue;
			}
			if (sequence[inputs] != buttonToLED)
			{
				return true;
			}
			flash(buttonToLED, 500, game);
			inputs++;
		}
	}
	else
	{
		constPin = 0xA;
		while (inputs < sequenceLength)
		{
			buttonPressed = PINC & 0xF;

			switch(buttonPressed) {
				case 0b1000: 
					buttonToLED = 0xA;
					break;
				case 0b0100: 
					buttonToLED = 0xB;
					break;
				case 0b0010: 
					buttonToLED = 0xC;
					break;
				case 0b0001: 
					buttonToLED = 0xD;
					break;
			}

			if (buttonPressed == 0)
			{
				continue;
			}
			if (sequence[inputs] != buttonToLED)
			{
				return true;
			}
			flash(buttonToLED, 500, game);
			inputs++;
		}
	}
	Serial.println("Sequence Matched!");
	delay(100);
	return false;
}

void endGame(bool playerLost)
{
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

void playSpeedMemoryGame(int game)
{
	const int sequenceLength = 4;
	int symbolSequence[sequenceLength];
	bool playerLost = false;
	while (!playerLost)
	{
		makeSequence(symbolSequence, sequenceLength);
		for (int i = 0; i < sequenceLength; ++i)
		{
			flash(symbolSequence[i], pow(0.75, level-1) * 1000, game);
		}
		playerLost = getUserInput(symbolSequence, sequenceLength, game);
	}
	endGame(playerLost);
}

//MAIN
void loop()
{

	displaySymbol(getSegmentString(-1), 0.1);
	//used to randomize sequence each game
	randomSeed(analogRead(A4));

	//Picking which game:
	int game = 2;
	// int *ledSequence;
	switch (game)
	{
	//Simon
	case 1:
		playSimonGame(game);
		break;

	//Speed Memory Game
	case 2:
		playSpeedMemoryGame(game);
		break;

	//Hex to Binary Game
	case 3:
		break;
	}
}
