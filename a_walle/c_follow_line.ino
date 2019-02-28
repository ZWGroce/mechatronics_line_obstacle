//Line Following Functionality

void follow_line(int spd){
  setColor(0, 0, 255);
  
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

  if(leftVal > 5 && leftVal < 13){
    //Serial.println("Go LEFT!");
    turn_left(30, soft);
    last = leftTurn;
  }else if(leftVal > 13){
    turn_left(50, hard);
    last = leftTurn;
    //delay(2);  
  }else if(rightVal > 5 && rightVal < 13){
    //Serial.println("Go RIGHT!");
    turn_right(30, soft);
    last = rightTurn;
  }else if(rightVal > 13){
    turn_right(50, hard);
    last = rightTurn;
    //delay(2);  
  }else if (centerVal > 10){
    //Serial.println("Go STRAIGHT!");
    dead_ahead(30);
  }else{
    if(last == leftTurn){
      turn_left(50, hard);  
    }else if(last == rightTurn){
      turn_right(50, hard);  
    }
  }
  delay(1);
}

void circle_turn(int spd){
  setColor(0, 125, 255);
  turn_left(spd, hard);  
}

void calibrate_LDR(){
  Serial.println("Beginning Calibration");
  
  setColor(255, 0, 0);
    
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

  setColor(0, 255, 0);
  delay(1000);
  setColor(0, 0, 0);
}
