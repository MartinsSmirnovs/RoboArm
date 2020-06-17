#include "main.h"

void doAuto()
{
  switch (part)
  {
  case 0:
    move(0);
    break;
  case 1:
    move(1);
    break;
  case 2:
    grab();
    countPart();
    break;
  case 3:
    move(0);
    break;
  case 4:
    turn(true);
    countPart();
    break;
  case 5:
    move(2);
    break;
  case 6:
    grab();
    countPart();
    break;
  case 7:
    move(0);
    break;
  case 8:
    turn(false);
    countPart();
    break;
  default:
    break;
  }
}

void move(byte movePart)
{
  if (millis() - oldTimeInt >= smallDelay)
  {
    oldTimeInt = millis();
    switch (inPart)
    {
    case 0:
      bicep.setPosition(values[movePart][inPart]);
      smallDelay = 1000;
      break;
    case 1:
      elbowServo.write(values[movePart][inPart]);
      break;
    case 2:
      wristServo.write(values[movePart][inPart]);
      break;
    case 3:
      vertServo.write(values[movePart][inPart]);
      inPart = 0;
      countPart();
      smallDelay = 3000;
      break;
    default:
      break;
    }
    inPart++;
  }
}

void countPart()
{
  part++;
  if (part == 8)
    part = 0;
}

void turn(bool side)
{
  //side == true left
  //side == false right
  if (side)
  {
    shoulder.setPosition(60);
  }
  else
  {
    shoulder.setPosition(0);
  }
}

void grab()
{
  if (grabState) //grab
    fingerServo.write(98);
  else //release
    fingerServo.write(162);
  grabState = !grabState;
}