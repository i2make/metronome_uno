#include "RotaryEncoder.h"
#include "helper.h"

/// variable /////////////////////////////////////////////////

byte previousLed = 8;       // non number of led value (0 ~ 7)
byte previousClick = 255;
byte previousKeys = 0;

// SPI setting
SPISettings led_key(1000000, LSBFIRST, SPI_MODE0);

// TM1638 board setting
TM1638 module(10, &led_key);

// Setup a RoraryEncoder for pins A2 and A3:
RotaryEncoder encoderBpm(ROTARY_ENCODER_A, ROTARY_ENCODER_B);
RotaryEncoder encoderClick(ROTARY_ENCODER_A, ROTARY_ENCODER_B);

byte mode;              // TM1638 board display mode

byte status = 0;        // machine status

volatile unsigned long kjh_current_millis;
volatile unsigned long kjh_previous_millis;

///////////////////////////////////////////////////////////////////////

void setup() {
    Serial.begin(115200);
    encoderBpm.setPosition(INITIAL_BPM);
    encoderClick.setPosition(INITIAL_CLICK);
    //pinMode(2, OUTPUT);
    mode = LED_KEY_S1;  // starting mode
}

void loop() {
    stateMap[0][0] = M_State::STOP;
    /// polling
    led_key_read_button();

    switch (status) {
        case STOP:
            /// change bpm
            readRotaryEncoder(encoderBpm, BPM_MIN, BPM_MAX);
            led_key_display_update();
            pinMode(SPEAKER_PIN, INPUT); // reduction noise
            return;
        case START:
            pinMode(SPEAKER_PIN, OUTPUT); // restart pin
            // restart beat
            init_Click_and_Led();
            kjh_previous_millis = millis(); // initialize millis
            status = RUN;
            break;
        case RUN:
            /// change bpm
            readRotaryEncoder(encoderBpm, BPM_MIN, BPM_MAX);
            led_key_display_update();
            break;
        case CHANGE_CLICK:
            /// change click
            readRotaryEncoder(encoderClick, CLICK_MIN, CLICK_MAX);
            led_key_display_update();
            break;
        case RESUME_FROM_CHANGE_CLICK:
            // TODO:
            pinMode(SPEAKER_PIN, OUTPUT); // restart pin
            status = RUN;
        default:
            break;
    }

    sound_update(encoderBpm.getPosition(), encoderClick.getPosition());
    led_key_display_update();
    led_key_LED_update(encoderBpm.getPosition());
}

