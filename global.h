#ifndef GLOBAL_H
#define GLOBAL_H

#include "timer.h"
#include "timeControl.h"
#include "player.h"
#include "button.h"
#include "state.h"
#include "display.h"

extern State state;
extern TM1637TinyDisplay d1;
extern TM1637TinyDisplay d2;
extern byte animationNum;

extern unsigned long startTime;
extern bool touchTriggered;
extern bool isPlayer1Turn;
extern unsigned long initialTimePlayer1;
extern unsigned long initialTimePlayer2;
extern unsigned long remainingTimePlayer1;
extern unsigned long remainingTimePlayer2;
extern int Hour;
extern int Min;
extern int Sec;
extern TimeControlType timeControlSelected;
extern TimeControlType previousTimeControlSelected;
extern TimeControl timeControl;

//buttons
extern AcksenButton button;

#endif  // GLOBAL_H
