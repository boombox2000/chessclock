#include <Arduino.h>

#include "global.h"
#include "timer.h"
#include "timeControl.h"
#include "state.h"
#include "setup.h"
#include "defaults.h"
#include "button.h"
#include "display.h"
#include "animation.h"
#include "player.h"

State state;
TM1637TinyDisplay d1(CLK1, DIO1);
TM1637TinyDisplay d2(CLK2, DIO2);
TimeControl timeControl;
TimeControlType timeControlSelected;
TimeControlType previousTimeControlSelected;

AcksenButton button = AcksenButton(BUTTON_INPUT_IO, ACKSEN_BUTTON_MODE_LONGPRESS, BUTTON_DEBOUNCE_INTERVAL, INPUT);
AcksenButton buttonSwitch = AcksenButton(SWITCH_INPUT_IO, ACKSEN_BUTTON_MODE_NORMAL, BUTTON_DEBOUNCE_INTERVAL, INPUT);

unsigned long startTime = 0;
unsigned long initialTime = 0;

void setup() {
  Serial.begin(115200);
  beginSetup();
}

void loop() {

  bool isAnimationRunning = d1.Animate();
  d2.Animate();

  switch (state) {
    case INITIALIZING:
      Serial.println("In INITIALIZING");
      // if (!isAnimationRunning) {
      // clear display and pause before starting the non-blocking animation/scrolling
      d1.clear();
      d2.clear();
      //delay(500);

      //   // switch to the next animation/scrolling to run
      //   animationNum++;
      //   Serial.println("");
      //   Serial.println("Animate from SRAM");
      //   // non-blocking animation from SRAM
      //   d1.startAnimation(ANIMATION, FRAMES(ANIMATION), TIME_MS(50));
      //   d2.startAnimation(ANIMATION, FRAMES(ANIMATION), TIME_MS(50));
      //   break;
      // } else {
      //   waitingForInput = false;
      //   state = GAME_WAITING;
      //   break;
      // }
      state = GAME_WAITING;
      break;  // add break statement here

    case GAME_WAITING:
      Serial.println("In GAME_WAITING");
      setStartTime(d1, d2, timeControl);
      waitingForInput = true;

      while (waitingForInput == true) {
        Serial.println("In GAME_WAITING FOR INPUT");
        checkButtonStatus(button, waitingForInput, state); //isolated button check seperate from main loop.
        delay(200);
      }

      //state = GAME_STARTED;
      break;
    case GAME_STARTED:
      Serial.println("In GAME_STARTED");
      handleTimer(d1,d2,initialTime,startTime);
      delay(10);
      break;  // add break statement here

    case GAME_PAUSED:
      Serial.println("In GAME_PAUSED");
      // long press in GAME_STARTED can pause
      break;  // add break statement here

    case GAME_OVER:
      Serial.println("In GAME_OVER");
      break;  // add break statement here

    case SET_GAME_TIME:
      Serial.println("In SET_GAME_TIME");
      timeControl = GetTimeControl(timeControlSelected);
      if (timeControlSelected != previousTimeControlSelected) {
        previousTimeControlSelected = timeControlSelected; //helps remove flicker from screen
        displayTimeControlSetup(timeControlSelected,timeControl,d1,d2);
      }
      delay(50);
      break;  // add break statement here

    default:
      // handle default case here
      break;
  }

  button.refreshStatus();
 buttonSwitch.refreshStatus();

  if ((state == SET_GAME_TIME) && (button.onLongPress())) {
      Serial.println("***pressed LONG LONG LONG*** in set game state");

      //hack because button press is registered before long press.
      timeControlSelected = getPreviousTimeControl(timeControlSelected);
      timeControl = GetTimeControl(timeControlSelected);
      initialTimePlayer1 = initialTimePlayer2 = remainingTimePlayer1 = remainingTimePlayer2 = timeControl.initialTime;
      state = GAME_WAITING;
  } else if ((state == SET_GAME_TIME) && (button.onPressed())) {
      Serial.println("***pressed*** in set game state");
      timeControlSelected = getNextTimeControl(timeControlSelected);
      Serial.println(timeControlSelected);
      delay(10);
  }
  if ((state == GAME_WAITING) && (button.onPressed())) {
      Serial.println("***pressed*** in GAME_WAITING");
      state = GAME_STARTED;
  }
  
}