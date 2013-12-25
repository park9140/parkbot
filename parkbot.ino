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
  dist.init();
  // turn on motor
}

void loop() {
  Serial.println("Test distance");
  stop();
  delayMicroseconds(2);
  dist.record();
  delayMicroseconds(2);
  
  Serial.println(dist.getLast());
  if(dist.getLast() > 36)
  {
    Serial.println("Go forward");
    goForward(255);
  }
  else if(dist.getLast() > 16)
  {
    Serial.println("Go forward left");
    goLeftLight(255);
  }
  else if(dist.getLast() > 6) {
    Serial.println("Go left");
    goLeft(255);
    Serial.println("Going left");
  }
  else
  {
    goRightBack(255);
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

void stop(void) {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
    motor1.setSpeed(0);
    motor2.setSpeed(0);
    motor3.setSpeed(0);
    motor4.setSpeed(0);
}

void goLeftLight(int goRate) {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    motor1.setSpeed(goRate/2);
    motor2.setSpeed(goRate/2);
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

void goRightBack(int goRate) {
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
    motor1.setSpeed(goRate);
    motor2.setSpeed(goRate);
    motor3.setSpeed(goRate/2);
    motor4.setSpeed(goRate/2);
}




