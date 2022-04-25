#ifndef USE_SOFTWARESERIAL
#define USE_SOFTWARESERIAL 1      // Set to 1 to use SoftwareSerial library, 0 for native serial port
#endif

// LIBRARIES
//#include <OOCSI.h>              // send data to oocsi (not yet implemented)
//#include <EEPROM.h>             // saving data in the memory of ESP (not yet implemented)
#include <MD_YX5300.h>            // MD_YX5300 MP3 Player 

#if USE_SOFTWARESERIAL
#include <SoftwareSerial.h>

// other parts of the software
//#include "./Buttons.h"
//#include "./AudioPlayer.h"
//#include "./Question.h"
//#include "./Saver.h"

// Code outline
#include <string>

#include "./Buttons.h"
#include "./AudioPlayer.h"
#include "./Question.h"
#include "./Saver.h"

const int QUESTION_AMOUNT = 10;

int main() {
  Question questions[QUESTION_AMOUNT] = {
    { "Question 1 file location" },
    { "Question 2 file location" },
    { "Question 3 file location" },
    { "Question 4 file location" },
    { "Question 5 file location" },
    { "Question 6 file location" },
    { "Question 7 file location" },
    { "Question 8 file location" },
    { "Question 9 file location" },
    { "Question 10  file location" }
  };

  auto buttons = Buttons();
  auto player = AudioPlayer();

  buttons.PlayStartAnimation();
  player.PlayIntro();

  buttons.ShowNextButtonAndWait();

  std::string answers[QUESTION_AMOUNT] = {};
  for(int i = 0; i < QUESTION_AMOUNT; i++) {
    player.PlayQuestion(questions[i].audioFileLocation);
    answers[i] = buttons.GetUserAnswer();
  }

  auto saver = Saver();
  saver.Save(answers, QUESTION_AMOUNT);
  
  player.PlayOutro();
  player.PlayStory();
  player.PlayEndText();

  return 0;
}
