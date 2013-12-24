#include "UFDistance.h"

const int pingPin = 50;
const int timeIndex = 0;
const int distanceIndex = 1;
const int sampleSize = 10;

inline long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

UFDistance::UFDistance(void) {
}

void UFDistance::init(void) {
  Serial.println("Getting initial distances");
  historyIndex = 0;
  for(int i = 0; i <10; i++)
  {
    distanceHistory[i][timeIndex] = get();
    distanceHistory[i][distanceIndex] = millis();
    delay(1);
  }
}

float UFDistance::slope(void) {
  int sumx = 0, sumy = 0, sumxy, sumx2;
  for(int i = 0; i <10; i++)
  {
    sumx += distanceHistory[i][timeIndex];
    sumy += distanceHistory[i][distanceIndex];
    sumxy += distanceHistory[i][timeIndex] * distanceHistory[i][distanceIndex];
    sumx2 += distanceHistory[i][distanceIndex] * distanceHistory[i][distanceIndex];
  }
  return (float)(((sampleSize*sumxy) - (sumx*sumy))/((sampleSize*sumx2)-(sumx*sumy)));
}

float UFDistance::intercept(void) {
  int sumx = 0, sumy = 0, sumxy, sumx2;
  for(int i = 0; i <10; i++)
  {
    sumx += distanceHistory[i][timeIndex];
    sumy += distanceHistory[i][distanceIndex];
    sumxy += distanceHistory[i][timeIndex] * distanceHistory[i][distanceIndex];
    sumx2 += distanceHistory[i][distanceIndex] * distanceHistory[i][distanceIndex];
  }
  return (float)(((sumx2*sumy) - (sumx*sumxy))/((sampleSize*sumx2)-(sumx*sumy)));
}

long UFDistance::get(void) {
  Serial.println("Getting Distance to object");
  long duration, dist;
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  dist = microsecondsToInches(duration);
  Serial.println("Distance to object");
  Serial.println(dist);
  return dist;
}

void UFDistance::record(void) {
  long distance = get();
  long timeValue = millis();
  if(distance < 2)
  {
    return;
  }
  if(distance > 120 )
  {
    return;
  }
  historyIndex++;
  if(historyIndex > 9)
  {
    historyIndex = 0;
  }
  distanceHistory[historyIndex][timeIndex] = timeValue;
  distanceHistory[historyIndex][distanceIndex] = distance;
}

int UFDistance::approachRate(void){
  return (int)(slope()*255);
}

long UFDistance::getLast(void) {
  return distanceHistory[historyIndex][distanceIndex];
}

