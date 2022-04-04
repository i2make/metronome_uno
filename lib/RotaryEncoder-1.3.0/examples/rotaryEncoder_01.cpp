/*
#include <RotaryEncoder.h>

// Setup a RoraryEncoder for pins A2 and A3:
RotaryEncoder encoderBpm(12, 13); //DT = 12, CLK = 13

void setup()
{
    Serial.begin(9600);
    Serial.println("SimplePollRotator example for the RotaryEncoder library.");
} // setup()


// Read the current position of the encoderBpm and print out when changed.
void loop()
{
    static int pos = 0; // 좌표
    encoderBpm.tick(); // 로터리 엔코더의 상태 확인

    int newPos = encoderBpm.getPosition();
    if (pos != newPos) {
        Serial.print(newPos);
        Serial.print(' ');
        pos = newPos;
    } // if
} // loop ()

// The End

*/
