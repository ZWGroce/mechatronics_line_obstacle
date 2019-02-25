//Line Following Functionality

void follow_line(int spd){
  leftVal = analogRead(leftLDR);
  leftVal = map(leftVal, leftMin + 10, leftMax - 10, 20, 0);
  leftVal = constrain(leftVal, 0, 20);
  centerVal = analogRead(centerLDR);
  centerVal = map(centerVal, centerMin, centerMax, 20, 0);
  centerVal = constrain(centerVal, 0, 20);
  rightVal = analogRead(rightLDR);
  rightVal = map(rightVal, rightMin + 10, rightMax - 10, 20, 0);
  rightVal = constrain(rightVal, 0, 20);

  Serial.print(leftVal); Serial.print("\t");
  Serial.print(centerVal); Serial.print("\t");
  Serial.println(rightVal);

  if(leftVal > 5 && leftVal <= 10){
    Serial.println("LEFT, SOFT");
    turn_left(spd, soft);
    last = leftTurn;
  }else if(leftVal > 10 && leftVal <= 15){
    Serial.println("LEFT, MEDIUM");
    turn_left(spd, medium);
    last = leftTurn; 
  }else if(leftVal > 15){
    Serial.println("LEFT, HARD");
    turn_left(spd, hard);
    last = leftTurn; 
  }else if(rightVal > 5 && rightVal <= 10){
    Serial.println("RIGHT, SOFT");
    turn_right(spd, soft);
    last = rightTurn;
  }else if(rightVal > 10 && rightVal <= 15){
    Serial.println("RIGHT, MEDIUM");
    turn_right(spd, medium);
    last = rightTurn;
  }else if(rightVal > 15){
    Serial.println("RIGHT, HARD");
    turn_right(spd, hard);
    last = rightTurn;
  }else if(centerVal > 10){
    Serial.println("Go STRAIGHT!");
    dead_ahead(spd);
  }else if(leftVal > 10 && rightVal > 10){
    if(last == leftTurn){
      turn_left(spd, hard);  
    }else if(last == rightTurn){
      turn_right(spd, hard);  
    }
  }else{
    if(last == leftTurn){
      turn_left(spd, hard);  
    }else if(last == rightTurn){
      turn_right(spd, hard);  
    }
  }
  delay(4);
}

void circle_turn(int spd){
  turn_left(spd, hard);  
}

void calibrate_LDR(){
  Serial.println("Beginning Calibration");
  int startTime = millis();
  while((millis()-startTime) < 7000){
    leftVal = analogRead(leftLDR);
    centerVal = analogRead(centerLDR);   
    rightVal = analogRead(rightLDR);

    if(leftVal > leftMax){
      leftMax = leftVal;
    }else if(leftVal < leftMin){
      leftMin = leftVal;  
    }

    if(centerVal > centerMax){
      centerMax = centerVal;  
    }else if(centerVal < centerMin){
      centerMin = centerVal;  
    }

    if(rightVal > rightMax){
      rightMax = rightVal;  
    }else if(rightVal < rightMin){
      rightMin = rightVal;  
    }
    delay(10);
  }

  Serial.print(leftMin); Serial.print(" "); Serial.print(leftMax); Serial.print("\t");
  Serial.print(centerMin); Serial.print(" "); Serial.print(centerMax); Serial.print("\t");
  Serial.print(rightMin); Serial.print(" "); Serial.print(rightMax); Serial.println();
}
