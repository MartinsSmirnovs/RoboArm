#include <Motor.h>

Motor::Motor(int stepsPerRevolution, byte stepPin, byte dirPin, int step)
{
    _stepPin = stepPin;
    _dirPin = dirPin;
    _stepsPerRevolution = stepsPerRevolution;
    _step = step;
    _currentPosition = 0;
    _plannedPosition = 0;
    _lastPosition = 0;
}

void Motor::setup()
{
    pinMode(_stepPin, OUTPUT);
    pinMode(_dirPin, OUTPUT);
}

void Motor::loop()
{
    if (_plannedPosition != _currentPosition && abs(_currentPosition - _plannedPosition) > _step)
    {
        if (_currentPosition < _plannedPosition)
        {
            digitalWrite(_dirPin, HIGH);
            for (int i = 0; i < _step; i++)
            {
                _currentPosition++;
                digitalWrite(_stepPin, HIGH);
                delayMicroseconds(2000);
                digitalWrite(_stepPin, LOW);
                delayMicroseconds(2000);
            }
        }
        else if (_currentPosition > _plannedPosition)
        {
            digitalWrite(_dirPin, LOW);
            for (int i = _step; i > 0; i--)
            {
                _currentPosition--;
                digitalWrite(_stepPin, HIGH);
                delayMicroseconds(2000);
                digitalWrite(_stepPin, LOW);
                delayMicroseconds(2000);
            }
        }
    }
}

void Motor::setPosition(int newPosition)
{
    _lastPosition = map(_plannedPosition, 0, _stepsPerRevolution, 0, 360);
    _plannedPosition = map(newPosition, 0, 360, 0, _stepsPerRevolution);
}

int Motor::getPosition(){
    return _lastPosition;
}