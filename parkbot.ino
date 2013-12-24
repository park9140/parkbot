// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!
#include <AFMotor.h>
#include <UFDistance.h>

AF_DCMotor motor1(1);

AF_DCMotor motor2(2);

AF_DCMotor motor3(3);

AF_DCMotor motor4(4);

UFDistance dist;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");
  dist.init();
  // turn on motor
}

void loop() {
  Serial.println("Test distance");
  dist.record();
  
  Serial.println(dist.getLast());
  if(dist.getLast() > 10)
  {
    Serial.println("Go forward");
    goForward(255);
  }
  else {
    Serial.println("Go left");
    goLeft(255);
    Serial.println("Going left");
  }
  delay(100);
}


void goForward(int goRate) {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    motor1.setSpeed(goRate);
    motor2.setSpeed(goRate);
    motor3.setSpeed(goRate);
    motor4.setSpeed(goRate);
}

void goLeft(int goRate) {
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    motor1.setSpeed(goRate);
    motor2.setSpeed(goRate);
    motor3.setSpeed(goRate);
    motor4.setSpeed(goRate);
}
void goRight(int goRate) {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
    motor1.setSpeed(goRate);
    motor2.setSpeed(goRate);
    motor3.setSpeed(goRate);
    motor4.setSpeed(goRate);
}




