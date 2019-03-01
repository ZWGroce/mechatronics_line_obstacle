void avoid_obstacles (int spd)
{  
  x = distance(callFront,hearFront);   //defines x as distance measured by front sensor
  x = constrain(x,0,60);               //limits the measured distance to 60cm
  y = distance(callRight,hearRight);   //defines y as distance measured by front sensor
  y = constrain(y,0,60);               //limits the measured distance to 60cm
  z = distance(callLeft,hearLeft);     //defines z as distance measured by front sensor
  z = constrain (z,0,60);              //limits the measured distance to 60cm
 
  if (x < 30)                    //if distance from front sensor < 30cm
    {
      all_stop();                   //stop moving
      setColor(255, 0, 0);          //red light
      lcd.print("obstacle at: ");   //display distance from obstacle
      lcd.print(x);
      delay(5000);                  //5 second pause  
      dead_astern(45);              //reverse for 1.2 sec
      delay(1200);
      turn_left(45,medium);         //left turn for 1 sec
      delay(1000);
    }

  if (y < 30)                       //if distance from right sensor < 30cm
    {
      all_stop();                   //stop moving
      setColor(255, 0, 0);          //red light
      lcd.print("obstacle at: ");   //display distance from obstacle
      lcd.print(y);
      delay(5000);                  //5 sec pause
      dead_astern(45);              //reverse 1.2 seconds
      delay(1200);
      turn_left(45,medium);         //turn left 1.2 seconds
      delay(1200);
    }  
    if (z < 30)                   //if distance from left sensor < 30cm
    {
      all_stop();                 //stop moving
      setColor(255, 0, 0);        //red light
      lcd.print("obstacle at: "); //print obstacle distance
      lcd.print(z);
      delay(5000);                //5 second pause
      dead_astern(45);            //reverse for 1.2 sec
      delay(1200);
      turn_right(45,medium);      //turn right for 1.2 sec
      delay(1200);
    }
    else                          //if no obstacle,
    {
      setColor(0, 255, 0);        //green light
      dead_ahead(45);             //drive forward
    }
}

//Functions
int distance (int mouth, int ear) //defines the distance in cm measured by the ultrasonic sensor
{
    digitalWrite(mouth,LOW);  //makes no sound
    delay(5);                 //short delay   
    digitalWrite(mouth,HIGH); //makes sound
    delay(10);                //short delay
    digitalWrite(mouth,LOW);  //make no sound

    t = pulseIn(ear,HIGH);    //receives sound waves
    int d;                    //defines "d"
    d = t*.034/2;             //uses the speed of sound in cm to determine distance
    return d;                 //sends distance measured to "distance"
}
