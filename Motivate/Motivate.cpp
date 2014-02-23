// Parkbot
#include "Motivate.h"

	Motivate::Motivate(int leftMotor, int rightMotor):
	mLeftMotor(leftMotor, MOTOR12_64KHZ), 
	mRightMotor(rightMotor, MOTOR12_64KHZ),
	mStatus("")
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
		return spd;
	}

	void Motivate::stop()
	{
		mLeftMotor.setSpeed(0);
		mRightMotor.setSpeed(0);
		mLeftMotor.run(RELEASE);
		mRightMotor.run(RELEASE);
		mStatus = "Stopped\n";
	}

	String Motivate::status()
	{
		return mStatus;
	}

	void Motivate::go(Direction direction, Speed speed)
	{
		stop();
		
		mStatus = "";
		int lspd = calcSpeed(speed);
		int rspd = calcSpeed(speed);
		int ldir = FORWARD;
		int rdir = FORWARD;
		switch(direction){

		case Forward:
			break;
		case Backward:
			ldir = BACKWARD;
		    rdir = BACKWARD;
			break;
		case ForwardRight:
            rspd = calcHalfSpeed(speed);
            break;
		case BackwardRight:
            rspd = calcHalfSpeed(speed);
			ldir = BACKWARD;
		    rdir = BACKWARD;
		case ForwardLeft:
            lspd = calcHalfSpeed(speed);
			break;
		case BackwardLeft:
			lspd = calcHalfSpeed(speed);
			ldir = BACKWARD;
		    rdir = BACKWARD;;
			break;
		case RotateLeft:
			ldir = BACKWARD;
			rdir = FORWARD;
			break;
		case RotateRight:
			ldir = FORWARD;
			rdir = BACKWARD;
			break;		
		};

		mLeftMotor.setSpeed(lspd);
		mRightMotor.setSpeed(rspd);
		mLeftMotor.run(ldir);
		mRightMotor.run(rdir);
        if(ldir == FORWARD) mStatus = "L Forward ";
        if(ldir == BACKWARD) mStatus = "L Backward ";
        mStatus += String(lspd, DEC);
        if(rdir == FORWARD) mStatus += " R Forward ";
        if(rdir == BACKWARD) mStatus += " R Backward ";
        mStatus += String(rspd, DEC);
        mStatus += "\n";
	
        }