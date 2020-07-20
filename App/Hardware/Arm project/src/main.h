#ifndef header
#define header
#include "BtClassic.h"
#include "Motor.h"
#include "Servo.h"
#include "DcMotor.h"
#include "Arduino.h"

void grab();
void doAuto();
void grab();
void checkBt();
void turn(bool side);
void move(byte movePart);
void countPart();
void smMove();

extern Servo elbowServo;
extern Servo wristServo;
extern Servo fingerServo;
extern Servo vertServo;

extern Motor bicep;
extern DcMotor shoulder;

struct Smooth
{
    unsigned long oldTimeInt;
    int oldPosit, newPosit, motPosition, difference;
    int motCount;
    int delayTime;
    int maxStep;
};

extern Smooth smooth;

extern bool autoMode;
extern unsigned long oldTimeInt;
extern bool grabState;
extern int smallDelay;
extern int genDelay;
extern byte part;
extern byte inPart;
extern byte maxStep;
extern int values[3][4];

#endif