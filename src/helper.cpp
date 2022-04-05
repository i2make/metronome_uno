#include "helper.h"

void toneLow() {
    tone(SPEAKER_PIN, FREQUENCY_LOW, DURATION_LOW);
}

void toneHigh() {
    tone(SPEAKER_PIN, FREQUENCY_HIGH, DURATION_HIGH);
}

void led_key_display_update() {

    String sBpm;

    switch (mode) {
        case LED_KEY_S1:
            if (encoderBpm.getPosition() >= 100) {
                sBpm = "STOP " + String(encoderBpm.getPosition());
            } else {
                sBpm = "STOP  " + String(encoderBpm.getPosition());
            }
            module.setDisplayToString(sBpm);
            break;
        case LED_KEY_S2:
            if (encoderBpm.getPosition() >= 100) {
                sBpm = "RUN  " + String(encoderBpm.getPosition());
            } else {
                sBpm = "RUN   " + String(encoderBpm.getPosition());
            }
            module.setDisplayToString(sBpm);
            break;
        case LED_KEY_S3:
            // TODO:
            module.setDisplayToString(String("Clk n  " + String(encoderClick.getPosition())));
            break;
    }
}

void init_Click_and_Led() {
    previousLed = 8;
    previousClick = 255;
}

void led_key_read_button() {
    byte keys = module.getButtons();

    // Escape if the button is not pressed.
    if (keys == 0) {
        return;
    }

    // if the button is pressed.
    if (keys != previousKeys) {
        mode = keys;
        previousKeys = keys;
    } else {
        switch (mode) {
            case LED_KEY_S1:            /// Pause button
                status = STOP;
                break;
            case LED_KEY_S2:            /// Resume button
                if (status == STOP) {   // from STOP
                    status = START;
                    break;
                }
                if (status == CHANGE_CLICK) {   // from CHANGE_CLICK
                    status = START_FROM_CHANGE_CLICK;
                    break;
                }
                if (status == CHANGE_CLICK_FROM_STOP) {
                    status = START;
                }
                break;
            case LED_KEY_S3:            /// Change click button
                if (status == STOP) {
                    status = CHANGE_CLICK_FROM_STOP;
                }
                if (status == CHANGE_CLICK_FROM_STOP) {
                    return;
                }
                status = CHANGE_CLICK;
                break;
            case LED_KEY_S4:
                encoderBpm.setPosition(60);
                mode = 2;
                init_Click_and_Led();
                kjh_previous_millis = millis();
                break;
            case LED_KEY_S5:
                encoderBpm.setPosition(90);
                mode = 2;
                init_Click_and_Led();
                kjh_previous_millis = millis();
                break;
            case LED_KEY_S6:
                encoderBpm.setPosition(120);
                mode = 2;
                init_Click_and_Led();
                kjh_previous_millis = millis();
                break;
            case LED_KEY_S7:
                encoderBpm.setPosition(150);
                mode = 2;
                init_Click_and_Led();
                kjh_previous_millis = millis();
                break;
            case LED_KEY_S8:
                encoderBpm.setPosition(180);
                mode = 2;
                init_Click_and_Led();
                kjh_previous_millis = millis();
                break;
            default:
                break;
        }
    }

}

void led_key_LED_update(uint16_t bpm) {

    // clickDivider =  250 / 7.f;   // bpm = 480 ( 250 / led)
    // clickDivider =  500 / 7.f;   // bpm = 240 ( 500 / led)
    // clickDivider = 1000 / 7.f;   // bpm = 120 (1000 / led)
    // clickDivider = 2000 / 7.f;   // bpm =  60 (2000 / led)
    // clickDivider = 4000 / 7.f;   // bpm =  30 (4000 / led)
    static float divider;
    static byte direction;

    divider = float((1000 * (120.f / bpm)) / 7);

    kjh_current_millis = millis() - kjh_previous_millis;

    // Witch LED turn on?
    byte led = long(float(kjh_current_millis) / divider) % 7;
    //byte led = long(float(millis()) / clickDivider) % 7;

    if (led == previousLed) {
        return;
    }
    previousLed = led;

    if (direction == 0) {
        if (led == 6) {
            direction = 1;
        }
    } else {
        led = 7 - led;
        if (led == 1) {
            direction = 0;
        }
    }

    switch (led) {
        case 0:
            module.setLEDs(0b10000000);
            break;
        case 1:
            module.setLEDs(0b01000000);
            break;
        case 2:
            module.setLEDs(0b00100000);
            break;
        case 3:
            module.setLEDs(0b00010000);
            break;
        case 4:
            module.setLEDs(0b00001000);
            break;
        case 5:
            module.setLEDs(0b00000100);
            break;
        case 6:
            module.setLEDs(0b00000010);
            break;
        case 7:
            module.setLEDs(0b00000001);
            break;
    }
}

void sound_update(uint16_t _bpm, byte _divider) {

    // variable
    auto divider = float((1000 * (120.f / encoderBpm.getPosition())) / _divider); // 120 -> 1000
    byte click;

    // restart millis
    kjh_current_millis = millis() - kjh_previous_millis;

    if (_divider == 1) {
        click = long(float(kjh_current_millis) / divider) % 2; // 0 ~ 1
    } else {
        click = long(float(kjh_current_millis) / divider) % _divider; // 0 ~ _divider
    }

    // skip
    if (click == previousClick) {
        return;
    }
    previousClick = click;

    // making click
    if (click % _divider == 0) {
        toneHigh();
    } else {
        toneLow();
    }

}

void readRotaryEncoder(RotaryEncoder &_encoder, int _min, int _max) {

    _encoder.tick();

    // read position
    uint16_t newPos = _encoder.getPosition();

    // min & max blocking
    if (newPos < _min) {
        _encoder.setPosition(_min);
        return;
    } else if (newPos > _max) {
        _encoder.setPosition(_max);
        return;
    }

    // update position
    if (_encoder.getPosition() != newPos) {
//        Serial.print(newPos);
//        Serial.println();
        _encoder.setPosition(newPos);
    }
}