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
int Relay_1 = 4; //left
int Relay_2 = 5; //right
int Relay_3 = 6; //Stop
int Relay_4 = 7; //Pdrking
int Relay_5 = 8; //Revers
int Relay_6 = 9; //X
int Relay_7 = 10; //blenda
int Relay_8 = 11; //ND

int R1, R2, R3, R4, R5, R6, R7, R8 = HIGH;

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
	digitalWrite(2,LOW);	

	attachInterrupt(0, ExtraStop, CHANGE);

	off();

	irrecv.enableIRIn();
	Serial.begin(9600);

}

// Add the main program code into the continuous loop() function
void loop()
{
	
	if (irrecv.decode(&results))
	{
		Serial.println(results.value);
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
	digitalWrite(Relay_6, HIGH);
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
	digitalWrite(Relay_6, LOW);
	digitalWrite(Relay_7, HIGH);
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
	digitalWrite(Relay_8, HIGH);

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

void Blenda()
{

  digitalWrite(Relay_1, HIGH);
  digitalWrite(Relay_2, HIGH);
  digitalWrite(Relay_3, HIGH);
  digitalWrite(Relay_4, HIGH);
  digitalWrite(Relay_5, HIGH);
  digitalWrite(Relay_6, HIGH);
  digitalWrite(Relay_7, LOW);
  digitalWrite(Relay_8, HIGH);

}

void PushLeft() {
	int Blinck = 5;
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
	int Blinck = 5;
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

	while (!StopBit)
	{
		Crash();
		delay(300);
    off();
    delay(300);
	}

  StopBit = false;

}

void ExtraStop() {

  if (irrecv.decode(&results))
   {
      if (results.value == 3783180003){
      
        StopBit = true;

      }
	  
	  }

  //////*
  ////switch (results.value) {
  ////case 1604042521:
	 //// on();
	 //// break;
  ////case 3783180003:
	 //// off();
	 //// break;
  ////case 2406563939:
	 //// revers();
	 //// break;
  ////case 1025137608:
	 //// pushleft();
	 //// break;
  ////case 2454966755:
	 //// pushright();
	 //// break;
  ////case 3742742344:
	 //// pushcrash();
	 //// break;
  ////case 3943488840:
	 //// stop();
	 //// break;
  ////case 3331861704:
	 //// parking();
	 //// break;
  ////}
  ////

}
