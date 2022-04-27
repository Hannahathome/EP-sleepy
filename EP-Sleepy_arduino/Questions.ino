int answerOne = 0;
int answerTwo = 0;
int answerThree = 0;
int answerFour = 0;
int answerFive = 0;
int replayQuestion = 0;

int CurrentQuestion = 0;

void playQuestion(uint8_t question) {
  sendCommand(PLAY_W_INDEX, FOLDER_ONE, question);

  Serial.println("playingQuestion");
  delay (10000);
  Serial.println("Waiting for answer");

  while (1) {
    int answerOne = digitalRead(BUTTON_ONE);
    int answerTwo = digitalRead(BUTTON_TWO);
    int answerThree = digitalRead(BUTTON_THREE);
    int answerFour = digitalRead(BUTTON_FOUR);
    int answerFive = digitalRead(BUTTON_FIVE);
    int replayQuestion = digitalRead(BUTTON_START);
    blinkButtonLights ();
    Serial.println("Waiting for answer");

    if (replayQuestion == HIGH) {
      Serial.println("replay question");
      sendCommand(PLAY_W_INDEX, FOLDER_ONE, Q1); //replay the current question
    }
    
    if (answerOne == HIGH) {
      Serial.println("answer 1");
      answers[CurrentQuestion] = 1;
      CurrentQuestion++; //replay the current question
      return;
    }
    if (answerTwo == HIGH) {
      Serial.println("answer 2");
      answers[CurrentQuestion] = 2;
      CurrentQuestion ++; //replay the current question
      return;
    }
    if (answerThree == HIGH) {
      Serial.println("answer 3");
      answers[CurrentQuestion] = 3;
      CurrentQuestion++; //replay the current question
      return;
    }
    if (answerFour == HIGH) {
      Serial.println("answer 4");
      answers[CurrentQuestion] = 4;
      CurrentQuestion++; //replay the current question
      return;
    }
    if (answerFive == HIGH) {
      Serial.println("answer 5");
      answers[CurrentQuestion] = 5;
      CurrentQuestion++; //replay the current question
      return;
    }
  }
  Serial.println("answered!");
}
