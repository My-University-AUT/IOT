// #include <Wire.h>
// #include <Keypad.h>
// #include <LiquidCrystal.h>

// const byte rows = 4;
// const byte cols = 3;
// char keys[rows][cols] = {
//     {'1', '2', '3'},
//     {'4', '5', '6'},
//     {'7', '8', '9'},
//     {'#', '0', '*'}};
// byte rowPins[rows] = {43, 44, 45, 46}; // connect to the row pinouts of the keypad
// byte colPins[cols] = {47, 48, 49}; // connect to the column pinouts of the keypad
// Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);


// // seven segment
// const byte segRows = 7;
// // left digit
// uint segLeftPins[segRows] = { 22, 23, 24, 25, 26, 27, 28}; // { a b c d e f g . )
// // right digit
// uint segRightPins[segRows] = {29, 30, 31, 32, 33, 34, 35}; // { a b c d e f g . )

// // Truth table for driving the 7segments LED
// uint segCode[11][8] = {
//     //  a  b  c  d  e  f  g  .
//     {1, 1, 1, 1, 1, 1, 0, 1}, // 0
//     {0, 1, 1, 0, 0, 0, 0, 0}, // 1
//     {1, 1, 0, 1, 1, 0, 1, 0}, // 2
//     {1, 1, 1, 1, 0, 0, 1, 0}, // 3
//     {0, 1, 1, 0, 0, 1, 1, 0}, // 4
//     {1, 0, 1, 1, 0, 1, 1, 0}, // 5
//     {1, 0, 1, 1, 1, 1, 1, 0}, // 6
//     {1, 1, 1, 0, 0, 0, 0, 0}, // 7
//     {1, 1, 1, 1, 1, 1, 1, 0}, // 8
//     {1, 1, 1, 1, 0, 1, 1, 0}, // 9
//     {0, 0, 0, 0, 0, 0, 0, 1}  // .
// };

// const int LDRPin = A0;// Initialize PIN A0 LDR PIN

// void readNumber();
// void checkLightness();
// void countDown();
// void updateView();

// void setup() {
//     Serial1.begin(9600);

//     // pinMode(LDRPin, INPUT);// Define LDR pin as input 


//     for (int i = 0; i <= segRows; i++)
//     {
//         pinMode(segLeftPins[i], OUTPUT);// declare Arduino pin as an output
//     }

//     for (int i = 0; i <= segRows; i++)
//     {
//         pinMode(segRightPins[i], OUTPUT);// declare Arduino pin as an output
//     }
// }

// int number = 0;
// bool countingDown = false;
// bool lightIsEnough = false;
// void loop()
// {

//     readNumber();
//     checkLightness();
//     if(countingDown == true && lightIsEnough == true) {
//         countDown();
//         updateView();
//         delay(1000);
//     }
// }

// void readNumber()
// {
//     char key = keypad.getKey();

//     if (countingDown == false && lightIsEnough == true && key != NO_KEY)
//     {
//         if (key >= '0' && key <= '9') // read digits
//         {
//             number = number % 10; // mod acts as a decimal left shift for number
//             number = number * 10 + (key - '0');
//             Serial1.println("number is "+ String(number));
//         }
//         else if(number > 10)
//         { // read non digit number as a countdown starter
//             Serial1.println("Counting down...");
//             countingDown = true;
//         }
//     }
// }

// void countDown()
// {
//     if (number > 0)
//     {
//         number--;
//         Serial1.println("counting down, number is " + String(number));
//         if(number == 0) {
//             countingDown = false;
//             number = 0;
//         }
//     }
// }

// void updateView()
// {
//     const int leftDigit = number / 10;
//     const int rightDigit = number % 10;
//     for (int i = 0; i <= segRows; i++)
//     {
//         const uint pinNumber = segLeftPins[i];
//         digitalWrite(pinNumber, segCode[leftDigit][i]);
//     }
//     for (int i = 0; i <= segRows; i++)
//     {
//         const uint pinNumber = segRightPins[i];
//         digitalWrite(pinNumber, segCode[rightDigit][i]);
//     }
// }


// void checkLightness() {

//     int ldrStatus = analogRead(LDRPin);
//     if (ldrStatus <= 500) {
//         lightIsEnough = true;
//     } else {
//         lightIsEnough = false;
//     }
// }