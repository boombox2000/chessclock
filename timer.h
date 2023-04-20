#ifndef TIMER_H
#define TIMER_H
#include <Arduino.h>
#include "global.h"
#include "display.h"
#include "player.h"
#include "timeControl.h"

unsigned long lastLoopTime = 0;

int Hour = 0;
int Min = 10;
int Sec = 0;

const uint8_t dots = 0b01000000;

// Function to display the initial times for the players
void setStartTime(TM1637TinyDisplay d1, TM1637TinyDisplay d2, TimeControl time) {
  // Compute the values
  Serial.println("in setStartTime");

  Serial.println(time.initialTime);
  unsigned long MINUTES1 = numberOfMinutes(time.initialTime / 1000);
  unsigned long SECONDS1 = numberOfSeconds(time.initialTime / 1000);
  Serial.println("in minutes");

  Serial.println(MINUTES1);
  // Convert time values to integer to display
  d1.showNumberDec(MINUTES1, dots, true, 2, 0);
  d1.showNumberDec(SECONDS1, dots, true, 2, 2);

  unsigned long MINUTES2 = numberOfMinutes(time.initialTime / 1000);
  unsigned long SECONDS2 = numberOfSeconds(time.initialTime / 1000);
  // Convert time values to integer to display

  d2.showNumberDec(MINUTES2, dots, true, 2, 0);
  d2.showNumberDec(SECONDS2, dots, true, 2, 2);
}

// void continueGameTimer(TM1637TinyDisplay d1, TM1637TinyDisplay d2, unsigned long initialTime, unsigned long startTime) {
//   Serial.println("in continueGameTimer");

// }

void handleTimer(TM1637TinyDisplay d1, TM1637TinyDisplay d2, unsigned long initialTime, unsigned long startTime) {
  // d.begin();
  unsigned long timeNow = millis();
  unsigned long timeElapsed = timeNow - startTime;    // amount of time since start
  unsigned long counter = initialTime - timeElapsed;  // current state of initialTime
  d2.showNumberDec(43, dots, true, 2, 2);
  d2.showNumberDec(34, dots, true, 2, 0);

  // Update Display - every 10ms
  if (timeNow - lastLoopTime >= 10) {
    lastLoopTime = timeNow;  // remember last time we displayed

    if (timeElapsed >= initialTime) {
      // If we hit zero - flash every second
      unsigned long since = (long)((timeElapsed - initialTime) / 500);
      if (since % 2) {
        d1.clear();
      } else {
        d1.showNumberDec(0, dots, true);  // Show 0 if timer has expired
      }
    } else {
      // Compute the values
      unsigned long MINUTES = numberOfMinutes(counter / 1000);
      unsigned long SECONDS = numberOfSeconds(counter / 1000);
      // Convert time values to integer to display
      d1.showNumberDec(MINUTES, dots, true, 2, 0);
      d1.showNumberDec(SECONDS, dots, true, 2, 2);
    }
  }
}
#endif
