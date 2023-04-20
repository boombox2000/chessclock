#ifndef PLAYER_H
#define PLAYER_H

#include "global.h"
#include "timer.h"

bool isPlayer1Turn = true;  // Flag to keep track of which player is active
unsigned long initialTimePlayer1 = 0;
unsigned long initialTimePlayer2 = 0;
unsigned long remainingTimePlayer1 = initialTimePlayer1;
unsigned long remainingTimePlayer2 = initialTimePlayer2;

void setInitialPlayerTime() {
  // initialTimePlayer1 = timeControl.initialTime;
  // remainingTimePlayer1 = initialTimePlayer1;
  // initialTimePlayer2 = timeControl.initialTime;
  // remainingTimePlayer2 = initialTimePlayer2;
}

#endif
