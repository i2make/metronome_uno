#ifndef METRONOME_HEPLER_H
#define METRONOME_HEPLER_H

#include "define.h"
#include "TM1638.h"
#include "RotaryEncoder.h"

void tone01();

void led_key_display_update();

void led_key_read_button();

void init_Click_and_Led();

void led_key_LED_update(uint16_t bpm);

void sound_update(uint16_t bpm, byte divider);

void readRotaryEncoder(RotaryEncoder& _encoder, int _min, int _max);


extern TM1638 module;
extern byte mode;              // led display mode

extern byte status;

extern byte previousLed;
extern byte previousClick;
extern byte previousKeys;

extern RotaryEncoder encoderBpm;
extern RotaryEncoder encoderClick;

//extern volatile unsigned long timer0_millis;

extern volatile unsigned long kjh_current_millis;
extern volatile unsigned long kjh_previous_millis;

extern M_State stateMap[5][2];

#endif //METRONOME_HEPLER_H
