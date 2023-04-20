#ifndef TIMECONTROL_H
#define TIMECONTROL_H

#include "global.h"
#include "timer.h"
#include "display.h"

const uint8_t dotsConst = 0b01000000;

struct TimeControl {
  int initialTime = 0;
  int increment = (3 * 1000);
};

enum TimeControlType {
  TEN_FIVE,
  FIVE_ZERO,
  FIVE_THREE,
  TEN_ZERO,
  FIFTEEN_FIVE,
  THREE_THREE
};

const std::string TimeControlNames[] = { "10-5", " 5-0", " 5-3", "10-0", "15-5", " 3-3" };

// function to cycle through the enum values
TimeControlType getNextTimeControl(TimeControlType time) {
  return static_cast<TimeControlType>((static_cast<int>(time) + 1) % 6);
}

TimeControlType getPreviousTimeControl(TimeControlType time) {
  return static_cast<TimeControlType>((static_cast<int>(time) + 5) % 6);
}

TimeControl GetTimeControl(TimeControlType type) {

  TimeControl time;
  switch (type) {

    case TEN_FIVE:
      time.initialTime = 600000;
      time.increment = 5000;
      break;
    case FIVE_ZERO:
      time.initialTime = 300000;
      time.increment = 0;
      break;

    case FIVE_THREE:
      time.initialTime = 300000;
      time.increment = 3000;
      break;

    case TEN_ZERO:
      time.initialTime = 600000;
      time.increment = 0;
      break;

    case FIFTEEN_FIVE:
      time.initialTime = 900000;
      time.increment = 5000;
      break;

    case THREE_THREE:
      time.initialTime = 180000;
      time.increment = 3000;
      break;
  }
  return time;
}

void displayTimeControlSetup(TimeControlType type, TimeControl time, TM1637TinyDisplay d1, TM1637TinyDisplay d2) {
  Serial.println(time.initialTime);

  unsigned long MINUTES2 = numberOfMinutes(time.initialTime / 1000);
  unsigned long SECONDS2 = numberOfSeconds(time.initialTime / 1000);
  // Convert time values to integer to display
  d2.showNumberDec(MINUTES2, dotsConst, true, 2, 0);
  d2.showNumberDec(SECONDS2, dotsConst, true, 2, 2);
  std::string text = TimeControlNames[type];
  d1.showString(text.c_str());  //display setup
}

#endif