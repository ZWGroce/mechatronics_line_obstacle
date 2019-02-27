//Task: Control a simple robot for line following and obstacle avoidance using an IR remote
 
#include <IRremote.h>

//*****Define Variables*****

//IR Stuff
const int irPin = 6;
IRrecv irrecv(irPin);
decode_results results;
unsigned long irVal;

//RGB Parameters
const int rPin = 5;
const int gPin = 4;
const int bPin = 8;

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
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  irrecv.enableIRIn();
  Serial.begin(9600);
}

//*****Main Program*****
void loop() {
  if (irrecv.decode(&results)) {
    irVal = results.value;
    Serial.println(irVal, HEX);

    delay(50);
    irrecv.resume(); // Receive the next value
  }

  if(irVal == 0xFFA25D){  //All stop
    all_stop();
  }else if(irVal == 0xFF9867){  //Calibrate LDRs
    irVal = 0;
    //Serial.println(irVal);
    calibrate_LDR();
  }else if(irVal == 0xFF30CF){  //Follow line
    follow_line(30);    
  }else if(irVal == 0xFF18E7){  //Turn in circle
    circle_turn(60);    
  }/*else if(results.value == 0xFF7A85){  //Avoid obstacles
      
  }*/else if(irVal == 0xFF02FD){
    dead_ahead(60);  
  }
}

void setColor(int red, int green, int blue){
  analogWrite(rPin, red);
  analogWrite(gPin, green);
  analogWrite(bPin, blue);  
}
