/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-save-data-permanently-preferences/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <Preferences.h>

Preferences preferences;

int dayNumber;

void stateInitialization() {
  //Create a namespace called "state" = section in the flash memory to save the state. it is set to 0 if no state is found
  preferences.begin("stateSpace", false); //false is read write mode 

  // read the last system state from flash memory
  dayNumber = preferences.getInt("systemStateKey", 0);

  Serial.printf("system state before reset: %d \n", dayNumber);
}

void updateState() {
  dayNumber++; 
  preferences.putInt("systemStateKey", dayNumber);   // save the new daynumber in flash memory
  Serial.printf("State saved: %d \n", preferences.getInt("systemStateKey", 0));
}
