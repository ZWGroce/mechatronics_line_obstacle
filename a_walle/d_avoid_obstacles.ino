void avoid_obstacles (int spd)
{
  setColor(255, 0, 255);
  
  x = distance(callFront,hearFront);
  x = constrain(x,0,60);
  y = distance(callRight,hearRight);
  y = constrain(y,0,60);
  z = distance(callLeft,hearLeft);
  z = constrain (z,0,60);
  Serial.print(z);Serial.print("\t");Serial.print(x);Serial.print("\t");Serial.println(y);
  if (x < 20) 
    {
      all_stop();
      delay(500);
      dead_astern(45);
      delay(1200);
      turn_left(45,medium);
      delay(1000);
    }

  if (y < 20) 
    {
      all_stop();
      delay(500);
      dead_astern(45);
      delay(1200);
      turn_left(45,medium);
      delay(1200);
    }  
    if (z < 20) 
    {
      all_stop();
      delay(500);
      dead_astern(45);
      delay(1200);
      turn_right(45,medium);
      delay(1200);
    }
    else
    {dead_ahead(45);}
}

//Functions
int distance (int mouth, int ear)
{
    digitalWrite(mouth,LOW);
    delay(5);
    digitalWrite(mouth,HIGH);
    delay(10);
    digitalWrite(mouth,LOW);

    t = pulseIn(ear,HIGH);
    int d;
    d = t*.034/2;
    return d;
}
