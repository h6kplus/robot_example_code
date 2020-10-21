#ifndef IRSENSOR_H
#define IRSENSOR_H
//IR sensor: 红外测距传感器
class IRsensor
{
private:
  int frontDistance;
  int backDistance;
  int rightDistance;
  int leftDistance;
public:
  int getFrontDistance(){ return frontDistance;}
  int getBackDistance(){ return backDistance;}
  int getRightDistance(){ return rightDistance;}
  int getLeftDistance(){ return leftDistance;}
};

IRsensor myIR;

#endif