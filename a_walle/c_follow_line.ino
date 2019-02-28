//*****Line Following Functionality*****

void follow_line(int spd){  //Creates a function to perform line following
  setColor(0, 0, 255);  //Turns the LED blue during line following

  //LDR Read - Gets values for LDRs and converts to a range of 0-20 for easier comparioson between all sensors
  leftVal = analogRead(leftLDR);  //Reads the left LDR value
  leftVal = map(leftVal, leftMin + 10, leftMax - 10, 20, 0);  //Maps the left LDR to a range of 0-20
  leftVal = constrain(leftVal, 0, 20);  //Ensures the left LDR falls between 0 and 20
  centerVal = analogRead(centerLDR);  //Reads the center LDR value
  centerVal = map(centerVal, centerMin, centerMax, 20, 0);  //Maps the center LDR to a range of 0-20
  centerVal = constrain(centerVal, 0, 20);  //Ensures the center LDR falls between 0 and 20
  rightVal = analogRead(rightLDR);  //Reads the right LDR value
  rightVal = map(rightVal, rightMin + 10, rightMax - 10, 20, 0);  //Maps the center LDR to a range of 0-20
  rightVal = constrain(rightVal, 0, 20);  //Ensures the right LDR falls between 0 and 20

  //Logic loop for line following
  if(leftVal > 3 && leftVal < 15){  //Triggers if the robot begins to veer to the right
    turn_left(30, soft);  //Turns the robot to the left, softly
    lastTurn = leftTurn;  //Tracks the most recent course correction
    lastSeverity = soft;  //Tracks the most recent turn "hardness" ie severity
  }else if(leftVal > 15){  //Triggers if the robot is far to the right
    turn_left(50, hard);  //Turns the robot to the left, hard
    lastTurn = leftTurn;  //Tracks the most recent course correction
    lastSeverity = hard;  //Tracks the most recent turn severity
  }else if(rightVal > 3 && rightVal < 15){  //Triggers if the robot begins to veer to the left
    turn_right(30, soft);  //Turns the robot to the right, softly
    lastTurn = rightTurn;  //Tracks the most recent course correction
    lastSeverity = soft;  //Tracks the most recent turn severity
  }else if(rightVal > 15){  //Triggers if the robot is far to the left
    turn_right(50, hard);  //Turns the robot to the right, hard
    lastTurn = rightTurn;  //Tracks the most recent course correction
    lastSeverity = hard;  //Tracks the most recent turn severity 
  }else if (centerVal > 15){  //Triggers if the robot is centered over the line
    dead_ahead(30);  //Drives the robot straight forward
  }else{  //Triggers if none of the above conditions are met (likely if the robot went totally off the line)
    if(last == leftTurn){  //Continues turning left if the robot overshot but was turning left last
      turn_left(50, hard);  //Turns the robot to the left, hard
    }else if(last == rightTurn){  //continues turning right if the robot overshot but was turning right last
      turn_right(50, hard);    //Turns the robot to the right, hard
    }
  }
  delay(1);  //Waits one millisecond
}

void circle_turn(int spd){  //Function to spin in a circle (deliverable)
  setColor(255, 0, 255);  //Turns the LED purple
  turn_left(spd, hard);  //Turns the robot to the left, hard
}

void calibrate_LDR(){  //Function to automatically calibrate the LDRs
  setColor(255, 0, 0);  //Sets the LED red while calibrating
    
  int startTime = millis();  //Updates the start time
  while((millis()-startTime) < 7000){  //Runs while the time since starting calibration is less than 7 seconds
    leftVal = analogRead(leftLDR);  //Reads the value of the left LDR
    centerVal = analogRead(centerLDR);  //Reads the value of the center LDR
    rightVal = analogRead(rightLDR);  //Reads the value of the right LDR

    if(leftVal > leftMax){  //Triggers if the left LDR is greater than the maximum value (starts at 0)
      leftMax = leftVal;  //Sets the maximum value equal to the current (larger) LDR reading
    }else if(leftVal < leftMin){  //Triggers if the left LDR is lower than the minimum value (starts at 1023)
      leftMin = leftVal;  //Sets the minimum value equal to the current (lower) LDR reading
    }

    if(centerVal > centerMax){  //Triggers if the center LDR is greater than the maximum value (starts at 0)
      centerMax = centerVal;  //Sets the maximum value equal to the current (larger) LDR reading  
    }else if(centerVal < centerMin){  //Triggers if the center LDR is lower than the minimum value (starts at 1023)
      centerMin = centerVal;  //Sets the minimum value equal to the current (lower) LDR reading  
    }

    if(rightVal > rightMax){  //Triggers if the right LDR is greater than the maximum value (starts at 0)
      rightMax = rightVal;  //Sets the maximum value equal to the current (larger) LDR reading  
    }else if(rightVal < rightMin){  //Triggers if the right LDR is lower than the minimum value (starts at 1023)
      rightMin = rightVal;  //Sets the minimum value equal to the current (lower) LDR reading
    }
    delay(10);  //Halts the program for 10 milliseconds
  }

  setColor(0, 255, 0);  //Sets the LED to green
  delay(1000);  //Leaves the LED green for 1 second
  setColor(0, 0, 0);  //Turns the LED off
}
