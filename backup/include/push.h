#ifndef PUSH_H
#define PUSH_H
#include "vex.h"
#include "move_and_intake.h"


void Push(int push_voltage){  // 底座输出
  double max_voltage=13000;
  double push_rotation=(RightPush.rotation(vex::rotationUnits::deg)+LeftPush.rotation(vex::rotationUnits::deg))/2;
  if(PushBumper.pressing()&&push_voltage<0){
    push_voltage=0; // 底座限位控制
    LeftPush.resetRotation();
    RightPush.resetRotation();
  }
  else if(push_rotation>params.getValue("vertical_value")&&push_voltage>0)push_voltage=0;
  if(push_voltage>max_voltage)push_voltage=max_voltage;
  if(push_voltage<-max_voltage)push_voltage=-max_voltage;
  if(!push_voltage){
    LeftPush.stop(vex::brakeType::brake);
    RightPush.stop(vex::brakeType::brake);
  }
  else{
    LeftPush.spin(vex::directionType::fwd,push_voltage,vex::voltageUnits::mV);
    RightPush.spin(vex::directionType::fwd,push_voltage,vex::voltageUnits::mV);
  }
}

void PID_Push(){  //用PID自动推底座
  int error;
  double push_voltage,Kp=5,Kc=5000;
  double push_rotation=(RightPush.rotation(vex::rotationUnits::deg)+LeftPush.rotation(vex::rotationUnits::deg))/2;
  error=params.getValue("vertical_value")-push_rotation;
  push_voltage=error*Kp+Kc;
  if(error<=0)Push(0);
  else Push(push_voltage);
}

void Auto_Push(double current_time, double start_time){
  double push_time=4000, release_time=1000+push_time, back_time=1000+release_time; //三个阶段时间
  double push_rotation=(RightPush.rotation(vex::rotationUnits::deg)+LeftPush.rotation(vex::rotationUnits::deg))/2;

  if(current_time-start_time<=push_time){
    if(!pneumatics_close.value()){ // 关闭夹子
      pneumatics_close.set(false);
      pneumatics_open.set(true);
    }
    if((RightPush.rotation(vex::rotationUnits::deg)+LeftPush.rotation(vex::rotationUnits::deg))/2<params.getValue("vertical_value")-400)Intake(6000);
    else {
      LeftIntake.stop(vex::brakeType::coast);
      RightIntake.stop(vex::brakeType::coast);
      LeftUpIntake.stop(vex::brakeType::coast);
      RightUpIntake.stop(vex::brakeType::coast);
    }
    PID_Push();
  }
  else if(current_time-start_time<=release_time){
      LeftIntake.stop(vex::brakeType::coast);
      RightIntake.stop(vex::brakeType::coast);
      LeftUpIntake.stop(vex::brakeType::coast);
      RightUpIntake.stop(vex::brakeType::coast);
    Push(0);
    if(pneumatics_close.value()){ // 打开夹子
      pneumatics_close.set(false);
      pneumatics_open.set(true);
    }
  }
  else if(current_time-start_time<=back_time)Push(-13000);
  else move(-20,-20);
}
#endif
