#ifndef USERCTRLMOVE_H
#define USERCTRLMOVE_H
#include "robot.h"
#include "vex.h"
#include <math.h>

/* goStraightMotor(): control motors with proper velocity in usercontrol stage, original code from move.h in 18-19 rpogram
   Input the Motor's target velocity in pct(-100~100) by controller. 
   Calculates a middle velocity between target-vel and current-vel, so that the robot can move with less shock.
   Need to be used in a loop to smoothly approach the target-vel */
void userctrlMove(double targetLeftMotorVel,double targetRightMotorVel){       //left motors' velocity & right motors' velocity (in pct)

  double max_MotorVel=100, min_MotorVel=5;  //recommanded value: max=100%, min=5%
  if(targetLeftMotorVel>max_MotorVel) targetLeftMotorVel = max_MotorVel;
  if(targetLeftMotorVel<max_MotorVel*-1) targetLeftMotorVel = max_MotorVel * -1;
  if(targetRightMotorVel>max_MotorVel) targetRightMotorVel = max_MotorVel;
  if(targetRightMotorVel<max_MotorVel*-1) targetRightMotorVel = max_MotorVel * -1;
  if(fabs(targetLeftMotorVel)<min_MotorVel) targetLeftMotorVel = 0;
  if(fabs(targetRightMotorVel)<min_MotorVel) targetRightMotorVel = 0;

  //current vel: average of four wheels
  double currentLeftMotorVel = robot.chassis.LeftVelocity();
 double currentRightMotorVel = robot.chassis.RightVelocity();
//double currentRightMotorVel=currentLeftMotorVel;
  double min_currentLeftMotorVel=7, min_currentRightMotorVel=7;   //recommanded value: 7


  double k;     //coefficient for calculating mid-vel
  double delta_leftMotorVel = fabs(targetLeftMotorVel - currentLeftMotorVel);
  double delta_rightMotorVel = fabs(targetRightMotorVel - currentRightMotorVel);

  //smoothly stop the robot if both target-vel and current-vel is low.
  if(!targetLeftMotorVel && !targetRightMotorVel && fabs(currentLeftMotorVel)<min_currentLeftMotorVel && fabs(currentRightMotorVel)<min_currentRightMotorVel){
      robot.chassis.Brake("coast"); 
      return;
  }
  //set coefficient k for different situation(experimented value)
  else if (targetLeftMotorVel*currentLeftMotorVel<0 && targetRightMotorVel*currentRightMotorVel<0)  //both change direction
    {k = (delta_leftMotorVel>100 && delta_rightMotorVel>100) ? 0.22 : 0.4 ;}
  else if (targetLeftMotorVel*currentLeftMotorVel<0 || targetRightMotorVel*currentRightMotorVel<0)  //either change direction
    {k = (delta_leftMotorVel>50 || delta_rightMotorVel>50) ? 0.4 : 0.8 ;}
  else 
    {k = (delta_leftMotorVel>75 && delta_rightMotorVel>75) ? 0.75 : 1 ;}

  //calculate spinnig velocity(in mV) for motors.
  //maximum voltage is 13000mV, so 1% = 130mV
  double leftMotorVel = 130 * (k*targetLeftMotorVel + (1-k)*currentLeftMotorVel);
  double rightMotorVel = 130 * (k*targetRightMotorVel + (1-k)*currentRightMotorVel);

  //make motor spin with caluculated-velocity
  robot.chassis.Move(leftMotorVel, rightMotorVel);
}

#endif