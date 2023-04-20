#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include <AcksenButton.h>

#include "global.h"
#include "state.h"

#define DEBUG_BAUD_RATE 115200
#define BUTTON_INPUT_IO 4
#define SWITCH_INPUT_IO 22

#define BUTTON_DEBOUNCE_INTERVAL 50     // Milliseconds
#define BUTTON_LONGTOUCH_INTERVAL 1500  // Milliseconds
bool waitingForInput = false;           //used to move through states of the game.

void checkButtonStatus(AcksenButton& button, bool& waitingForInput, State& state) {
  button.refreshStatus();
  if (button.onLongPress()) {
    Serial.println("***Button LONG Pressed!***");
    if (state == GAME_WAITING) {
      state = SET_GAME_TIME;
    }
  } else if (button.onReleased()) {
    Serial.println("***Button released!*** in GAME WAITING");
    if (state == GAME_WAITING) {
      state = GAME_STARTED;
    }
    waitingForInput = false;
  }
}

#endif