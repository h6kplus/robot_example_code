#ifndef STATUS_H
#define STATUS_H
#include "vex.h"
#include "robot.h"

int status(){
  double current_left_velocity,current_right_velocity,left_rotation,right_rotation,speed,push_rotation;
  static double choose_timer = Brain.timer(vex::timeUnits::msec);
  static int choose=1;
  while(1) 
  {
    current_left_velocity=robot.chassis.LeftVelocity();
    current_right_velocity=robot.chassis.RightVelocity();
    left_rotation=robot.chassis.LeftRotation();
    right_rotation=robot.chassis.RightRotation();             
    push_rotation=(RightPush.rotation(vex::rotationUnits::deg)+LeftPush.rotation(vex::rotationUnits::deg))/2;
    Brain.Screen.printAt(  10,  40, "leftVelocity %f", current_left_velocity );
    Brain.Screen.printAt(  10,  60, "rightVelocity %f", current_right_velocity );
    Brain.Screen.printAt(  10,  80, "leftrotation %f", left_rotation);
    Brain.Screen.printAt(  10, 100, "rightrotation %f", right_rotation);
    Brain.Screen.printAt(  10, 120, "pushrotation %f", push_rotation);
    Brain.Screen.printAt(  10, 140, "gyroangle %f", robot.getTheta());
    // 输出左右轮平均速度已经总转圈数

    if(pneumatics_close.value())Brain.Screen.printAt(  10, 200, "Clamp Close");
    else Brain.Screen.printAt(  10, 200, "Clamp Open");
  }
}

#endif