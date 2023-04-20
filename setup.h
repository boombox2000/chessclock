#ifndef SETUP_H
#define SETUP_H

#include "global.h"
#include "timer.h"
#include "timeControl.h"
#include "button.h"
#include "defaults.h"
#include "player.h"
#include "state.h"

void beginSetup() {
  // Record Epoch - Same as Timer Reset
  startTime = millis();

  timeControlSelected = previousTimeControlSelected = TEN_FIVE;
  timeControl = GetTimeControl(timeControlSelected);
  // timeControl.initialTime = hmsToMillis(Hour, Min, Sec);
  Serial.println(timeControl.initialTime);

  Serial.println("Setting Initial Players Times");
  initialTimePlayer1 = initialTimePlayer2 = remainingTimePlayer1 = remainingTimePlayer2 = timeControl.initialTime;

  //buttons
  button.setLongPressInterval(BUTTON_LONGTOUCH_INTERVAL);

  //display
  d1.begin();
  d2.begin();
  d1.setBrightness(0);
  d2.setBrightness(0);
  d1.flipDisplay(true);
  d2.flipDisplay(true);
  //setInitialPlayerTime();
  animationNum = 0;
  //state
  state = INITIALIZING;
};

#endif
