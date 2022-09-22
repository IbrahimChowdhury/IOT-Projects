#include <AFMotor.h>
#include <Servo.h>
Servo servo;

AF_DCMotor LF(1);
AF_DCMotor LB(2);

#define trigPin  A0
#define echoPin  A1
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(10);
  pinMode(trigPin, OUTPUT);          // Declare "trigPin" as "Output Pin".
  pinMode(echoPin, INPUT);           // Declare "echoPin" as "Input Pin".

}

void loop() {
  char val;
  // put your main code here, to run repeatedly:
  if (Serial.available() == 1)  //if communication is going on
  {
     val = Serial.read();   //Read the data recieved
    Serial.println("Recieved data is " + (String) val);
    if (val == 'F')
    {
      //forward

      LF.setSpeed(200);
      LB.setSpeed(200);
      LF.run(FORWARD);
      LB.run(FORWARD);
      Serial.println("Going forward!");
    }
    if (val == 'B')
    {
      //backward
      LF.setSpeed(200);
      LB.setSpeed(200);
      LF.run(BACKWARD);
      LB.run(BACKWARD);

      Serial.println("Going backward!");
    }
    if (val == 'L')
    {
      //left
      LF.setSpeed(150);
      LB.setSpeed(150);
      LF.run(FORWARD);
      LB.run(BACKWARD);
      Serial.println("Going left!");
    }
    if (val == 'R')
    {
      //right

      LF.setSpeed(150);
      LB.setSpeed(150);
      LF.run(BACKWARD);
      LB.run(FORWARD);
      Serial.println("Going right!");
    }

    if (val == 'S')
    {
      //all off
      LF.run(RELEASE);
      LB.run(RELEASE);
    }

    
  }

if (val == 'Y')
    {
      float distance = 0.00;
      float RightDistance = 0.00;
      float LeftDistance = 0.00;
      distance = search();

      if (distance <= 30) // If obstracle found in 40 CM.
      {
        RobotStop(); //Robot Stop
        delay(100);
        servo.write(5);
        delay(300);
        RightDistance = search();
        delay(100);
        servo.write(180);
        delay(300);
        LeftDistance = search();
        delay(100);
        servo.write(90);
        delay(300);
        if (LeftDistance > RightDistance)
        {
          RobotBackward();
          delay(100);
          RobotStop();
          delay(100);
          RobotLeft();
          delay(500);
          RobotStop();
          delay(100);
        }
        else
        {
          RobotBackward();
          delay(100);
          RobotStop();
          delay(100);
          RobotRight();
          delay(500);
          RobotStop();
          delay(100);
        }
      }
      else
      {
        RobotForward();
      }
    }

      if(val=='y')
    {
        LF.run(RELEASE);
        LB.run(RELEASE);
        servo.write(90);
        digitalWrite(trigPin, LOW);
    }
  
}

float search(void)
{
  float duration = 0.00;             // Float type variable declaration
  float CM = 0.00;
  digitalWrite(trigPin, LOW);        // Trig_pin output as OV (Logic Low-Level)
  delayMicroseconds(2);              // Delay for 2 us
  //Send 10us High Pulse to Ultra-Sonic Sonar Sensor "trigPin"
  digitalWrite(trigPin, HIGH);       // Trig_pin output as 5V (Logic High-Level)
  delayMicroseconds(10);             // Delay for 10 us
  digitalWrite(trigPin, LOW);        // Trig_pin output as OV (Logic Low-Level)
  duration = pulseIn(echoPin, HIGH); // Start counting time, upto again "echoPin" back to Logical "High-Level" and puting the "time" into a variable called "duration"
  CM = (duration / 58.82); //Convert distance into CM.
  Serial.println(CM);
  return CM;
}

void RobotForward()
{
  LF.setSpeed(200);
  LB.setSpeed(200);
  LF.run(FORWARD);
  LB.run(FORWARD);

}
void RobotBackward()
{
  LF.setSpeed(200);
  LB.setSpeed(200);
  LF.run(BACKWARD);
  LB.run(BACKWARD);

}
void RobotLeft()
{
  LF.setSpeed(150);
  LB.setSpeed(150);
  LF.run(FORWARD);
  LB.run(BACKWARD);

}
void RobotRight()
{
  LF.setSpeed(150);
  LB.setSpeed(150);
  LF.run(BACKWARD);
  LB.run(FORWARD);

}
void RobotStop()
{
  LF.run(RELEASE);
  LB.run(RELEASE);

}
