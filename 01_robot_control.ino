//Task:
//*****Define Variables*****
//Motor Stuff
const int dirA = 2;
const int dirB = 4;
const int pwmA = 3;
const int pwmB = 11;
const int motorA = 0;
const int motorB = 1;
const int forward = 0;
const int backward = 1;
const int hard = 1;

//LDR Stuff
const int leftLDR = A13;
const int centerLDR = A14;
const int rightLDR = A15;

int leftVal, centerVal, rightVal;

void turn_left(int spd, int severity = 0);
void turn_right(int spd, int severity = 0);


//*****Program Initialization*****
void setup() {
  pinMode(dirA, OUTPUT);
  pinMode(dirB, OUTPUT);
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(leftLDR, INPUT);
  pinMode(centerLDR, INPUT);
  pinMode(rightLDR, INPUT);
  Serial.begin(9600);
}

//*****Main Program*****
void loop() {
  leftVal = analogRead(leftLDR);
  leftVal = map(leftVal, 120, 175, 15, 0);
  centerVal = analogRead(centerLDR);
  centerVal = map(centerVal, 30, 45, 15, 0);
  rightVal = analogRead(rightLDR);
  rightVal = map(rightVal, 115, 190, 15, 0);

  /*Serial.print(leftVal); Serial.print("\t");
  Serial.print(centerVal); Serial.print("\t");
  Serial.println(rightVal);
  delay(1500);*/

  if(leftVal > 5 && leftVal < 10){
    //Serial.println("Go LEFT!");
    turn_left(30);
  }else if(leftVal > 10){
    turn_left(60, hard);
    delay(2);  
  }else if(rightVal > 5 && rightVal < 10){
    //Serial.println("Go RIGHT!");
    turn_right(30);
  }else if(rightVal > 10){
    turn_right(60, hard);
    delay(2);  
  }else{
    //Serial.println("Go STRAIGHT!");
    dead_ahead(30); 
  }
  delay(3);
}

void drive_motor(int motor, int dir, int spd){
    if(motor ==0){
      digitalWrite(dirA, dir);
      analogWrite(pwmA, spd);  
    }else if(motor == 1){
      digitalWrite(dirB, dir);
      analogWrite(pwmB, spd);  
    }
}

void stop_motor(int motor){
  drive_motor(motor, 0, 0);  
}

void all_stop(){
  drive_motor(motorA, 0, 0);
  drive_motor(motorB, 0, 0);  
}

void dead_ahead(int spd){
    drive_motor(motorA, forward, spd);
    drive_motor(motorB, forward, spd);
}

void turn_left(int spd, int severity = 0){
  if(severity == 0){
    drive_motor(motorA, forward, 0.5*spd);
    drive_motor(motorB, forward, spd);
  }else{
    drive_motor(motorA, backward, 0.5*spd);
    drive_motor(motorB, forward, spd); 
  }
}

void turn_right(int spd, int severity = 0){
  if(severity == 0){
    drive_motor(motorA, forward, spd);
    drive_motor(motorB, forward, 0.5*spd);
  }else{
    drive_motor(motorA, forward, spd);
    drive_motor(motorB, backward, 0.5*spd);      
  }
}
