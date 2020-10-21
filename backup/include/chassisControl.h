#ifndef CHASSISCONTRIL_H
#define CHASSISCONTROL_H
#include "vex.h"

class Chassis{
public:
  void Move(double leftVel, double rightVel){
  LeftWheel1.spin(vex::directionType::fwd, leftVel, vex::voltageUnits::mV);
  LeftWheel2.spin(vex::directionType::fwd, leftVel, vex::voltageUnits::mV);
  LeftWheel3.spin(vex::directionType::fwd, leftVel, vex::voltageUnits::mV);
  LeftWheel4.spin(vex::directionType::fwd, leftVel, vex::voltageUnits::mV);

  RightWheel1.spin(vex::directionType::fwd, rightVel, vex::voltageUnits::mV);
  RightWheel2.spin(vex::directionType::fwd, rightVel, vex::voltageUnits::mV);
  RightWheel3.spin(vex::directionType::fwd, rightVel, vex::voltageUnits::mV);
  RightWheel4.spin(vex::directionType::fwd, rightVel, vex::voltageUnits::mV);
  }

  void Brake(std::string braketype){
    if(braketype == "hold"){
      LeftWheel1.stop(vex::brakeType::hold);
      LeftWheel2.stop(vex::brakeType::hold);
      LeftWheel3.stop(vex::brakeType::hold);
      LeftWheel4.stop(vex::brakeType::hold);
      RightWheel1.stop(vex::brakeType::hold);
      RightWheel2.stop(vex::brakeType::hold);
      RightWheel3.stop(vex::brakeType::hold);
      RightWheel4.stop(vex::brakeType::hold);
    }
    else if(braketype == "coast"){
      LeftWheel1.stop(vex::brakeType::coast);
      LeftWheel2.stop(vex::brakeType::coast);
      LeftWheel3.stop(vex::brakeType::coast);
      LeftWheel4.stop(vex::brakeType::coast);
      RightWheel1.stop(vex::brakeType::coast);
      RightWheel2.stop(vex::brakeType::coast);
      RightWheel3.stop(vex::brakeType::coast);
      RightWheel4.stop(vex::brakeType::coast);
    }
    else if (braketype == "brake"){
      LeftWheel1.stop(vex::brakeType::brake);
      LeftWheel2.stop(vex::brakeType::brake);
      LeftWheel3.stop(vex::brakeType::brake);
      LeftWheel4.stop(vex::brakeType::brake);
      RightWheel1.stop(vex::brakeType::brake);
      RightWheel2.stop(vex::brakeType::brake);
      RightWheel3.stop(vex::brakeType::brake);
      RightWheel4.stop(vex::brakeType::brake);
    }
    else Brain.Screen.print("!!Warning!!no matching braketype!!");
  }

  void Reset(){
    LeftWheel1.resetRotation();
    LeftWheel2.resetRotation();
    LeftWheel3.resetRotation();
    LeftWheel4.resetRotation();
    RightWheel1.resetRotation();
    RightWheel2.resetRotation();
    RightWheel3.resetRotation();
    RightWheel4.resetRotation();
  }
  double LeftRotation(){
    return (LeftWheel1.rotation(vex::rotationUnits::deg)+LeftWheel2.rotation(vex::rotationUnits::deg)+
            LeftWheel3.rotation(vex::rotationUnits::deg)+LeftWheel4.rotation(vex::rotationUnits::deg))/4;//TODO:乘传动比!!
  }
  double RightRotation(){
    return (RightWheel1.rotation(vex::rotationUnits::deg)+RightWheel2.rotation(vex::rotationUnits::deg)+
            RightWheel3.rotation(vex::rotationUnits::deg)+RightWheel4.rotation(vex::rotationUnits::deg))/4; 
  }
  //returns in pct
  double LeftVelocity(){
    return (LeftWheel1.velocity(vex::percentUnits::pct)+LeftWheel2.velocity(vex::percentUnits::pct)+
            LeftWheel3.velocity(vex::percentUnits::pct)+LeftWheel4.velocity(vex::percentUnits::pct)) /4;
  }
  double RightVelocity(){
    return (RightWheel1.velocity(vex::percentUnits::pct)+RightWheel2.velocity(vex::percentUnits::pct)+
            RightWheel3.velocity(vex::percentUnits::pct)+RightWheel4.velocity(vex::percentUnits::pct)) /4;
  }
};

#endif