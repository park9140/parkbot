/*
  UFDistance.h
*/
#ifndef UFDistance_h
#define UFDistance_h

#include "Arduino.h"

class UFDistance
{
  public:
    UFDistance(void);
    void init(void);
    void record(void);
    int approachRate(void);
    long getLast(void);

  private:
    long distanceHistory[10][2];
    int historyIndex;
    long get(void);
    float slope(void);
    float intercept(void);
};

#endif
