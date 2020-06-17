#include "DcMotor.h"

DcMotor::DcMotor(byte plusPin, byte minusPin, int rotDelay)
{
    _plusPin = plusPin;
    _minusPin = minusPin;
    _rotDelay = rotDelay;
    _oldTimeInt = millis();
    _currentPosition = 0;
    _plannedPosition = 0;
}

void DcMotor::setup()
{
    pinMode(_plusPin, OUTPUT);
    pinMode(_minusPin, OUTPUT);
}

void DcMotor::loop()
{
    if (abs(_currentPosition - _plannedPosition) > 0)
    {

        if (millis() - _oldTimeInt >= _rotDelay)
        {
            _oldTimeInt = millis();
            if (_currentPosition - _plannedPosition > 0)
            {
                _currentPosition --;
                digitalWrite(_plusPin, LOW);
                digitalWrite(_minusPin, HIGH);
            }
            else
            {
                _currentPosition ++;
                digitalWrite(_plusPin, HIGH);
                digitalWrite(_minusPin, LOW);
            }
        }
    }
    else
    {
        digitalWrite(_plusPin, HIGH);
        digitalWrite(_minusPin, HIGH);
    }
}

void DcMotor::setPosition(int newPosition)
{
    _plannedPosition = newPosition;
}