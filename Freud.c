// Ping sensor + TTS + Servo
// State machine bits -> Probably not complete
// Can not find wiring diagrams -> Pin definitions
// Can not find laser cutter project files for housing


#include <SoftwareSerial.h>
#include <SPI.h>
#include <TFT.h>
#include <Servo.h>
// #include "LibrarySmartRobot.h"

#define rxPin 2 //10 //Serial input - connects to Emic 2's SOUT pin
#define txPin 3 //11 //Serial output - connects to Emic 2's SIN pin
#define ledPin 13 //On-board ledPin
#define cs 10 //CS LD - TFT LCD
#define dc 9 // Reset - TFT LCD
#define rst 8 // D/C-LD - TFT LCD

//TFT LCD code starts here

// For future ref:
//int Black[3]={0,0,0};
//int Pink[3]={195,89,89};
//int Brown[3]={102, 0,0};
//int Pink[3]={195,89,89};
//int LightPink[3]={237, 138, 138};
//int LighterPink[3]={249,195,195};

int i = 0;

const int Palette[8][3] = {
	{ 255, 240, 245 }, //Background color, for erasing - 0                           
	{ 0, 0, 0 }, //Black  - 1
	{ 102, 0, 0 }, //Brown  - 2
	{ 125, 78, 91 }, //LightBrown  - 3
	{ 195, 89, 89 }, //Pink  - 4
	{ 237, 138, 138 }, //LightPink  - 5
	{ 249, 195, 195 }, //LighterPink  - 6
	{ 255, 255, 255 }, //White  - 7                           
};

//int Brown[3]={102, 0,0};
//int LightPink[3]={237, 138, 138};
//int LighterPink[3]={249,195,195};

const int Frame1[8][14] = {
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 }, //1
	{ 0, 0, 1, 5, 5, 6, 5, 4, 4, 1, 0, 0, 0, 0 }, //2
	{ 0, 1, 4, 2, 2, 2, 2, 2, 2, 4, 1, 0, 0, 0 }, //3
	{ 1, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 1, 0, 0 }, //4
	{ 0, 1, 4, 2, 0, 2, 2, 0, 2, 4, 1, 0, 0, 0 }, //5
	{ 0, 0, 1, 4, 2, 5, 6, 2, 5, 1, 0, 0, 0, 0 }, //6
	{ 0, 0, 0, 1, 4, 1, 1, 6, 1, 0, 0, 0, 0, 0 }, //7
	{ 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0 }, //8
};

const int Frame2[8][14] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //1 
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 }, //2
	{ 0, 0, 1, 4, 5, 6, 6, 5, 4, 1, 0, 0, 0, 0 }, //3
	{ 0, 1, 4, 4, 2, 2, 3, 2, 5, 4, 1, 0, 0, 0 }, //4
	{ 1, 2, 2, 2, 4, 4, 1, 1, 5, 5, 1, 1, 0, 0 }, //5
	{ 0, 1, 1, 4, 4, 1, 1, 5, 5, 1, 1, 0, 0, 0 }, //6
	{ 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0 }, //7
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //8
};


TFT TFTscreen = TFT(cs, dc, rst);

//TFT LCD code ends here

//Emic2 codestarts here
//Set up a new serial port - TTS
SoftwareSerial emicSerial = SoftwareSerial(rxPin, txPin);
//Emic2 code ends here

//Ping sensor code starts here
//Setting up input for Ping sensor
const int pingPin = 7;
unsigned int duration, inches;

long microsecondsToCentimeters(long microseconds) /*  Speed of sound = 340m/s = 29 microseconds/centimeter.
												  To find distance = Take half of distance travelled.*/
{
	long lRetVal = microseconds / 29 / 2;
	Serial.println((int)lRetVal);
	return lRetVal;
}
//Ping sensor code ends here

//Servo code starts here
Servo myservo;
int servoPosition = 90; //Stores the intial position of the servo
int servoDeltaChange = 1; //The angle of rotation for the servo code
const int servoRight = 110; //Max angle in servo right-turn range
const int servoLeft = 70; // Max angle in servo left-turn range
int g_iDelay = 45;
//Servo code ends here

void setup()
{

	TFTscreen.begin();

	int r = Palette[0][0];
	int g = Palette[0][1];
	int b = Palette[0][2];

	TFTscreen.background(r, g, b);


	//Parameters xPos : int, the location of the center of the circle on the x axis
	//yPos : int, the location of the cent. er of the circle on the y axis
	//radius : int, the radius of the circle
	Serial.begin(9600); //Ping sensor

	//define pin modes - TTS
	pinMode(ledPin, OUTPUT);
	pinMode(rxPin, INPUT);
	pinMode(txPin, OUTPUT);


	emicSerial.begin(9600); //Set the data rate for the SoftwareSerial port - Emic 2
	digitalWrite(ledPin, LOW); // Turn LED off

	/*When the Emic 2 powers on, it takes about three seconds to successfully initialize.
	It then sends a ":" character to indicate its ready to accept commands. If the Emic 2 is already initialized, a CR
	will also cause it to send an ":".*/

	emicSerial.print('\n'); // Send a CR incase the system is already up
	while (emicSerial.read() != ':');// When the Emic 2 has intialized and is ready, it will send a single ":". Wait here until we receive it.
	delay(10);
	emicSerial.flush();

	//Servo code
	myservo.attach(6);
}

void DrawDimple(int x, int y, int r, int g, int b)
{
	int radius = 4;
	int real_x = 20 + x * 10;
	int real_y = 11 + y * 11;

	TFTscreen.fill(r, g, b); //Color changes FIRST LINE FROM GROUND UP
	TFTscreen.circle(real_x, real_y, radius);
}

void DrawFrame(const int Frame[8][14], bool bVertFlip)
{
	int x, y;

	for (y = 0; y < 8; y++)
		for (x = 0; x < 14; x++)
		{
			int color_idx = Frame[y][x];
			int r = Palette[color_idx][0];
			int g = Palette[color_idx][1];
			int b = Palette[color_idx][2];

			if (bVertFlip)
				DrawDimple(x, 7 - y, r, g, b);
			else
				DrawDimple(x, y, r, g, b);
		}



} // This bracket ends the void setup () function

long PingGetDistance()
{
	long distance, duration;
	pinMode(pingPin, OUTPUT);
	digitalWrite(pingPin, LOW);
	delayMicroseconds(5);
	digitalWrite(pingPin, HIGH);
	delayMicroseconds(5);
	digitalWrite(pingPin, LOW);

	pinMode(pingPin, INPUT);
	duration = pulseIn(pingPin, HIGH);
	Serial.println(duration);

	distance = microsecondsToCentimeters(duration);

	return distance;
}
//State machine for the sensor and TTS
// Don't fuck this up!  
#define STATE_IDLE_0    0 // Sensor on,robot is not speaking
#define STATE_IDLE_1    1 // Sensor off
#define STATE_SPEAKING  2 // Robot is speaking, the sensor can either be on or off
int g_iState = STATE_IDLE_0;
//State machine for the sensor and TTS - end code

//State machine for the servo
#define SERVO_STATE_SCANNING 3
#define SERVO_STATE_GOING_TO_EDGE 4
#define SERVO_STATE_GOING_TO_CENTER 5
#define SERVO_STATE_STAYING_AT_CENTER 6
int g_iServoState = SERVO_STATE_SCANNING;
//State machine for the servo - end code

//void drawLips(bool bFirstFramec){
void drawLips(){
	DrawFrame(Frame1, true);
	delay(25);
	DrawFrame(Frame2, true);
	delay(25);
}

void startTalking(){
	emicSerial.print('\n');
	emicSerial.print("STest message. \n");
	//emicSerial.print("D1\n");

}


void loop()
{
	// Reading out the PING distance - do it always regardless of the state
	long distance = PingGetDistance();

	if (g_iState == STATE_IDLE_1)
	{
		//Events to monitor: Sensor going OFF

		if (distance > 50)
			g_iState = STATE_IDLE_0;
	}
	else
		if (g_iState == STATE_IDLE_0)
		{
			//Events to monitor: Sensor going ON

			//if( g_iServoState = SERVO_STATE_STAYING_AT_CENTER )
			if (distance <= 50)
			{
				g_iState = STATE_SPEAKING;
				startTalking();
			}

		}
		else //g_iState == STATE_SPEAKING
		{
			// Events to monitor: The robot stops speaking
			if (emicSerial.read() == ':')
			{
				g_iState = STATE_IDLE_1;
				digitalWrite(ledPin, LOW); //Turn off the LED
			}
			else
				drawLips();
		}

	//
	// Servo movement code
	//

	if ((servoPosition >= servoRight) || (servoPosition <= servoLeft)){
		servoDeltaChange = -(servoDeltaChange);
	}
	servoPosition += servoDeltaChange;
	myservo.write(servoPosition);


	//
	//  Interaction between ping sensor and servo
	//

	if (g_iServoState == SERVO_STATE_STAYING_AT_CENTER && distance > 50){
		g_iServoState = SERVO_STATE_SCANNING;
		myservo.write(servoPosition);
	}

	if (g_iServoState == SERVO_STATE_SCANNING && distance < 50){
		g_iServoState = SERVO_STATE_GOING_TO_EDGE;
		myservo.write(servoPosition);
	}

	if (g_iServoState == SERVO_STATE_GOING_TO_EDGE && distance < 50){
		myservo.write(90);
	}
	else {
		g_iServoState = SERVO_STATE_SCANNING;
		myservo.write(servoPosition);
	}
}// ends void loop () 

	
	
