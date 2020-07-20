#ifndef dc
#include <Arduino.h>
class DcMotor
{
public:
    DcMotor(){};
    DcMotor(byte plusPin, byte minusPin, int rotDelay);
    void loop();
    void setup();
    void setPosition(int newPosition);

private:
    byte _plusPin;
    byte _minusPin;
    int _rotDelay;
    int _currentPosition;
    int _plannedPosition;
    unsigned long _oldTimeInt;
};

#endif