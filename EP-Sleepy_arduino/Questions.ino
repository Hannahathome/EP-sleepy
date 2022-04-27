int answerOne = 0;
int answerTwo = 0;
int answerThree = 0;
int answerFour = 0;
int answerFive = 0;
int replayQuestion = 0;


int CurrentQuestion = 1;

void playQuestionOne () {
  sendCommand(PLAY_W_INDEX, FOLDER_ONE, Q1);
  
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
      CurrentQuestion++; //replay the current question
      return;
    }
    if (answerTwo == HIGH) {
      Serial.println("answer 2");

      CurrentQuestion ++; //replay the current question
      return;
    }
    if (answerThree == HIGH) {
      Serial.println("answer 3");

      CurrentQuestion++; //replay the current question
      return;
    }
    if (answerFour == HIGH) {
      Serial.println("answer 4");

      CurrentQuestion++; //replay the current question
      return;
    }
    if (answerFive == HIGH) {
      Serial.println("answer 5");

      CurrentQuestion++; //replay the current question
      return;
    }
  }
  Serial.println("answered!");
}

//char Q = 'Q';
//int CurrentQuestion = 2; //oke ik probeerde hier en met het char question gedeelte hironder een makkelijker iets te amken dan de12 if statemetns, maar k krijgt het niet wekrend. jij een idee?
//int CurrentQuestion = 0;

//void playQuestions () {
//
//  for (int i = 0; i < QUESTION_AMOUNT; i++) {
//    //char QUESTION = '(Q + CurrentQuestion)'; //the command for the question that needs to be played is Q+ the number of the quesiton
//
//    char QUESTION =
//    sendCommand(PLAY_W_INDEX, FOLDER_ONE, QUESTION);
//    Serial.println("playingQuestion");
//    delay (17000);
//    Serial.println("waiting for answer");
//
//
//    while (1) {
//      int answerOne = digitalRead(BUTTON_ONE);
//      int answerTwo = digitalRead(BUTTON_TWO);
//      int answerThree = digitalRead(BUTTON_THREE);
//      int answerFour = digitalRead(BUTTON_FOUR);
//      int answerFive = digitalRead(BUTTON_FIVE);
//      int replayQuestion = digitalRead(BUTTON_START);
//      blinkButtonLights ();
//
//      if (replayQuestion == HIGH) {
//        Serial.println("replay question");
//        //sendCommand(PLAY_W_INDEX, FOLDER_ONE, QUESTION); //replay the current question
//        return;
//      }
//      if (answerOne == HIGH) {
//        Serial.println("answer 1");
//        CurrentQuestion++; //replay the current question
//        return;
//      }
//      if (answerTwo == HIGH) {
//        Serial.println("answer 2");
//
//        CurrentQuestion ++; //replay the current question
//        return;
//      }
//      if (answerThree == HIGH) {
//        Serial.println("answer 3");
//
//        CurrentQuestion++; //replay the current question
//        return;
//      }
//      if (answerFour == HIGH) {
//        Serial.println("answer 4");
//
//        CurrentQuestion++; //replay the current question
//        return;
//      }
//      if (answerFive == HIGH) {
//        Serial.println("answer 5");
//
//        CurrentQuestion++; //replay the current question
//        return;
//      }
//    }
//    Serial.println("answered!");
//  }
//}
//
