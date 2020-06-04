#include "main.h"
#include "BtClassic.h"
#include "Motor.h"
#include "Servo.h"
#include "DcMotor.h"

BtClassic bt;

Servo elbowServo;
Servo wristServo;
Servo fingerServo;
Servo vertServo;

Motor bicep(571, 8, 7, 1);

DcMotor shoulder(5, 6, 50);

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

  if (bt.getNewData())
  {

    switch (bt.getType())
    {
    case 1:
      fingerServo.write(bt.getValue());
      break;
    case 2:
      elbowServo.write(bt.getValue());
      break;
    case 3:
      wristServo.write(bt.getValue());
      break;
    case 4:
      vertServo.write(bt.getValue());
      break;
    case 5:
      bicep.setPosition(bt.getValue());
      break;
    case 6:
        shoulder.setPosition(bt.getValue());
        break;
    default:
      break;
    }
  }
}