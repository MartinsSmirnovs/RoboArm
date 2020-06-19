#include "main.h"

void doAuto()
{
  if (millis() - oldTimeInt >= smallDelay)
  {
    oldTimeInt = millis();

    switch (part)
    {
    case 0:
      if (millis() - smooth.oldTimeInt >= smooth.delayTime)
        move(0);
      break;
    case 1:
      if (millis() - smooth.oldTimeInt >= smooth.delayTime)
        move(1);
      break;
    case 2:
      grab();
      countPart();
      break;
    case 3:
      if (millis() - smooth.oldTimeInt >= smooth.delayTime)
        move(0);
      break;
    case 4:
      turn(true);
      countPart();
      break;
    case 5:
      if (millis() - smooth.oldTimeInt >= smooth.delayTime)
        move(2);
      break;
    case 6:
      grab();
      countPart();
      break;
    case 7:
      if (millis() - smooth.oldTimeInt >= smooth.delayTime)
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
}

void countPart()
{
  part++;
  if (part == 9)
    part = 0;
}
