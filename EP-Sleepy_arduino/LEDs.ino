/* LIGHT CONTROL EXPLANATION
   QA, QB, QC... QH are the pins on the Shiftregister.
   QH = led 1 = white LEDbutton = 0x00000001
   QG-QB = blue LEDbuttons = 0x000000010, 0x000000100 etc
   you can turn them on individually using the storageByte = 0xXXXXXXX command
   and then updating the shiftregister.
*/

/*
  Functions you can call from this file:

  walkingLights ();
  blinkLights ();
  blinkButtonLights (); (dont blink the white buttons light)
  lightsOn ();
  lightsOff ();
  blinkNextButton (); only blink white button

*/

// function which sends the stored byte to the output pins by setting the latch pin LOW
void updateShiftRegister(byte storageByte) {
  digitalWrite(latchPin, LOW);                          // set the latch pin LOW
  shiftOut(dataPin, clockPin, LSBFIRST, storageByte);   // send the storage byte to the shift register with the LSB first, since the latch is LOW, set the 8 output pins based on the stored 8 bits and in turn light the correct LED
  digitalWrite(latchPin, HIGH);                         // set the latch pin HIGH again
}


void walkingLights () {
  byte storageByte = 0x01;                    // the byte (8 bits) to be stored in the shift register, initialize to 00000001, representing the first LED on

  for (int i = 0; i < NUM_LEDS - 1; i++)  {   // create the effect of having the light travel to the left
    updateShiftRegister(storageByte);         // send the 8 bits to the shift register and set latch LOW
    storageByte = storageByte << 1;           // bitwise shift to the left by 1 bit the MSB will disappear and a 0 will be shifted in for the LSB
    //  example: 10000001 to 00000010

    delay(delayTime);                         // wait before moving on to the next LED to enhance the animation
  }

  for (int i = 0; i < NUM_LEDS - 1; i++)  {   // create the effect of having the light travel in the opposite direction
    updateShiftRegister(storageByte);         // send the 8 bits to the shift register and set latch LOW
    storageByte = storageByte >> 1;           // bitwise shift to the right by 1 bit, the LSB will disappear and a 0 will be shifted in for the MSB
    //     i.e. 10000000 to 01000000
    delay(delayTime);                         // wait before moving on to the next LED to enhance the animation
  }
}

void blinkLights () {
  storageByte = 0b11111111;                   // command to turn on all lights
  updateShiftRegister(storageByte);           // send the 8 bit command to the shift register and set latch LOW
  delay(delayTime);                           // wait
  storageByte = 0b00000000;                   // command to turn off all lights
  updateShiftRegister(storageByte);           // send the 8 bit command to the shift register and set latch LOW
  delay(delayTime);                           // wait
}


void blinkButtonLights () {
  storageByte = 0b01111111;                   // command to turn on all lights except the first (white LED, QH)
  updateShiftRegister(storageByte);           // send the 8 bit command to the shift register and set latch LOW
  delay(delayTime);                           // wait
  storageByte = 0b00000000;                   // command to turn off all lights
  updateShiftRegister(storageByte);           // send the 8 bit command to the shift register and set latch LOW
  delay(delayTime);                           // wait
}

void blinkNextButton () {
  storageByte = 0b10000001;                   // command to turn on all lights except the first (white LED, QH)
  updateShiftRegister(storageByte);           // send the 8 bit command to the shift register and set latch LOW
  delay(delayTime);                           // wait
  storageByte = 0b00000000;                   // command to turn off all lights
  updateShiftRegister(storageByte);           // send the 8 bit command to the shift register and set latch LOW
  delay(delayTime);                           // wait
}


void lightsOn () {
  storageByte = 0b11111111;
  updateShiftRegister(storageByte);
}

void lightsOff () {
  storageByte = 0b00000000;
  updateShiftRegister(storageByte);
}
