// Parkbot motivate 
// copyright Parkbot, 2014

#include <PBStorage.h>
#include <Arduino.h>
#include <SoftwareSerial.h>

const int chipSelect = 4;

PBStorage::PBStorage()
{
	init();
}

void PBStorage::init()
{
	pinMode(10, OUTPUT);
	SoftwareSerial btSerial(2, 4);
	btSerial.begin(38400);	
	mStatus = "SD Card Init Status\n";

	if( !mCard.init(SPI_HALF_SPEED, chipSelect)){
		mStatus += "Initializion Failed";
		return;
	}else{
		mStatus += "Initializion OK";
	}

	mStatus += "\nCard Type: ";
    switch (mCard.type()) {
    case SD_CARD_TYPE_SD1:
        mStatus += "SD1";
        break;
    case SD_CARD_TYPE_SD2:
        mStatus += "SD2";
        break;
    case SD_CARD_TYPE_SDHC:
        mStatus += "SDHC";
        break;
    default:
        mStatus += "Unknown";
    }
  
    mStatus += "\n";

  	if (!mVolume.init(mCard)) {
    	mStatus += "Could not find FAT16/FAT32 partition.\n";
    	mStatus += "Make sure you've formatted the card";
    	return;
  	}

  	uint64_t volumesize64;
  	uint32_t volumesize32;
    mStatus += "Volume type is FAT";
    mStatus += String(mVolume.fatType(), DEC) + "\n";
  
    volumesize64 = mVolume.blocksPerCluster();    // clusters are collections of blocks
    volumesize64 *= mVolume.clusterCount();       // we'll have a lot of clusters
    volumesize64 *= 512;                            // SD card blocks are always 512 bytes
  
    mStatus += "Volume size (Kbytes): ";
    volumesize32 = volumesize64/1024;
    mStatus += volumesize32;
    mStatus += "\n";

  
    mStatus += "Volume size (Mbytes): ";
    volumesize32 /= 1024;
    mStatus += volumesize32;

	btSerial.println(mStatus);
    
}

void PBStorage::ls(uint8_t flags)
{
	SoftwareSerial btSerial(2, 4);
	btSerial.begin(38400);	
	if (!mFile.openRoot(&mVolume)) btSerial.println("openRoot failed");
	//mFile.ls(flags);
 	dir_t p;
 
	mFile.rewind();
	while (mFile.readDir(p) > 0) {
	    // done if past last used entry
	    if (p.name[0] == DIR_NAME_FREE) break;
	 
	    // skip deleted entry and entries for . and  ..
	    if (p.name[0] == DIR_NAME_DELETED || p.name[0] == '.') continue;
	 
	    // only list subdirectories and files
	    if (!DIR_IS_FILE_OR_SUBDIR(&p)) continue;
	 
		 
		    // print file name with possible blank fill
		    //root.printDirName(*p, flags & (LS_DATE | LS_SIZE) ? 14 : 0);
		 
		 
		for (uint8_t i = 0; i < 11; i++) {
		    if (p.name[i] == ' ') continue;
		    if (i == 8) {
		    	btSerial.print('.');
		    }
		    btSerial.print( char(p.name[i]) );
	    }
	    if (DIR_IS_SUBDIR(&p)) {
	      	btSerial.print('/');
	    }
	 
	    // print modify date/time if requested
	    if (flags & LS_DATE) {
		    mFile.printFatDate(p.lastWriteDate);
		    btSerial.print(' ');
		    mFile.printFatTime(p.lastWriteTime);
	    }
	    // print size if requested
	    if (!DIR_IS_SUBDIR(&p) && (flags & LS_SIZE)) {
		    btSerial.print(' ');
		    btSerial.print(p.fileSize);
	    }
	    btSerial.println("\n");
	}
}

String PBStorage::status()
{
	return mStatus;
}