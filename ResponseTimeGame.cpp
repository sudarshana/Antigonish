// Who can respond faster to a blinking series of LEDs, that speed up?
// Hardware --> Breadboard + Arduino + LEDs + resistors + 2 SPST switches. Did not need external power (USB).  
// Should probably have debounce --> Ref: https://www.arduino.cc/en/Tutorial/Debounce
// Quirky and I had good fun with this :)


void setup () {
  pinMode (0, OUTPUT);
  pinMode (1, OUTPUT);
  pinMode (2, OUTPUT);
  pinMode (3, OUTPUT);
  pinMode (4, OUTPUT);
  pinMode (5, OUTPUT);
  pinMode (6, OUTPUT);
  pinMode (7, OUTPUT);
  pinMode (9, INPUT_PULLUP);
  pinMode (10, INPUT_PULLUP);
}

bool firstPlayerTurn=true; //Sets first player's turn
float interval=350;

void loop () {
  int i;
  for (i=0; i<=8; i++){digitalWrite(i,LOW);}
  delay(interval);
  for (i=0; i<=8; i++){digitalWrite(i,HIGH);}
  delay(interval);
  for (i=0; i<=8; i++){digitalWrite(i,LOW);}
  int x=0; //Always, always, always set variables to something
  int switchPin =0;

  if (firstPlayerTurn==true) {
    switchPin =10; //Depending on whose turn it is, this takes input from pin 9 or 10
  }
  else {switchPin=9;
  }
  
  interval=interval*.9;
  while (x<8) { //Running the LED lights from Player A to Player B
    delay (interval); //Change every time the loop runs, to make it faster **CHANGE CODE** time=timePrevious*.8
    if (firstPlayerTurn==true){
      digitalWrite (x, HIGH);
    }
    else {
      digitalWrite (7-x, HIGH);
    }
    x++;
  } //Loop turning the lights on ends here.
  
  bool failed=false; //Declaring the boolean value for switch not pressed
  int switched = !digitalRead (switchPin); //inverse switch is On 
  unsigned long timeTaken =0; 
  unsigned long startTime= millis();
  while (!switched){
    switched=!digitalRead(switchPin);
    unsigned long endTime =millis();
    timeTaken= endTime-startTime; 
    if (timeTaken>interval*4){
      failed=true; //The player has not pressed the switch
      break;
      //Fun stuff should happen     
    }
  }
  int counter=0;
  int lightsOut=0;
  firstPlayerTurn= !firstPlayerTurn;
  if (true==failed){
    for (lightsOut=0;lightsOut<8;lightsOut++)
    {digitalWrite(lightsOut, LOW);
    }
    while(true){
       if (firstPlayerTurn==true){
         for (counter=0; counter<4; counter++){
           digitalWrite(counter,HIGH);
           delay(250);
           digitalWrite(counter, LOW);
         }
       }
       else { 
         for (counter=0;counter<4;counter++){
           digitalWrite (7-counter, HIGH);
           delay(250);
           digitalWrite (7-counter, LOW);
        
  }  
       }
    }
 
    
  }
}

