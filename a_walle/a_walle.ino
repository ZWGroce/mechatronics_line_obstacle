/*Task: Control a simple robot for line following and obstacle avoidance using an IR remote
 * Created by Nate Abramson and Zach Groce
 * Released 01 March 2019
 */
 
#include <IRremote.h>  //Imports IR remote library
#include <LiquidCrystal.h> // Import LCD library
//*****Define Variables*****

//*****LCD Stuff*****
const int rs = 39, en = 37, d4 = 35, d5 = 33, d6 = 31, d7 = 29; //defines LCD-used pins
LiquidCrystal lcd(rs,en,d4,d5,d6,d7); //tells LCD how to name the pins

//*****IR Definitions*****
const int irPin = 22;  //Sets the IR receiver to pin 22
IRrecv irrecv(irPin);  //Creates an instance of the IR receiver on pin 22
decode_results results;  //Creates an instance of the IR decoder
unsigned long irVal;  //Creates a variable to track the most recent IR value

//*****RGB Parameters*****
const int rPin = 5;  //Sets the red LED pin
const int gPin = 6;  //Sets the green LED pin
const int bPin = 8;  //Sets the blue LED pin

//*****Motor Stuff*****
const int dirA = 2;  //Sets the left motor direction pin
const int dirB = 4;  //Sets the right motor direction pin
const int pwmA = 3;  //Sets the left motor PWM speed pin
const int pwmB = 11;  //Sets the right motor PWM speed pin
const int motorA = 0;  //Creates a variable for the left motor
const int motorB = 1;  //Creates a variable for the right motr
#define forward 0  //Defines the word forward as 0
#define backward 1  //Defines the word backward as 1
#define soft 0  //Defines the word soft as 0
#define medium 1  //Defines the word medium as 1
#define hard 2  //Defines the word hard as 2
#define leftTurn 0  //Defines the word left turn as 0
#define rightTurn 1  //Defines the word right turn as 1
int lastDir, lastSeverity;  //Creates variables to track the last direction (left or right) and last turn severity (soft, medium, or hard)

//*****UltraSonic Stuff*****
const int callLeft = 13;  //Sets the left ultrasonic output to pin 13
const int callFront = 12;  //Sets the center ultrasonic output to pin 12
const int callRight = 10;  //Sets the right ultrasonic output to pin 10
const int hearLeft = A3;  //Sets the left ultrasonic input to pin A3
const int hearFront = A2;  //Sets the center ultrasonic input to pin A2
const int hearRight = A0;  //Sets the right ultrasonic input to pin A0
long t; //Creates a variable to define the pulse duration
int x, y, z; //Creates variables to track the distance heard for each sensor (left, center and right)

//*****LDR Stuff*****
const int leftLDR = A13;  //Sets the left LDR intput to pin A13
const int centerLDR = A14;  //Sets the center LDR input to pin A14
const int rightLDR = A15;  //Sets the right LDR input to pin A15
int leftMin = 1023, centerMin = 1023, rightMin = 1023;  //Sets each LDR initial minimum to 1023
int leftMax = 0, centerMax = 0, rightMax = 0;  //Sets each LDR initial maximum to 0

int leftVal, centerVal, rightVal;  //Creates variables to track each LDR reading

//*****Program Initialization*****
void setup() {
  pinMode(dirA, OUTPUT);  //Sets the pin to output
  pinMode(dirB, OUTPUT);  //Sets the pin to output
  pinMode(pwmA, OUTPUT);  //Sets the pin to output
  pinMode(pwmB, OUTPUT);  //Sets the pin to output
  pinMode(leftLDR, INPUT);  //Sets the pin to input
  pinMode(centerLDR, INPUT);  //Sets the pin to input
  pinMode(rightLDR, INPUT);  //Sets the pin to input
  pinMode(rPin, OUTPUT);  //Sets the pin to output
  pinMode(gPin, OUTPUT);  //Sets the pin to output
  pinMode(bPin, OUTPUT);  //Sets the pin to output
  pinMode(callLeft,OUTPUT);  //Sets the pin to output
  pinMode(callFront,OUTPUT);  //Sets the pin to output
  pinMode(callRight,OUTPUT);  //Sets the pin to output
    pinMode(39,OUTPUT); // sets pin to output
    pinMode(37,OUTPUT);  //Sets the pin to output
    pinMode(35,OUTPUT);  //Sets the pin to output
    pinMode(33,OUTPUT);  //Sets the pin to output
    pinMode(31,OUTPUT);  //Sets the pin to output
    pinMode(29,OUTPUT);  //Sets the pin to output
    lcd.begin(16,2); // tells the LCD how many spaces there are
  irrecv.enableIRIn();  //Starts the IR receiver for remote input
}

//*****Main Program*****
void loop() {
  if (irrecv.decode(&results)){  //Triggers if the IR receives gets an input
    irVal = results.value;  //Stores the ir input in the variable irVal
    delay(50);  //Pauses the program for 50 ms to handle bounce in the remote
    irrecv.resume(); // Receive the next IR value
  }

  if(irVal == 0xFFA25D){  //Triggers if the user presses the power button
    all_stop();  //Stops the motors
  }else if(irVal == 0xFF9867){  //Triggers if the user presses Eq
    irVal = 0;  //Sets the irVal to 0 so the calibration doesn't run twice
    calibrate_LDR();  //Runs the calibrate LDRs function
  }else if(irVal == 0xFF30CF){  //Triggers if the user presses 1
    follow_line(30);  //Runs the line following function with a speed of 30
  }else if(irVal == 0xFF18E7){  //Triggers if the user presses 2
    circle_turn(60);  //Runs the function to turn the robot in a circle
  }else if(results.value == 0xFF7A85){  //Triggers if the user presses 3
    avoid_obstacles(45);  //Runs the obstacle avoidance function with a speed of 45
  }
}

//*****Additional Functions*****
void setColor(int red, int green, int blue){  //Creates a function to set the LED color
  analogWrite(rPin, red);  //Outputs the red value (between 0 and 255)
  analogWrite(gPin, green);  //Outputs the green value (between 0 and 255)
  analogWrite(bPin, blue);  //Outputs the blue value (between 0 and 255)  
}
