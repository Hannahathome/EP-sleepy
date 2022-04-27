/*
  Functions you can call from this file:

  checkButton ();

  checks if buttons are being pressed, prints which ones.

*/

#ifndef BUTTONS_H
#define BUTTONS_H

enum ButtonAnswer {
  unknown,
  one,
  two,
  three,
  four,
  five,
  action
};

class Buttons {
  public:
    //define the buttons pins
    static const int BUTTON_START = 34;  // GI(O)P 34 pin connected to button (CAREFUL! INPUT ONLY pin, this pin does not give any OUTPUT, so do not use if for that)
    static const int BUTTON_ONE = 27;    // GIOP 27 pin connected to button
    static const int BUTTON_TWO = 26;    // GIOP 26 pin connected to button
    static const int BUTTON_THREE = 25;  // GIOP 25 pin connected to button
    static const int BUTTON_FOUR = 33;   // GIOP 33 pin connected to button
    static const int BUTTON_FIVE = 32;   // GIOP 32 pin connected to button

    void Initialize() {
      pinMode(BUTTON_ONE, INPUT);
      pinMode(BUTTON_TWO, INPUT);
      pinMode(BUTTON_THREE, INPUT);
      pinMode(BUTTON_FOUR, INPUT);
      pinMode(BUTTON_FIVE, INPUT);
      pinMode(BUTTON_START, INPUT);
      Serial.println("Buttons setup");
    }

    ButtonAnswer GetInput () {
      if (digitalRead(BUTTON_START)) {
        return ButtonAnswer::action;
      }
      if (digitalRead(BUTTON_ONE)) {
        return ButtonAnswer::one;
      }
      if (digitalRead(BUTTON_TWO)) {
        return ButtonAnswer::one;
      }
      if (digitalRead(BUTTON_THREE)) {
        return ButtonAnswer::one;
      }
      if (digitalRead(BUTTON_FOUR)) {
        return ButtonAnswer::one;
      }
      if (digitalRead(BUTTON_FIVE)) {
        return ButtonAnswer::one;
      }

      return ButtonAnswer::unknown;
    }


    //check if the white button gets pressed (buttonWait(34);)
    void Wait(int buttonPin) {
      Serial.println("waiting for button");
      int buttonState = 0;
      blinkNextButton ();
      while (1) {
        blinkNextButton ();
        buttonState = digitalRead(BUTTON_START);
        if (buttonState == HIGH) {
          return;
        }
      }
    }
};


#endif
