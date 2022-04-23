// Code outline
#include "./Buttons.h"
#include "./AudioPlayer.h"
#include "./Question.h"
#include "./Saver.h"

const int QUESTION_AMOUNT = 10;

int main() {
  Question questions[QUESTION_AMOUNT] = {};

  auto buttons = Buttons();
  auto player = AudioPlayer();

  buttons.PlayStartAnimation();
  player.PlayIntro();

  buttons.ShowNextButtonAndWait();

  int answers[QUESTION_AMOUNT] = {};
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