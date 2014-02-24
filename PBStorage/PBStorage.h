// Parkbot motivate 
// copyright Parkbot, 2014


#ifndef _PBStorage_
#define _PBStorage_

#include <SPI.h>
#include <SD.h>

class PBStorage
{
public:
	 PBStorage();
	//~ PBStorage();
	 String status();
	 void ls(uint8_t flags);
 
private:
	void init();

private:
	Sd2Card mCard;
	SdVolume mVolume;
	SdFile mFile;
	String mStatus;

};
#endif