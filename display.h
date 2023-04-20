#ifndef display_H
#define display_H

#include <TM1637TinyDisplay.h>

#define CLK1 16
#define DIO1 17
#define CLK2 18
#define DIO2 19

// uint8_t dots = 0b01000000;  // Add dots or colons (depends on display module)

/* Useful Constants */
#define SECS_PER_MIN (60UL)
#define SECS_PER_HOUR (3600UL)
#define SECS_PER_DAY (SECS_PER_HOUR * 24L)

/* Useful Macros for time (s) */
#define numberOfSeconds(_time_) (_time_ % SECS_PER_MIN)
#define numberOfMinutes(_time_) ((_time_ / SECS_PER_MIN) % SECS_PER_MIN)
#define numberOfHours(_time_) ((_time_ % SECS_PER_DAY) / SECS_PER_HOUR)
#define elapsedDays(_time_) (_time_ / SECS_PER_DAY)
#define hmsToMillis(_h_, _m_, _s_) ((_h_ * SECS_PER_HOUR) + (_m_ * SECS_PER_MIN) + _s_) * 1000ul;

// void blinkDisplay(TM1637TinyDisplay& display, uint16_t interval_ms) {
//     uint32_t last_blink_time = millis();
//     bool display_on = true;
    
//     while (true) {
//         uint32_t current_time = millis();
        
//         if ((current_time - last_blink_time) >= interval_ms) {
//             display.setDisplayOn(display_on);
//             display_on = !display_on;
//             last_blink_time = current_time;
//         }
//     }
// }

#endif