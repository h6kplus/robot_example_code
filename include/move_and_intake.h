#ifndef MOVE_AND_INTAKE_H
#define MOVE_AND_INTAKE_H
#include "vex.h"
#include "robot.h"

void VoltageMove(double left_voltage,double right_voltage){ // 底盘电压输出
  double max_voltage=13000;
  if(left_voltage>max_voltage)left_voltage=max_voltage;
  if(left_voltage<-max_voltage)left_voltage=-max_voltage;
  if(right_voltage>max_voltage)right_voltage=max_voltage;
  if(right_voltage<-max_voltage)right_voltage=-max_voltage;
  // 设定最大输出电压
  robot.chassis.Move(left_voltage, right_voltage);
  // 底盘马达输出
}

void move(double left_velocity,double right_velocity){  // 底盘速度初步输出 
  if(left_velocity>100)left_velocity=100;
  if(left_velocity<-100)left_velocity=-100;
  if(fabs(left_velocity)<5)left_velocity=0;
  if(right_velocity>100)right_velocity=100;
  if(right_velocity<-100)right_velocity=-100;
  if(fabs(right_velocity)<5)right_velocity=0;
  // 设定最大输出转速

  double max_velocity=100,left_voltage,right_voltage,current_left_velocity,current_right_veolocity;;
  double k=1; // 系数K越大，软启动效果越差

  current_left_velocity=robot.chassis.LeftVelocity();
  current_right_veolocity=robot.chassis.RightVelocity();
  // 计算当前速度

  if(left_velocity*current_left_velocity<0&&right_velocity*current_right_veolocity<0){// 左右两边都要反转
      if(fabs(left_velocity-current_left_velocity)>100&&fabs(right_velocity-current_right_veolocity)>100)k=0.24;
      else k=0.5;
  }
  else if(left_velocity*current_left_velocity<0||right_velocity*current_right_veolocity<0){// 某一边要反转
      if(fabs(left_velocity-current_left_velocity)>50||fabs(right_velocity-current_right_veolocity)>50)k=0.5;
      else k=1;
  }
  else {
      if(fabs(left_velocity-current_left_velocity)>75&&fabs(right_velocity-current_right_veolocity)>75)k=0.75;  // 无反转，但有急停或者急加速
      else k=1;
  }

  left_voltage=130*(k*left_velocity+(1-k)*current_left_velocity);
  right_voltage=130*(k*right_velocity+(1-k)*current_right_veolocity); 
  VoltageMove(left_voltage,right_voltage);  // 转化为电压并进行输出
}

void Intake(int intake_voltage){  //吸方块控制
  double max_voltage=13000;
  if(intake_voltage>max_voltage)intake_voltage=max_voltage;
  if(intake_voltage<-max_voltage)intake_voltage=-max_voltage;
  // 设定最大输出电压
  if(!intake_voltage){
    LeftIntake.stop(vex::brakeType::brake);
    RightIntake.stop(vex::brakeType::brake);
    LeftUpIntake.stop(vex::brakeType::brake);
    RightUpIntake.stop(vex::brakeType::brake);
  }
  if(intake_voltage>7500){
    LeftIntakeClamp.spin(vex::directionType::fwd,6500,vex::voltageUnits::mV);
    RightIntakeClamp.spin(vex::directionType::fwd,6500,vex::voltageUnits::mV);
    
    LeftIntake.spin(vex::directionType::fwd,intake_voltage,vex::voltageUnits::mV);
    RightIntake.spin(vex::directionType::fwd,intake_voltage,vex::voltageUnits::mV);
    LeftUpIntake.spin(vex::directionType::fwd,intake_voltage,vex::voltageUnits::mV);
    RightUpIntake.spin(vex::directionType::fwd,intake_voltage,vex::voltageUnits::mV);
  }
}

#endif

