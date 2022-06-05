int playQuestion(uint8_t question, Buttons buttons, AudioPlayer player) {
  bool firstPlay = true;
  
  while (1) {
    // Blink the buttons and wait for user input
    Serial.println("Waiting for answer");
    blinkButtonLightsAsync ();
    ButtonAnswer buttonAnswer = buttons.GetInput();
    
    // On first play or on the action button, play question    
    if (buttonAnswer == ButtonAnswer::action || firstPlay) {
      firstPlay = false;
      lightsOff();
      
      Serial.println("playing question");
      player.PlayQuestion(question);
      delay (10000);
    }

    // If a button was pressed, print this and return answer
    else if (buttonAnswer != ButtonAnswer::unknown) {
      lightsOff();
      Serial.print("answer ");
      Serial.println(static_cast<int>(buttonAnswer));
      return static_cast<int>(buttonAnswer);
    }
  }
}
