// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
	Name:       BMW.ino
	Created:	23.02.2019 13:55:51
	Author:     IBOOK\velse
*/

// Define User Types below here or use a .h file
//


// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//



#include <ir_Lego_PF_BitStreamEncoder.h>
#include <IRremoteInt.h>
#include <IRremote.h>
#include <boarddefs.h>
int Relay_1 = 3; //left
int Relay_2 = 4; //right
int Relay_3 = 5; //StopL
int Relay_4 = 6; //PdrkingL
int Relay_5 = 7; //ReversL
int Relay_6 = 8; //stopR
int Relay_7 = 9; //ParkingR
int Relay_8 = 10; //ReversR

volatile bool StopBit = false;

IRrecv irrecv(2);
decode_results results;

// The setup() function runs once each time the micro-controller starts
void setup()
{

	pinMode(Relay_1, OUTPUT);
	pinMode(Relay_2, OUTPUT);
	pinMode(Relay_3, OUTPUT);
	pinMode(Relay_4, OUTPUT);
	pinMode(Relay_5, OUTPUT);
	pinMode(Relay_6, OUTPUT);
	pinMode(Relay_7, OUTPUT);
	pinMode(Relay_8, OUTPUT);
	pinMode(2, INPUT);
	digitalWrite(2, LOW);

	attachInterrupt(0, ExtraStop, CHANGE);

	off();

	irrecv.enableIRIn();
	//Serial.begin(9600);

}

// Add the main program code into the continuous loop() function
void loop()
{

	if (irrecv.decode(&results))
	{
		//Serial.println(results.value);
		irrecv.resume();

		switch (results.value) {
		case 1604042521:
			on();
			break;
		case 3783180003:
			off();
			break;
		case 2406563939:
			Revers();
			break;
		case 1025137608:
			PushLeft();
			break;
		case 2454966755:
			PushRight();
			break;
		case 3742742344:
			PushCrash();
			break;
		case 3943488840:
			Stop();
			break;
		case 3331861704:
			Parking();
			break;
		}

	}

}

void off()
{
	digitalWrite(Relay_1, HIGH);
	digitalWrite(Relay_2, HIGH);
	digitalWrite(Relay_3, HIGH);
	digitalWrite(Relay_4, HIGH);
	digitalWrite(Relay_5, HIGH);
	digitalWrite(Relay_6, HIGH);
	digitalWrite(Relay_7, HIGH);
	digitalWrite(Relay_8, HIGH);
}

void on()
{
	digitalWrite(Relay_1, LOW);
	digitalWrite(Relay_2, LOW);
	digitalWrite(Relay_3, LOW);
	digitalWrite(Relay_4, LOW);
	digitalWrite(Relay_5, LOW);
	digitalWrite(Relay_6, LOW);
	digitalWrite(Relay_7, LOW);
	digitalWrite(Relay_8, LOW);
}

void Left()
{

	digitalWrite(Relay_1, LOW);
	digitalWrite(Relay_2, HIGH);
	digitalWrite(Relay_3, HIGH);
	digitalWrite(Relay_4, HIGH);
	digitalWrite(Relay_5, HIGH);
	digitalWrite(Relay_6, HIGH);
	digitalWrite(Relay_7, HIGH);
	digitalWrite(Relay_8, HIGH);

}

void Right()
{

	digitalWrite(Relay_1, HIGH);
	digitalWrite(Relay_2, LOW);
	digitalWrite(Relay_3, HIGH);
	digitalWrite(Relay_4, HIGH);
	digitalWrite(Relay_5, HIGH);
	digitalWrite(Relay_6, HIGH);
	digitalWrite(Relay_7, HIGH);
	digitalWrite(Relay_8, HIGH);

}

void Stop()
{

	digitalWrite(Relay_1, HIGH);
	digitalWrite(Relay_2, HIGH);
	digitalWrite(Relay_3, LOW);
	digitalWrite(Relay_4, HIGH);
	digitalWrite(Relay_5, HIGH);
	digitalWrite(Relay_6, LOW);
	digitalWrite(Relay_7, HIGH);
	digitalWrite(Relay_8, HIGH);

}

void Revers()
{

	digitalWrite(Relay_1, HIGH);
	digitalWrite(Relay_2, HIGH);
	digitalWrite(Relay_3, HIGH);
	digitalWrite(Relay_4, HIGH);
	digitalWrite(Relay_5, LOW);
	digitalWrite(Relay_6, HIGH);
	digitalWrite(Relay_7, LOW);
	digitalWrite(Relay_8, HIGH);

}

void Parking()
{

	digitalWrite(Relay_1, HIGH);
	digitalWrite(Relay_2, HIGH);
	digitalWrite(Relay_3, HIGH);
	digitalWrite(Relay_4, LOW);
	digitalWrite(Relay_5, HIGH);
	digitalWrite(Relay_6, HIGH);
	digitalWrite(Relay_7, HIGH);
	digitalWrite(Relay_8, LOW);

}

void Crash()
{

	digitalWrite(Relay_1, LOW);
	digitalWrite(Relay_2, LOW);
	digitalWrite(Relay_3, HIGH);
	digitalWrite(Relay_4, HIGH);
	digitalWrite(Relay_5, HIGH);
	digitalWrite(Relay_6, HIGH);
	digitalWrite(Relay_7, HIGH);
	digitalWrite(Relay_8, HIGH);

}

void PushLeft() {
	int Blinck = 3;
	int Increment = 0;

	while (Blinck >= Increment)
	{
		Left();
		delay(300);
		off();
		delay(300);
		Increment++;
	}

}

void PushRight() {
	int Blinck = 3;
	int Increment = 0;

	while (Blinck >= Increment)
	{
		Right();
		delay(300);
		off();
		delay(300);
		Increment++;
	}

}

void PushCrash() {
	int Blinck = 10;
	int Increment = 1;
	StopBit = false;

	while (Blinck >= Increment)
	{
		Crash();
		delay(300);
		off();
		delay(300);
		Increment++;

		if (StopBit) {
			break;
		}
	}

	StopBit = false;

}

void ExtraStop() {

	if (irrecv.decode(&results))
	{
		//if (results.value == 3783180003){

		StopBit = true;

		//}

	}

}
