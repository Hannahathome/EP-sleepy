/*
   Using this code you can test your buttons.
   Use the serial monitor to see if your system detects the buttons being pushed 

   This code was written by Hannah van Iterson
   Code shiftregister LED control inspired  by:
   https://github.com/NicolasBrondin/flower-player/blob/master/arduino.c

*/
 

int BUTTON_START = 34;  // GI(O)P 34 pin connected to button (CAREFUL! INPUT ONLY pin, this pin does not give any OUTPUT, so do not use if for that)
int BUTTON_ONE = 27;    // GIOP 27 pin connected to button 
int BUTTON_TWO = 26;    // GIOP 26 pin connected to button 
int BUTTON_THREE = 25;  // GIOP 25 pin connected to button 
int BUTTON_FOUR = 33;   // GIOP 33 pin connected to button 
int BUTTON_FIVE = 32;   // GIOP 32 pin connected to button 

void setup() {
  Serial.begin(9600);
  // initialize the pushbutton pin as an input
  pinMode(BUTTON_ONE, INPUT);
  pinMode(BUTTON_TWO, INPUT);
  pinMode(BUTTON_THREE, INPUT);
  pinMode(BUTTON_FOUR, INPUT);
  pinMode(BUTTON_FIVE, INPUT);
  pinMode(BUTTON_START, INPUT);
  
  Serial.println("system start");
}

void loop() {
//    Serial.println("we have entered the loop");
checkButton ();

}

void checkButton (){ 
  int answerOne = digitalRead(BUTTON_ONE); 
  int answerTwo = digitalRead(BUTTON_TWO); 
  int answerThree = digitalRead(BUTTON_THREE); 
  int answerFour = digitalRead(BUTTON_FOUR); 
  int answerFive = digitalRead(BUTTON_FIVE); 
  int replayQuestion = digitalRead(BUTTON_START); 

  if(answerOne == 1){
    Serial.println ("button 1 pressed"); 
    delay(500);                             //delay to prevent sending a lot of the same answers
  }
    if(answerTwo == 1){
    Serial.println ("button 2 pressed"); 
    delay(500);                             //delay to prevent sending a lot of the same answers
  }
    if(answerThree == 1){
    Serial.println ("button 3 pressed"); 
    delay(500);                             //delay to prevent sending a lot of the same answers
  }
    if(answerFour == 1){
    Serial.println ("button 4 pressed"); 
    delay(500);                             //delay to prevent sending a lot of the same answers
  } 
    if(answerFive == 1){
    Serial.println ("button 5 pressed"); 
    delay(500);                             //delay to prevent sending a lot of the same answers
  }
    if(replayQuestion == 1){
    Serial.println ("replay sound"); 
    delay(500);                             //delay to prevent sending a lot of the same answers
  }
}
