#include "main.h"

BtClassic bt;

Servo elbowServo;
Servo wristServo;
Servo fingerServo;
Servo vertServo;

Motor bicep(571, 8, 7, 1);

DcMotor shoulder(5, 6, 50);

bool autoMode = false;
unsigned long oldTimeInt = 0;
bool grabState = false;

int genDelay = 5000;
int smallDelay = 1000;

byte part = 0;
byte inPart = 0;
int values[3][4] = {
    {209, 122, 90, 139}, //down take
    {147, 170, 90, 162}, //up
    {238, 118, 90, 139}  //up put
};

void setup()
{
  Serial.begin(9600);
  fingerServo.attach(9);
  elbowServo.attach(10);
  wristServo.attach(11);
  vertServo.attach(12);

  fingerServo.write(110);
  elbowServo.write(135);
  wristServo.write(90);
  vertServo.write(90);

  bicep.setup();
  shoulder.setup();
}

void loop()
{
  bt.loop();
  bicep.loop();
  shoulder.loop();
  checkBt();

  if (autoMode)
  {
    doAuto();
  }
}


void checkBt()
{
  if (bt.getNewData())
  {
    switch (bt.getType())
    {
    case 1:
      if (!autoMode)
        fingerServo.write(bt.getValue());
      break;
    case 2:
      if (!autoMode)
        elbowServo.write(bt.getValue());
      break;
    case 3:
      if (!autoMode)
        wristServo.write(bt.getValue());
      break;
    case 4:
      if (!autoMode)
        vertServo.write(bt.getValue());
      break;
    case 5:
      if (!autoMode)
        bicep.setPosition(bt.getValue());
      break;
    case 6:
      if (!autoMode)
        shoulder.setPosition(bt.getValue());
      break;
    case 7:
      autoMode = !autoMode;
      grabState = false;
      break;
    default:
      break;
    }
  }
}