#ifndef __BUTTONS__
#define __BUTTONS__

/*
 * Author Jacob Psimos 5/25/2017
 * Version 3
 * 
 * Detects button presses and press duration
 * The button event is called after a press and release has occured, returning the details of the event with it.
 * Handles two buttons and events caught are: Button 1 press, Button 2 press, Both buttons press
 */

#define BUTTON1_OUTPUT_PIN A0
#define BUTTON1_INPUT_PIN A1
#define BUTTON2_OUTPUT_PIN A4
#define BUTTON2_INPUT_PIN A5

#define BUTTON1_DOWN 0x01
#define BUTTON2_DOWN 0x02
#define DBL_DOWN 0x04
#define BUTTON1_HANDLE 0x08
#define BUTTON2_HANDLE 0x10
#define DBL_HANDLE 0x20

#define BUTTON_DURATION_MIN 140   //Minimum amount of milliseconds for button press to register
#define BUTTON_DURATION_MAX 2000  //Maximum amount of milliseconds a button can be held down to be considered valid. Prevents sticky button.

class Buttons{
  public:
  
    Buttons(void (*)(byte, unsigned int));
    void tick(void);

  private:
    void (*buttonEvent)(byte btnStatus, unsigned int duration);
    byte btnStatus;
    unsigned long button1_start;
    unsigned long button2_start;
    unsigned int button1_duration;
    unsigned int button2_duration;
};

Buttons::Buttons(void (*buttonEvent)(byte, unsigned int)){
  this->buttonEvent = buttonEvent;
  btnStatus = 0;
  button1_start = 0;
  button2_start = 0;
  button1_duration = 0;
  button2_duration = 0;
  pinMode(BUTTON1_OUTPUT_PIN, OUTPUT);          //Connected to button 1
  pinMode(BUTTON1_INPUT_PIN, INPUT_PULLUP);    //Connected to button 1
  pinMode(BUTTON2_OUTPUT_PIN, OUTPUT);          //Connected to button 2
  pinMode(BUTTON2_INPUT_PIN, INPUT_PULLUP);    //Connected to button 2
  digitalWrite(BUTTON1_OUTPUT_PIN, LOW);
  digitalWrite(BUTTON2_OUTPUT_PIN, LOW);
}

void Buttons::tick(void){
  byte _button1 = (byte)digitalRead(BUTTON1_INPUT_PIN);
  byte _button5 = (byte)digitalRead(BUTTON2_INPUT_PIN);
  
  unsigned long now = millis();

  /* Button Presses */

  if( _button1 == HIGH && !(btnStatus & BUTTON1_DOWN) ){
    btnStatus |= BUTTON1_DOWN;
    button1_start = now;
  }

  if( _button5 == HIGH && !(btnStatus & BUTTON2_DOWN) ){
    btnStatus |= BUTTON2_DOWN;
    button2_start = now;
  }

  if( _button1 == HIGH && _button5 == HIGH && !(btnStatus & DBL_DOWN) ){
    btnStatus |= DBL_DOWN;
  }

  /* Button Releases */
  
  if( _button1 == LOW && (btnStatus & BUTTON1_DOWN) ){
    btnStatus &= ~BUTTON1_DOWN;
    button1_duration = (unsigned int)(now - button1_start);
    if(button1_duration >= BUTTON_DURATION_MIN && button1_duration <= BUTTON_DURATION_MAX){
      btnStatus |= BUTTON1_HANDLE;
    }else{
      btnStatus &= ~BUTTON1_HANDLE;
    }
  }

  if( _button5 == LOW && (btnStatus & BUTTON2_DOWN) ){
    btnStatus &= ~BUTTON2_DOWN;
    button2_duration = (unsigned int)(now - button2_start);
    if(button2_duration >= BUTTON_DURATION_MIN && button2_duration <= BUTTON_DURATION_MAX){
      btnStatus |= BUTTON2_HANDLE;
    }else{
      btnStatus &= ~BUTTON2_HANDLE;
    }
  }

  if( _button1 == LOW && _button5 == LOW && (btnStatus & DBL_DOWN) ){
    btnStatus &= ~DBL_DOWN;
    if( (btnStatus & BUTTON1_HANDLE) && (btnStatus & BUTTON2_HANDLE) ){
      btnStatus |= DBL_HANDLE;
    }else{
      btnStatus &= ~DBL_HANDLE;
    }
  }

  /* Process Handlers - A button(s) have been pressed and released */
  if( !(btnStatus & (BUTTON1_DOWN | BUTTON2_DOWN | DBL_DOWN)) && (btnStatus >= BUTTON1_HANDLE) ){
    if(buttonEvent != (void (*)(byte, unsigned int))NULL){
      buttonEvent(btnStatus, button1_duration > button2_duration ? button1_duration : button2_duration);
    }
    button1_start = 0;
    button2_start = 0;
    button1_duration = 0;
    button2_duration = 0;
    btnStatus &= ~(BUTTON1_HANDLE | BUTTON2_HANDLE | DBL_HANDLE);
  }
}



#endif
