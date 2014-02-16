// Parkbot motivate 
#ifndef _Motivate_h_
#define _Motivate_h_

#include <AFMotor.h>

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
	void go(Direction direction, Speed speed);

private:
	AF_DCMotor mRightMotor;
	AF_DCMotor mLeftMotor;
};

#endif