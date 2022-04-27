// LIBRARIES
//#include <OOCSI.h>                // send data to oocsi (not yet implemented)
//#include <EEPROM.h>               // saving data in the memory of ESP (not yet implemented)
#include "LEDs.h"
#include "Buttons.h"
#include "AudioPlayer.h"

/*--------------------Specifications-----------------------*/
#define FOLDER_ONE 0X00
#define INTRO 0X01
#define Q1 0X02
#define Q2 0X03
#define Q3 0X04
#define Q4 0X05
#define Q5 0X06
#define Q6 0X07
#define Q7 0X08
#define Q8 0X09
#define Q9 0X0A
#define Q10 0X0B
#define Q11 0X0C
#define Q12 0X0D
#define OUTRO 0X0E
#define OUTRO_STORY 0X0F

#define FOLDER_TWO 0X01
#define STORY_1 0X01
#define STORY_2 0X02
#define STORY_3 0X03
#define STORY_4 0X04
#define STORY_5 0X05
/*********************************************************************/

//QUESTIONS--------------------------------------------------//
int QUESTION_AMOUNT = 12;
char questions[] = {Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9, Q10, Q11, Q12};
int answers[] = {0,0,0,0,0,0,0,0,0,0,0,0}; 

void setup () {
  //AUDIO PLAYER--------------------------------------------------//
  Serial.begin(9600);
  InitializeAudio();
  Serial.println("START");
  delay(500);

  //PLAY/PAUSE SETUP


  InitializeButtons();

  

  //LIGHTS IN BUTTONS--------------------------------------------------//
  // initialize all the pins connected to the shift register as outputs
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  Serial.println("Lights setup");

/***************************************************/
  //THE ACTUAL LIKE PROGRAM THAT RUNS ONCE--------------------------------------------------//
  Serial.println("Starting system");
  //first lights
  blinkLights ();
  blinkLights ();

  //introduction text
  sendCommand(PLAY_W_INDEX, FOLDER_ONE, INTRO); //versturen commando naar mp3 --> speel muziek
  delay (17000); //waiting for the text to finish
  //checkButton();
  buttonWait(BUTTON_START); //waiting for the button to be pressed
  
  for (int i = 0; i < QUESTION_AMOUNT; i++) {
    answers[i] = playQuestion(questions[i]);
  }

  for(int i = 0; i < 12; i++) {
    Serial.println(String(answers[i]));
  }
  
  walkingLights (); //anything after playig the sound will happen during the playing, beware of this
  Serial.println("end of the program"); 
}

/***************************************************/

void loop() {}
