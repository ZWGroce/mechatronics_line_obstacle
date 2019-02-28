//*****Motor Functionality*****

void drive_motor(int motor, int dir, int spd){  //Function to actuate a DC motor based on which motor (left or right), a desired direction (forward or backward) and a speed (0 to 255)
    if(motor == 0){  //Triggers for the left motor
      digitalWrite(dirA, dir);  //Sets the direction of the DC motor (forward or backward)
      analogWrite(pwmA, spd);  //Sets the speed of the motor (0 to 255)
    }else if(motor == 1){  //Triggers for the right motor
      digitalWrite(dirB, dir);  //Sets the direction of the DC motor (forward or backward)
      analogWrite(pwmB, spd);  //Sets the speed of the motor (0 to 255)  
    }
}

void stop_motor(int motor){  //Function to stop a motor
  drive_motor(motor, 0, 0);  //Uses the above function to stop the motor by sending a speed of 0
}

void all_stop(){  //Function to stop both motors
  drive_motor(motorA, 0, 0);  //Uses the above function to stop the left motor
  drive_motor(motorB, 0, 0);  //Stops the right motor
  setColor(0, 0, 0);  //Turns the LED off
}

void dead_ahead(int spd){  //Function to drive straight forward
    drive_motor(motorA, forward, .9*spd);  //Drives the left motor forward (spd coefficient due to difference in motor speeds)
    drive_motor(motorB, forward, 1.05*spd);  //Drives the right motor foward
}

void dead_astern(int spd){  //Function to drive staright backward
    drive_motor(motorA, backward, spd);  //Drives the left motor backward
    drive_motor(motorB, backward, spd);  //Drives the right motor backward
}

void turn_left(int spd, int severity = 0){  //Function to turn to the left
  if(severity == 0){  //Triggers if severity is "soft" (soft defined in a_walle and is equal to 0)
    drive_motor(motorA, forward, 0.7*spd);  //Drives the left motor forward at 70% spd
    drive_motor(motorB, forward, spd);  //Drives the right motor forward at 100% spd
  }else if(severity == 1){  //Triggers if severity is "medium"
    drive_motor(motorA, forward, .45*spd);  //Drives the left motor forward at 45% spd
    drive_motor(motorB, forward, spd);  //Drives the right motor forward at 100% spd
  }else{  //Triggers if severity is "hard"
    drive_motor(motorA, backward, 0.6*spd);  //Drives the left motor backward at 60% spd
    drive_motor(motorB, forward, spd);  //Drives the right motor forward at 100% spd
  }
}

void turn_right(int spd, int severity = 0){  //Function to turn to the right
  if(severity == 0){  //Triggers if severity is "soft"
    drive_motor(motorA, forward, spd);  //Drives the left motor forward at 100% spd
    drive_motor(motorB, forward, 0.7*spd);  //Drives the right motor forward at 70% spd
  }else if(severity == 1){  //Triggers if severity is "medium"
    drive_motor(motorA, forward, spd);  //Drives the left motor forward at 100% spd
    drive_motor(motorB, forward, 0.53*spd);  //Drives the right motor forward at 53% spd      
  }else{  //Triggers if severity is "hard"
    drive_motor(motorA, forward, spd);  //Drives the left motor forward at 100% spd
    drive_motor(motorB, backward, 0.6*spd);  //Drives the right motor backward at 60% spd   
  }
}
