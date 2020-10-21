#ifndef PARAMETERS_H
#define PARAMETERS_H
#include <cstring>
#include "vex.h"
class Params{
  private:
    //params of robot:
    ////////////////////////////这块参数基本没用////////////////////////////////////
    double robotWidth;                                  //
    double wheelDiameter          =        3*2      ;   //all length in half_inches
    double wheelDistance          =        60*2     ;   //length between left and right wheels
    double MotorGearRatio         =        18       ;
    double WheelGearRatio         =         1       ;   //
    const int max_MotorGearRatio  =        36       ;
    const int min_MotorSpeed      =        100      ;
    
    //params for judging breaking conditions
    //value depands on sensors' accuracy.
    const double min_dist                 =        3       ;   //没用
    const double min_turningAngle         =        5       ;   //没用
    const double min_straightDriveAngle   =        1       ;   //用于陀螺仪判断是否走偏的最小角度
    const double accel_initMotorVolt      =      3000      ;   //
    const double decel_constMotorVolt     =      2000      ;
     double sleeptimeBetweenMoves    =       50     ;


    //PID parameters
    //TODO:动态计算PID参数
    double accel_proportion4turn           =         0.2      ;
    double decel_proportion4turn           =         0.2     ;
    double accel_proportion4goStraight    =0.1;
    double decel_proportion4goStraight    =0.5;
    double accelKp                    =       60       ;
    double decelKp                    =       20       ;
    double decelKi                    =     0.0002     ;
    double decelKd                    =       1       ;
    double Kp4StraightDrive           =    0.0001   ;
    double turn_overshoot  =0           ;
    double straight_overshoot=0;
    double blocknums      ;

    
    int vertical_value                =      965       ; // 轨道竖直时编码器读数
    int down_value                    =      235       ; // 吸方块最合适角度时的编码器读数

  public:
    double getValue(char param[]){
      if       (!strcmp(param, "robotWidth"              )) return robotWidth;
      else if  (!strcmp(param, "wheelDiameter"           )) return wheelDiameter;
      else if  (!strcmp(param, "wheelDistance"           )) return wheelDistance;
      else if  (!strcmp(param, "MotorGearRatio"          )) return MotorGearRatio;
      else if  (!strcmp(param, "WheelGearRatio"          )) return WheelGearRatio;
      else if  (!strcmp(param, "max_MotorGearRatio"      )) return max_MotorGearRatio;
      else if  (!strcmp(param, "min_MotorSpeed"          )) return min_MotorSpeed;
      else if  (!strcmp(param, "min_dist"                )) return min_dist;
      else if  (!strcmp(param, "min_turningAngle"        )) return min_turningAngle;
      else if  (!strcmp(param, "min_straightDriveAngle"  )) return min_straightDriveAngle;
      else if  (!strcmp(param, "accel_initMotorVolt"     )) return accel_initMotorVolt;
      else if  (!strcmp(param, "decel_constMotorVolt"    )) return decel_constMotorVolt;
      else if  (!strcmp(param, "sleeptimeBetweenMoves"   )) return sleeptimeBetweenMoves;
      else if  (!strcmp(param, "accelKp"                 )) return accelKp;
      else if  (!strcmp(param, "decelKp"                 )) return decelKp;
      else if  (!strcmp(param, "decelKi"                 )) return decelKi;
      else if  (!strcmp(param, "decelKd"                 )) return decelKd;
      else if  (!strcmp(param, "Kp4StraightDrive"        )) return Kp4StraightDrive;
      else if  (!strcmp(param, "vertical_value"          )) return vertical_value;
      else if  (!strcmp(param, "down_value"              )) return down_value;
      else if  (!strcmp(param, "turn_overshoot"          )) return turn_overshoot;
      else if  (!strcmp(param, "straight_overshoot"          )) return straight_overshoot;
      else if  (!strcmp(param, "blocknums"               )) return blocknums;
      else if  (!strcmp(param, "accel_proportion4turn"               )) return accel_proportion4turn;
      else if  (!strcmp(param, "decel_proportion4turn"               )) return decel_proportion4turn;
      else if  (!strcmp(param, "accel_proportion4goStraight"         )) return accel_proportion4goStraight;
      else if  (!strcmp(param, "decel_proportion4goStraight"         )) return decel_proportion4goStraight;
      else {
        Brain.Screen.print("!!WARNING!!no matched param");Brain.Screen.print(param);
        Brain.Screen.newLine();
        return 0;
      }
    }
    void setValue(char param[], double val){
      if(!strcmp(param,"accelKp"))accelKp=val;
      else if(!strcmp(param,"decelKp"))decelKp=val;
      else if(!strcmp(param,"turn_overshoot"))turn_overshoot=val;
      else if(!strcmp(param,"straight_overshoot"))straight_overshoot=val;
      else if(!strcmp(param,"blocknums"))blocknums=(int)val;
      else if(!strcmp(param,"accel_proportion4turn"))accel_proportion4turn=val;
      else if(!strcmp(param,"decel_proportion4turn"))decel_proportion4turn=val;
      else if(!strcmp(param,"accel_proportion4goStraight"))accel_proportion4goStraight=val;
      else if(!strcmp(param,"decel_proportion4goStraight"))decel_proportion4goStraight=val;
      else if(!strcmp(param,"sleeptimeBetweenMoves"))sleeptimeBetweenMoves=val;
      else {
        Brain.Screen.print("!!WARNING!!no matched param");Brain.Screen.print(param);
        Brain.Screen.newLine();
      }

    }
};
Params params;
#endif
