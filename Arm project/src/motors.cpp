#include "main.h"

void doAuto() //automatic movement function
{
  switch (part) //switches between different arm states
  {
  case 0:
    move(0); // goes to default at the start
    break;
  case 1:
    move(1); //goes to pick up from down state
    break;
  case 2:
    grab();      //grabs
    countPart(); //increments movement count
    break;
  case 3:
    move(0); //pulls up arm to default position
    break;
  case 4:
    turn(true);  //turns clockwise
    countPart(); //counts parts
    break;
  case 5:
    move(2); //goes to put on top
    break;
  case 6:
    grab();      //release grab
    countPart(); //counts parts
    break;
  case 7:
    move(0); //goes to default position
    break;
  case 8:
    turn(false); //turns anticlockwise
    countPart(); //counts moevement
    break;
  default:
    break;
  }
}

void move(byte movePart) //moves to values coordinates depending on movePart variable
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

void countPart() //counts part
{
  part++;
  if (part == 9)
    part = 0;
}

void turn(bool side)
{
  //side == true left
  //side == false right
  if (side)
    shoulder.setPosition(60);
  else
    shoulder.setPosition(0);
}

void grab()
{
  if (grabState)
    fingerServo.write(98); //grab
  else
    fingerServo.write(162); //release
  grabState = !grabState;   //toggles grab state variable
}
