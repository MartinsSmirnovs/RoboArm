// unsigned long oldTimeInt = 0; //for time calculations

// float y = 0;
// int x = 0;

// int oldPosit = 120;//current motor position
// int newPosit = 123; //new motor position

// int delayTime = 40;//motor speed

// int maxStep = 6; //biggest step that can be done by motor


// int motPosition = oldPosit; //starts motor position with its default position which is oldPosit
// int difference = 0; //difference between old position and new position

// void setup() {
//   Serial.begin(115200);
// }

// void loop() {
//   motPosition = oldPosit; //resets motor position
//   difference = abs(oldPosit - newPosit); //calculates differenace between old position and new position

//   if (difference <= maxStep) { //if difference is smaller or equal than max step
//     maxStep = motPosition / 2;
//     if (maxStep == 0)
//       maxStep = 1;
//   }

//   for (int i = 1; i <= difference;) { //loops through motor values
//     if (millis() - oldTimeInt > delayTime) {
//       oldTimeInt = millis(); //resets timer

//       y = map(i, 0, difference, 0, PI * 100); //maps i value to radians and multiplies by 100 because map() doesn't work with floats
//       y = sin(y * 0.01) * 100; //calculates y sin value, multiplies by 0.01 to convert to radians and then by 100 for next max function

//       x = map(y, 0, 100, 1, maxStep); //final calculation of motor step

//       if (newPosit - oldPosit > 0) //if new position is bigger than last position then increment motor value
//         motPosition += x;
//       else if (newPosit - oldPosit < 0) //if new position is smaller than last position then subtract motor value
//         motPosition -= x;

//       i += x; //increment i by x value for next step
//       Serial.println(motPosition); //test
//     }
//   }

// }
