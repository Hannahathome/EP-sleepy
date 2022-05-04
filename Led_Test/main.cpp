#include <iostream>

// The different blinking patterns that our LEDs can have
enum LEDState {
  OFF,
  ON,
  KITT
};

// This is an abstract class. This means that the class does not have any implementation.
// To use a class that derives from this class, we need to use a pointer to an object of 
// type LEDStateBase. That would look like for instance:
//
// LEDStateBase* state = new LEDStateOff;
//
// We have to use a pointer because this is the way that we can use interfaces in c++.
// Because we create an object using the 'new' keyword. We must also clean it up when we
// reassign the variable ('state' in our example), and when we destroy the objet 
// containing the pointer to the object. Then this delete is done in the destructor (the)
// function with a ~ in front of it. 
class LEDStateBase {
public:
  virtual void Update() = 0;
};

// Below are several implementations of the abstract class, each belong to one of the LED 
// states defined above.
class LEDStateOn: public LEDStateBase {
public:
  void Update() {
    std::cout << "On\n";
  }
};

class LEDStateOff: public LEDStateBase {
public:
  void Update() {
    std::cout << "Off\n"; 
  }
};

class LEDStateKitt: public LEDStateBase {
  int current = 0;
  bool backwards = false;

public:
  void Update() {
    for(int i = 0; i < 5; i++) {
      if(i == current) {
        std::cout <<  "1";
      } 
      else {
        std::cout << "0";
      }
    }
    std::cout << "\n";
    if(backwards) {
      current--;
    }
    else {
      current++;
    }
    if(current == 0 || current == 4) {
      backwards = !backwards;
    }

  }
};

// Out class that handles showing the LEDs using an LEDStateBase*
class LEDs {
  LEDStateBase* state = new LEDStateOff();

public:
  void Update() {
    state->Update(); // Call the update function on the state object
  }

  void SetState(LEDState newState) {
    delete state; // Delete the old state object

    // Set the new state
    if(newState == LEDState::OFF) { state = new LEDStateOff(); }
    if(newState == LEDState::ON) { state = new LEDStateOn(); }
    if(newState == LEDState::KITT) { state = new LEDStateKitt(); }
  }

  ~LEDs() {
    delete state;
  }
};

// Some simple test code
int main() {
  LEDs leds = LEDs();
  leds.SetState(LEDState::KITT);
  int count = 0;
  while(1) {
    leds.Update();

  } 

  return 0;
}