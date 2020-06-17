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

extern Servo elbowServo;
extern Servo wristServo;
extern Servo fingerServo;
extern Servo vertServo;

extern Motor bicep;
extern DcMotor shoulder;

extern bool autoMode;
extern unsigned long oldTimeInt;
extern bool grabState;
extern int smallDelay;
extern int genDelay;
extern byte part;
extern byte inPart;
extern int values[3][4];

#endif