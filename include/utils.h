#ifndef UTILS_H
#define UTILS_H
#define PI 3.1415
#include "parameters.h"

double dist(int x2, int y2, int x1, int y1){
  int delta_y = y2 - y1, delta_x = x2 - x1;
  return (int)(sqrt(delta_y*delta_y + delta_x*delta_x));  //half_inches
}

int theta(int x2, int y2, int x1, int y1){
  double delta_y = y2 - y1, delta_x = x2 - x1;
  return ((int)(atan2(delta_y, delta_x)*100) + 6280 ) % 6280;
}
//return the smaller turning angle((-314,314]) between theta2 and theta1.
//when theta1 has default values, return angle between (x,y) and robot's current facing angle.
int turningAngle(int theta1, int theta2){
  int delta_Theta = theta1 - theta2;
  if (delta_Theta > 3140) return (-6280+delta_Theta);
  else if (delta_Theta <= -3140) return (delta_Theta + 6280);
  else return delta_Theta;
}

//convert linear vel(half_inches/s) to motor's rotate speed(mV)
double toRotateSpeed(){
  double Wheel_TurnsPerMinute = (1 / (2*PI*params.getValue("WheelDiameter"))) *60;
  double Motor_TurnsPerMinute = Wheel_TurnsPerMinute * params.getValue("WheelGearRatio");
  double speedInPct = Motor_TurnsPerMinute / (params.getValue("min_MotorSpeed") * (params.getValue("max_MotorGearRatio")/params.getValue("WheelGearRatio"))) *100 ;
  double speedInmVolt = 130*speedInPct;
  return speedInmVolt;
}
double chassis_speed=(0.133*3.25*600*36)/60; //底盘线速度（cm/s）， 600转马达，36:60皮带轮减速，3.25小轮子，0.133为常数
double chassis_ration=0.022*3.25*36/60; // 底盘编码器系数比，编码器转1deg机器前进的距离(cm)
#endif