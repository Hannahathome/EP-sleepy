// LIBRARIES
//#include <OOCSI.h>                // send data to oocsi (not yet implemented)
//#include <EEPROM.h>               // saving data in the memory of ESP (not yet implemented)
#include "LEDs.h"
#include "Buttons.h"
#include "AudioPlayer.h"

//QUESTIONS--------------------------------------------------//
int QUESTION_AMOUNT = 12;
char questions[] = {Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9, Q10, Q11, Q12};
int answers[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void setup () {
  //AUDIO PLAYER--------------------------------------------------//
  Serial.begin(9600);
  AudioPlayer player = AudioPlayer();
  player.Initialize();
  Serial.println("START");
  delay(500);

  //PLAY/PAUSE SETUP
  Buttons buttons = Buttons();
  buttons.Initialize();



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
  player.PlayIntro();
  
  delay (17000); //waiting for the text to finish
  //checkButton();
  buttons.Wait(Buttons::BUTTON_START); //waiting for the button to be pressed

  for (int i = 0; i < QUESTION_AMOUNT; i++) {
    answers[i] = playQuestion(questions[i], buttons, player);
  }

  for (int i = 0; i < 12; i++) {
    Serial.println(String(answers[i]));
  }

  walkingLights (); //anything after playig the sound will happen during the playing, beware of this
  Serial.println("end of the program");
}

/***************************************************/

void loop() {}
