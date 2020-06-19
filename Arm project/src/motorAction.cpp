#include "main.h"

void move(byte movePart)
{
  smooth.oldTimeInt = millis();

  if (smooth.motCount == 1) //starts smooth cycle
  {
    smallDelay = 0;
    smooth.maxStep = maxStep;


    Serial.print("Start:");
    Serial.println(inPart);

    smooth.newPosit = values[movePart][inPart - 1]; //sets new position inside smooth struct
    switch (inPart)                                 //reads last positions of motors
    {
    case 1:
      smooth.oldPosit = bicep.getPosition();
      break;
    case 2:
      smooth.oldPosit = elbowServo.read();
      break;
    case 3:
      smooth.oldPosit = wristServo.read();
      break;
    case 4:
      smooth.oldPosit = vertServo.read();
      break;
    default:
      break;
    }
    smooth.difference = abs(smooth.oldPosit - smooth.newPosit);

    smooth.motPosition = smooth.oldPosit;

    if (smooth.difference <= smooth.maxStep)
      smooth.maxStep = 1;
  }
  else if (smooth.motCount > smooth.difference)
  { //reset values
    smooth.motCount = 1;
    inPart++;

    smallDelay = 250;

    if (inPart == 5)
    {
      countPart();
      inPart = 1;
      smallDelay = 1500;
    }
    Serial.print("reset: ");
    Serial.println(inPart);

    return; //break from function
  }

  Serial.print("a: ");
  Serial.println(smooth.maxStep);
  smMove();

  switch (inPart)
  {
  case 1:
    bicep.setPosition(smooth.motPosition);
    // Serial.print("motPosition: ");Serial.println(smooth.motPosition);
    break;
  case 2:
    elbowServo.write(smooth.motPosition);
    break;
  case 3:
    wristServo.write(smooth.motPosition);
    break;
  case 4:
    vertServo.write(smooth.motPosition);
    break;
  default:
    break;
  }
}

void smMove()
{
  float y = 0;
  int x = 0;

  y = map(smooth.motCount, 0, smooth.difference, 0, PI * 100); //maps i value to radians and multiplies by 100 because map() doesn't work with floats
  y = sin(y * 0.01) * 100;                                     //calculates y sin value, multiplies by 0.01 to convert to radians and then by 100 for next max function

  x = map(y, 0, 100, 1, smooth.maxStep); //final calculation of motor step

  if (smooth.newPosit - smooth.oldPosit > 0) //if new position is bigger than last position then increment motor value
    smooth.motPosition += x;
  else if (smooth.newPosit - smooth.oldPosit < 0) //if new position is smaller than last position then subtract motor value
    smooth.motPosition -= x;

  smooth.motCount += x; //increment i by x value for next step
}

void turn(bool side)
{
  //side == true left
  //side == false right
  if (side)
  {
    shoulder.setPosition(10);
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
