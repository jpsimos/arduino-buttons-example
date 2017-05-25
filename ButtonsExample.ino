/* Arduino Momentary Contact Buttons Example */
/* Uses two normally closed momentary contact buttons */
/* Author Jacob Psimos 5/25/2017 */

#include "Buttons.h"

void buttonEvent(byte btnStatus, unsigned int duration);

Buttons buttons(NULL);

void setup() {
  Serial.begin(115200);
  buttons = Buttons(buttonEvent);
}

void loop() {
  buttons.tick();
}

void buttonEvent(byte btnStatus, unsigned int duration){
  Serial.print("[Button] ");
  
  if(btnStatus & DBL_HANDLE){
    Serial.print("both");
  }else if(btnStatus & BUTTON1_HANDLE){
    Serial.print("button 1");
  }else if(btnStatus & BUTTON2_HANDLE){
    Serial.print("button 2");
  }
  
  Serial.print("\tDuration: ");
  Serial.print(duration, DEC);
  Serial.print("\r\n");
}

