#include "main.h"

BtClassic bt;

Servo elbowServo;
Servo wristServo;
Servo fingerServo;
Servo vertServo;

Motor bicep(571, 8, 7, 1);

DcMotor shoulder(5, 6, 50);

bool autoMode = false;        //enables or disables auto mode
unsigned long oldTimeInt = 0; //follows time
bool grabState = false;       //finger servo grab toggle

int genDelay = 5000;
int smallDelay = 1000;

byte part = 0;   //delay between big movements
byte inPart = 0; //delay between small movements
int values[3][4] = {
    //arm states values
    {209, 122, 90, 139}, //down take
    {147, 170, 90, 162}, //up
    {238, 118, 90, 139}  //up put
};

void setup()
{
  Serial.begin(9600);
  fingerServo.attach(9); //start servos
  elbowServo.attach(10);
  wristServo.attach(11);
  vertServo.attach(12);

  fingerServo.write(110); //give servos starting position
  elbowServo.write(135);
  wristServo.write(90);
  vertServo.write(90);

  bicep.setup(); //setup other motors
  shoulder.setup();
}

void loop()
{
  bt.loop(); //main loops for different objects
  bicep.loop();
  shoulder.loop();

  checkBt(); //checks for incoming bluetooth data and proceeds it

  if (autoMode) //if user have chose automode then loop it
  {
    doAuto();
  }
}

void checkBt()
{
  if (bt.getNewData())
  {
    if (!autoMode && bt.getType() >= 1 && bt.getType() <= 6) //if there is automode then user can't manual set motor values
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
    else if (bt.getType() == 7) //if datatype is 7 then toggle auto mode
    {
      autoMode = !autoMode; //toggles auto mode
      grabState = false;    //resets grab to default open state
    }
  }
}
