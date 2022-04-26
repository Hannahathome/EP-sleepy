/*
  Functions you can call from this file:

  checkButton ();

  checks if buttons are being pressed, prints which ones.

*/



void checkButton () {
  int answerOne = digitalRead(BUTTON_ONE);
  int answerTwo = digitalRead(BUTTON_TWO);
  int answerThree = digitalRead(BUTTON_THREE);
  int answerFour = digitalRead(BUTTON_FOUR);
  int answerFive = digitalRead(BUTTON_FIVE);
  int replayQuestion = digitalRead(BUTTON_START);

  if (answerOne == 1) {
    Serial.println ("button 1 pressed");
    delay(500);                             //delay to prevent sending a lot of the same answers
  }
  if (answerTwo == 1) {
    Serial.println ("button 2 pressed");
    delay(500);                             //delay to prevent sending a lot of the same answers
  }
  if (answerThree == 1) {
    Serial.println ("button 3 pressed");
    delay(500);                             //delay to prevent sending a lot of the same answers
  }
  if (answerFour == 1) {
    Serial.println ("button 4 pressed");
    delay(500);                             //delay to prevent sending a lot of the same answers
  }
  if (answerFive == 1) {
    Serial.println ("button 5 pressed");
    delay(500);                             //delay to prevent sending a lot of the same answers
  }
  if (replayQuestion == 1) {
    Serial.println ("replay sound");
    delay(500);                             //delay to prevent sending a lot of the same answers
  }
}


//check if the white button gets pressed (buttonWait(34);)
void buttonWait(int buttonPin) {
  Serial.println("waiting for button");
  int buttonState = 0;
  blinkNextButton ();
  while (1) {
    buttonState = digitalRead(BUTTON_START);
    if (buttonState == HIGH) {
      return;
    }
  }
}




//void getUserAnswer() {
//for (initialization; condition; increment) 
//
//int QUESTION_NUM = 12;
//  byte code[QUESTION_NUM];
//
//  int answerOne = digitalRead(BUTTON_ONE);
//  int answerTwo = digitalRead(BUTTON_TWO);
//  int answerThree = digitalRead(BUTTON_THREE);
//  int answerFour = digitalRead(BUTTON_FOUR);
//  int answerFive = digitalRead(BUTTON_FIVE);
//  int replayQuestion = digitalRead(BUTTON_START);
//
//  if (answerOne) add(1);
//  else if (answerTwo) add(2);
//  else if (answerThree) add(3);
//  else if (answerFour) add(4);
//  else if (answerFive) add(5);
//  else if (replayQuestion) {
//    sendCommand(PLAY_W_INDEX, FOLDER_ONE, Q1);
//  }
//}



//
//class Buttons {
//public:
//  Buttons();
//
//  void PlayStartAnimation();
//  void ShowNextButtonAndWait();
//  std::string GetUserAnswer();
//};
//
//Buttons::Buttons() {}
//
//void Buttons::PlayStartAnimation() {
//  std::cout << "The buttons are making a fun pattern so you know it's working\n";
//
//}
//
//void Buttons::ShowNextButtonAndWait() {
//  system("pause");
//}
//
//std::string Buttons::GetUserAnswer() {
//  std::cout << "type your answer here: ";
//  std::string answer;
//  std::cin >> answer;
//  return answer;
//}
