//Motor Functionality

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
  setColor(0, 0, 0);
}

void dead_ahead(int spd){
    drive_motor(motorA, forward, .9*spd);
    drive_motor(motorB, forward, 1.05*spd);
}

void dead_astern(int spd){
    drive_motor(motorA, backward, spd);
    drive_motor(motorB, backward, spd);
}

void turn_left(int spd, int severity = 0){
  if(severity == 0){
    drive_motor(motorA, forward, 0.7*spd);
    drive_motor(motorB, forward, spd);
  }else{
    drive_motor(motorA, backward, 0.6*spd);
    drive_motor(motorB, forward, spd); 
  }
}

void turn_right(int spd, int severity = 0){
  if(severity == 0){
    drive_motor(motorA, forward, spd);
    drive_motor(motorB, forward, 0.7*spd);
  }else{
    drive_motor(motorA, forward, spd);
    drive_motor(motorB, backward, 0.6*spd);      
  }
}
