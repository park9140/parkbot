// Parkbot motivate 
// copyright Parkbot, 2014


/**
* A wrapper class for Adafruit Motor shield library
* Desinged for a two wheel robot with easily configurable
* functions for forward backward speed and turning.
*
* Example Usage:
*
* #include <Motivate.h>
* #include <AFMotor.h>
*
* Motivate moto(1, 2);
*
* void setup(){
*  
* }
*  
* void loop(){
*  moto.go(Forward, Fast);
*  delay(1000);
*  moto.go(RotateLeft, Fast);
*  delay(1000); 
* }
*/

#ifndef _Motivate_h_
#define _Motivate_h_

#include <AFMotor.h>
#include <SoftwareSerial.h>

enum Direction{
	Forward,
	Backward,
	ForwardRight,
	ForwardLeft,
	BackwardRight,
	BackwardLeft,
	RotateLeft,
	RotateRight
};

enum Speed{
	Fast,
	Medium,
	Slow,
	Stop
};

class Motivate
{
public:
	Motivate(int leftMotor, int rightMotor);
	//~Motivate();
	String status();
	void go(Direction direction, Speed speed);
	void stop();

private:
	AF_DCMotor mRightMotor;
	AF_DCMotor mLeftMotor;
    String mStatus;
};

#endif