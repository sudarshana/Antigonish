// Ping sensor activity triggering TTS 
// DECtalk + Ping Sensors + Arduino
// Wiring -> Pin definitions

#include <SoftwareSerial.h> 

#define rxPin   10  // Serial input (connects to Emic 2's SOUT pin) - PING
#define txPin   11  // Serial output (connects to Emic 2's SIN pin) - PING
#define ledPin  13  // On-board ledPin - PING

// Set up a new serial port - TTS
SoftwareSerial emicSerial =  SoftwareSerial( rxPin, txPin );

// Setting up input for ping sensor - PING
const int pingPin = 7;
unsigned int duration, inches;


void setup() {
  
  // define pin modes - TTS
  pinMode ( ledPin, OUTPUT );
  pinMode ( rxPin, INPUT );
  pinMode ( txPin, OUTPUT );
  
  // set the data rate for the SoftwareSerial port - TTS
  emicSerial.begin ( 9600 ); // - TTS
  digitalWrite ( ledPin, LOW );  // turn LED off - TTS
  emicSerial.print ( '\n' );  
  while ( emicSerial.read() != ':' );
  delay ( 3 );
  emicSerial.flush();

  long microsecondsToCentimeters ( long microseconds ) // Speed of sound = 340m/s = 29 microseconds/centimeter. To find distance = Take half of distance travelled.
{
  return microseconds / 29 / 2;
}
 
} // Bracket ends void setup ()


 void loop () {

  long distance, duration; 
  pinMode ( pingPin, OUTPUT );
  digitalWrite ( pingPin, LOW );
  delayMicroseconds ( 5 );
  digitalWrite ( pingPin, HIGH );
  delayMicroseconds ( 5 );
  digitalWrite ( pingPin, LOW );

  pinMode ( pingPin, INPUT );
  duration = pulseIn ( pingPin, HIGH );
  distance = microsecondsToCentimeters ( duration );

  if (distance < 104) {
  	emicSerial.print ( 'S' );
  	emicSerial.print ( "Testing something. La la la la. " )
  	emicSerial.print ( '\n' );
  	digitalWrite ( ledPin, HIGH );
  	while ( emicSerial.read() != ':' );
  	digitalWrite ( ledPin, LOW )

  }
