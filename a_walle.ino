//Task:
//*****Define Variables*****
//Motor Stuff
const int dirA = 2;
const int dirB = 4;
const int pwmA = 3;
const int pwmB = 11;
const int motorA = 0;
const int motorB = 1;
#define forward 0
#define backward 1
#define soft 0
#define medium 1
#define hard 2
#define leftTurn 0
#define rightTurn 1
int last;

//LDR Stuff
const int leftLDR = A13;
const int centerLDR = A14;
const int rightLDR = A15;
int leftMin = 1023, centerMin = 1023, rightMin = 1023;
int leftMax = 0, centerMax = 0, rightMax = 0;

int leftVal, centerVal, rightVal;

//*****Program Initialization*****
void setup() {
  pinMode(dirA, OUTPUT);
  pinMode(dirB, OUTPUT);
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(leftLDR, INPUT);
  pinMode(centerLDR, INPUT);
  pinMode(rightLDR, INPUT);
  //Serial.begin(9600);
  calibrate_LDR();
}

//*****Main Program*****
void loop() {
  follow_line(30);
}
