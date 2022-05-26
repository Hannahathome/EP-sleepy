// LIBRARIES
#include "LEDs.h"
#include "Buttons.h"
#include "AudioPlayer.h"

int QUESTION_AMOUNT = 12;
char questions[] = {Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9, Q10, Q11, Q12};   // Create an array for the questions (this is based on the number of questions as specified in QUASTION_AMOUNT)
int answers[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};                     // Create an array for the answers of the questions
char storyParts[] = {STORY_1, STORY_2, STORY_3, STORY_4, STORY_5};

void setup () {
  Serial.begin(9600);

  Buttons buttons = Buttons();
  buttons.Initialize();

  stateInitialization();                // The number of times the system has done a full run
  if (digitalRead(Buttons::BUTTON_START)) {
    resetState();
  }

  blinkLights ();
  blinkLights ();
  blinkLights ();
  Serial.println("STARTING SYSTEM");

  //lightsOn ();
  AudioPlayer player = AudioPlayer();
  player.Initialize();

  Serial.println("START");
  delay(500);

  // Initialize the pins connected to the shift register as outputs, these are the LEDs in the buttons
  pinMode(latchPin, OUTPUT);            // Look at your specific system to see what pins to connec them to.
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  Serial.println("Lights setup");

  OOCSIInitialization();

  /***************************************************/


  //THE ACTUAL LIKE PROGRAM THAT RUNS ONCE--------------------------------------------------//
  Serial.println("Starting system");

  blinkLights ();       // I use this as indication the system is starting.
  blinkLights ();

  player.PlayIntro();   // Anything after playig the sound will happen during the playing, beware of this
  delay (17000);        // Waiting for the text to finish, this duration is based on the time of the intro 17 seconds

  buttons.Wait(Buttons::BUTTON_START); // Waiting for the button to be pressed

  // Playing the questions in order
  for (int i = 0; i < QUESTION_AMOUNT; i++) {
    answers[i] = playQuestion(questions[i], buttons, player);
  }

  // Print the answers to the serial monitor for debugging
  for (int i = 0; i < 12; i++) {
    Serial.println(String(answers[i]));
  }

  SendAnswers();         // see OOCSI tab for details

  player.PlayOutro();    // Anything after playig the sound will happen during the playing, beware of this
  delay (10000);         // Waiting for the text to finish, this duration is based on the time of the outro

  Serial.printf("Try to play story for day %d \n", getCurrentDay());
  if (getCurrentDay() < 5) {
    player.PlayStory(storyParts[getCurrentDay()]);

  }
  updateState();
  delay (350000);
  blinkLights ();
  blinkLights ();
  //  blinkLights ();

  Serial.println("end of the program");
}

/***************************************************/

void loop() {}
