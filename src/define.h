#ifndef METRONOME_DEFINE_H
#define METRONOME_DEFINE_H

#include <Arduino.h>

/// define ////////////////////////////////////////////////

#define LED_KEY_S1  0b00000001
#define LED_KEY_S2  0b00000010
#define LED_KEY_S3  0b00000100
#define LED_KEY_S4  0b00001000
#define LED_KEY_S5  0b00010000
#define LED_KEY_S6  0b00100000
#define LED_KEY_S7  0b01000000
#define LED_KEY_S8  0b10000000

#define SPEAKER_PIN             8
#define ROTARY_ENCODER_A        7
#define ROTARY_ENCODER_B        6
#define ROTARY_ENCODER_PUSH     5

#define INITIAL_BPM           120
#define INITIAL_CLICK           1

#define BPM_MIN                30
#define BPM_MAX               255
#define CLICK_MIN               1
#define CLICK_MAX               9

#define FREQUENCY_LOW         880     // click frequency
#define DURATION_LOW           50     // click duration
#define FREQUENCY_HIGH       1760
#define DURATION_HIGH          50

enum STATE {
    STOP, START, RUN, CHANGE_CLICK,
    START_FROM_CHANGE_CLICK, CHANGE_CLICK_FROM_STOP,
};

enum class M_State {
    STOP, START, RUN, CHANGE_CLICK, RESUME_FROM_CHANGE_CLICK,
};

#endif //METRONOME_DEFINE_H
