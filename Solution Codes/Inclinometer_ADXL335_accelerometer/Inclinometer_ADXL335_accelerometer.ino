
#include <math.h>   //Auduino code library for math operations 

int greenLED = 3;     // assign digital pin to an LED
int yellowLED = 4;    // assign digital pin to an LED
int redLED = 5;       // assign digital pin to an LED

float valX, valY, valZ; //raw analog values for x, y, and z axis readings.
float accX, accY, accZ; //analog readings converted to acceleration, in g's.
float angleX, angleY, angleZ; //angle of inclination with x,y, and z axis.
float absAngleX, absAngleY, absAngleZ; //positive incline angles


void setup()
{//****start setup function****
  //Serial.begin(9600);  //set the serial port to 9600 baud if monitor is used.
  
  //constrain analog x, y, z readings to actual measured ranges
  constrain(valX,260,392);
  constrain(valY,259,391);
  constrain(valZ,284,418);
  
  //declare LED pins as output.
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  
  //start with green LED on, yellow LED and red LED off.
  digitalWrite(greenLED, HIGH);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);
  
}//****endof setup function****

void loop()
{//****start infinite loop****
  //read the accelerometer x, y, and z axis values
  valX = analogRead(0);       // read analog input pin A0
  valY = analogRead(1);       // read analog input pin A1
  valZ = analogRead(2);       // read analog input pin A2
  delay(10);  // short delay to allow readings to stabilize
  
  //map the analog sensor readings to a g value between -1 g to + 1 g
  //to match the values in AN-1057, the z readings were reversed.
  accX = mapf(valX,260.0,392.0,+1.0,-1.0); //user defined mapf function
  accY = mapf(valY,259.0,391.0,+1.0,-1.0); //user defined mapf function
  accZ = mapf(valZ,284.0,418.0,-1.0,+1.0); //user defined mapf function

  //calculate the angle of inclination with each axis.
  angleX = atan2(accX,(sqrt(pow(accY,2)+pow(accZ,2))))*(180/PI);
  angleY = atan2(accY,(sqrt(pow(accX,2)+pow(accZ,2))))*(180/PI);
  angleZ = atan2((sqrt(pow(accX,2)+pow(accY,2))),accZ)*(180/PI); 

  //use fabs() "f"loating point absolute value vs abs()
  absAngleX = fabs(angleX);
  absAngleY = fabs(angleY);
  absAngleZ = fabs(angleZ);
 
  //illuminate the green, yellow and red LEDs as aprropriate.
  if (absAngleX < 15 && absAngleY < 15 && absAngleZ < 15)
    {
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
    delay(100);
    }
  else if (absAngleX < 30 && absAngleY < 30 && absAngleZ < 30)
    {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);
    delay(100);
    }
  else
    {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);
    delay(100);
    }
  

 /********************************************************************/
//  Print data used for testing and debugging - comment out as needed.
//  Serial.print("analog readings for x, y, z: ");
//  Serial.print(valX, DEC);    // print the acceleration in the X axis
//  Serial.print(" ");          // prints a space between the numbers
//  Serial.print(valY, DEC);    // print the acceleration in the Y axis
//  Serial.print(" ");          // prints a space between the numbers
//  Serial.println(valZ, DEC);  // print the acceleration in the Z axis
//  
//  Serial.print("accX ");
//  Serial.println(accX,DEC);
//  Serial.print("accY ");
//  Serial.println(accY,DEC);
//  Serial.print("accZ ");
//  Serial.println(accZ,DEC);
//  
//  Serial.print("angleX ");
//  Serial.println(angleX,DEC);
//  Serial.print("angleY ");
//  Serial.println(angleY,DEC);
//  Serial.print("angleZ ");
//  Serial.println(angleZ,DEC);
//  delay(1000);  // waitfor next reading
/********************************************************************/

}//****endof infinite loop****

/********************************************************************
//function mapf to mimic map function but it uses floating point numbers
 *******************************************************************/
float mapf(float x_, float in_min, float in_max, float out_min, float out_max)
 {//****start mapf function****
   return (x_ - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
 }//****endof mapf function****