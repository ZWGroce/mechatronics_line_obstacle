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
}

void dead_ahead(int spd){
    drive_motor(motorA, forward, .9*spd);
    drive_motor(motorB, forward, spd);
}

void dead_astern(int spd){
    drive_motor(motorA, backward, spd);
    drive_motor(motorB, backward, spd);
}

void turn_left(int spd, int severity){
  if(severity == 0){
    drive_motor(motorA, forward, 0.75*spd);
    drive_motor(motorB, forward, 1.2*spd);
  }else if(severity == 1){
    drive_motor(motorA, forward, .5*spd);
    drive_motor(motorB, forward, spd); 
  }else{
    drive_motor(motorA, 0, 0);
    drive_motor(motorB, forward, 1.25*spd);
    delay(8);
  }
}

void turn_right(int spd, int severity){
  if(severity == 0){
    drive_motor(motorA, forward, spd);
    drive_motor(motorB, forward, 0.7*spd);
  }else if(severity == 1){
    drive_motor(motorA, forward, spd);
    drive_motor(motorB, forward, spd);      
  }else{
    drive_motor(motorA, forward, 1.15*spd);
    drive_motor(motorB, 0, 0);
    delay(8);     
  }
}
