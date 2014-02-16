// Parkbot
#include "Motivate.h"

	Motivate::Motivate(int leftMotor, int rightMotor):
	mLeftMotor(leftMotor, MOTOR12_64KHZ), 
	mRightMotor(rightMotor, MOTOR12_64KHZ)
	{

	}
	
	int calcSpeed(Speed speed)
	{
		int sp = 0;
		switch(speed){
		case Fast:
			sp = 255;
			break;
		case Medium:
			sp = 127;
			break;
		case Slow:
			sp = 63;
			break;
		case Stop:
			sp = 0;
		}
		return sp;
	}

	int calcHalfSpeed(Speed speed)
	{
		int spd = ((calcSpeed(speed) + 1) / 2 ) - 1;
		//Serial.print(spd);
		return spd;
	}

	void Motivate::go(Direction direction, Speed speed)
	{
		//Serial.print(direction);
		switch(direction){

		case Forward:
			mLeftMotor.setSpeed( calcSpeed(speed) );
			mRightMotor.setSpeed( calcSpeed(speed) );
			mLeftMotor.run(FORWARD);
			mRightMotor.run(FORWARD);
			//Serial.print("Forward\n");
			break;
		case Backward:
			mLeftMotor.setSpeed( calcSpeed(speed) );
			mRightMotor.setSpeed( calcSpeed(speed) );
			mLeftMotor.run(BACKWARD);
			mRightMotor.run(BACKWARD);
			//Serial.print("Backward\n");
			break;
		case ForwardRight:
			mLeftMotor.setSpeed( calcSpeed(speed) );
			mRightMotor.setSpeed( calcHalfSpeed(speed)  );
			mLeftMotor.run(FORWARD);
			mRightMotor.run(FORWARD);
			//Serial.print("ForwardRight\n");
			break;
		case ForwardLeft:
			mLeftMotor.setSpeed( calcHalfSpeed(speed) );
			mRightMotor.setSpeed( calcSpeed(speed)  );
			mLeftMotor.run(FORWARD);
			mRightMotor.run(FORWARD);
			//Serial.print("ForwardLeft\n");
			break;
		case BackwardRight:
			mLeftMotor.setSpeed( calcSpeed(speed) );
			mRightMotor.setSpeed( calcHalfSpeed(speed)  );
			mLeftMotor.run(BACKWARD);
			mRightMotor.run(BACKWARD);
			//Serial.print("BackwardRight\n");
			break;
		case BackwardLeft:
			mLeftMotor.setSpeed( calcHalfSpeed(speed) );
			mRightMotor.setSpeed( calcSpeed(speed)  );
			mLeftMotor.run(BACKWARD);
			mRightMotor.run(BACKWARD);
			//Serial.print("BackwardLeft\n");
			break;
		case RotateLeft:
			mLeftMotor.setSpeed( calcSpeed(speed) );
			mRightMotor.setSpeed( calcSpeed(speed)  );
			mLeftMotor.run(BACKWARD);
			mRightMotor.run(FORWARD);
			//Serial.print("RotateLeft\n");
			break;
		case RotateRight:
			mLeftMotor.setSpeed( calcSpeed(speed) );
			mRightMotor.setSpeed( calcSpeed(speed)  );
			mLeftMotor.run(FORWARD);
			mRightMotor.run(BACKWARD);
			//Serial.print("RotateRight\n");
			break;		
		}
	}