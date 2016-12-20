// Using a TFT LCD screen to animate robot mouth frames (basically drawing, erasing, redrawing)
// Hardware --> Arduino + TFT LCD screen (https://www.arduino.cc/en/Main/GTFT)


#include <SD.h>
#include <SPI.h>
#include <TFT.h>

#define cs 10
#define dc 9
#define rst 8
#define pingPin 7



//constant int pingPin = 7; 
//#define SD_CS    8  // Chip select line for SD card


int i=0;

const int Palette[8][3]= {
                            { 255, 240, 245 }, //Background color, for erasing - 0                           
                            {   0,   0,   0 }, //Black  - 1
                            { 102,   0,   0 }, //Brown  - 2
                            { 125,  78,  91 }, //LightBrown  - 3
                            { 195,  89,  89 }, //Pink  - 4
                            { 237, 138, 138 }, //LightPink  - 5
                            { 249, 195, 195 }, //LighterPink  - 6
                            { 255, 255, 255 }, //White  - 7                           
                         };


const int Frame1[8][14] = {  
                             { 0,0,0,1,1,1,1,1,1,0,0,0,0,0 }, //1
                             { 0,0,1,5,5,6,5,4,4,1,0,0,0,0 }, //2
                             { 0,1,4,2,2,2,2,2,2,4,1,0,0,0 }, //3
                             { 1,2,2,0,0,0,0,0,0,2,2,1,0,0 }, //4
                             { 0,1,4,2,0,2,2,0,2,4,1,0,0,0 }, //5
                             { 0,0,1,4,2,5,6,2,5,1,0,0,0,0 }, //6
                             { 0,0,0,1,4,1,1,6,1,0,0,0,0,0 }, //7
                             { 0,0,0,0,1,0,0,1,0,0,0,0,0,0 }, //8
                          };

const int Frame2[8][14] = { 
                             
                             { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, //1 
                             { 0,0,0,1,1,1,1,1,1,0,0,0,0,0 }, //2
                             { 0,0,1,4,5,6,6,5,4,1,0,0,0,0 }, //3
                             { 0,1,4,4,2,2,3,2,5,4,1,0,0,0 }, //4
                             { 1,2,2,2,4,4,1,1,5,5,1,1,0,0 }, //5
                             { 0,1,1,4,4,1,1,5,5,1,1,0,0,0 }, //6
                             { 0,0,0,1,1,0,0,1,1,0,0,0,0,0 }, //7
                             { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, //8
                          };


const int Frame3[8][14] = { 
                             
                             { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, //1 
                             { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, //2
                             { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, //3
                             { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, //4
                             { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, //5
                             { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, //6
                             { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, //7
                             { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, //8
                          };


TFT TFTscreen = TFT(cs, dc, rst);


void setup ()
{
    TFTscreen.begin();
  
    int r = Palette[0][0];
    int g = Palette[0][1];
    int b = Palette[0][2];
  
    TFTscreen.background(r,g,b);
 

        //Parameters xPos : int, the location of the center of the circle on the x axis
        //yPos : int, the location of the center of the circle on the y axis
        //radius : int, the radius of the circle
}

void DrawDimple( int x, int y, int r, int g, int b )
{
   int radius = 4;
   int real_x = 20 + x * 10;
   int real_y = 11 + y * 11;
  
   TFTscreen.fill( r,g,b ); //Color changes FIRST LINE FROM GROUND UP
   TFTscreen.circle( real_x, real_y, radius );
}

void DrawFrame( const int Frame[8][14] )
{
   int x, y;
 
   for( y=0; y< 8; y++ ) 
   for( x=0; x<14; x++ )
   {
      int color_idx = Frame[y][x];
      int r = Palette[color_idx][0];
      int g = Palette[color_idx][1];
      int b = Palette[color_idx][2];
      
      DrawDimple( x,   y, r, g, b );        
   }  


} 

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}


void loop()
{

  long distance, duration;
  pinMode (pingPin, OUTPUT);
  digitalWrite (pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite (pingPin, HIGH);
  delayMicroseconds (5);
  digitalWrite (pingPin, LOW);

  pinMode (pingPin, INPUT);
  duration = pulseIn (pingPin, HIGH);
  distance = microsecondsToCentimeters(duration);



  if (distance < 104){

   DrawFrame( Frame1 );  
   delay(200);
   DrawFrame( Frame2 );
   delay(200);
   
  }

  else {
    DrawFrame ( Frame3 );
  }
  
}
