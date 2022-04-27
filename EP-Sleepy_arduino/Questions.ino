int playQuestion(uint8_t question, Buttons buttons, AudioPlayer player) {
  player.PlayQuestion(question);

  Serial.println("playingQuestion");
  delay (10000);
  Serial.println("Waiting for answer");

  while (1) {
    ButtonAnswer answer = buttons.GetInput();

    blinkButtonLights ();
    Serial.println("Waiting for answer");
    
    if (answer == ButtonAnswer::action) {
      Serial.println("replay question");
      player.PlayQuestion(question); //replay the current question
    }
    
    if (answer == ButtonAnswer::one) {
      Serial.println("answer 1");
      return 1;
    }
    
    if (answer == ButtonAnswer::two) {
      Serial.println("answer 2");
      return 2;
    }
    
    if (answer == ButtonAnswer::three) {
      Serial.println("answer 3");
      return 3;
    }
    
    if (answer == ButtonAnswer::four) {
      Serial.println("answer 4");
      return 4;
    }
    
    if (answer == ButtonAnswer::five) {
      Serial.println("answer 5");
      return 5;
    }
  }
  return -1;
}
