#include "vex.h"
#include "push.h"
#include "move_and_intake.h"
#include "utils.h"
#include "autonMove.h"
using namespace vex;
void Red(){
  int gyroerror=0;
  Brain.Screen.newLine();
  Brain.Screen.print("startangle:");
  Brain.Screen.print(robot.getTheta());
  Brain.Screen.newLine();

  LeftPush.resetRotation();
  RightPush.resetRotation();
  int theta0 = robot.getTheta();
  Brain.Screen.print( theta0 );
  Brain.Screen.newLine();
  //Push(-4000);
  LeftPush.startRotateTo(params.getValue("vertical_value"), vex::rotationUnits::deg);
  RightPush.startRotateTo(params.getValue("vertical_value"), vex::rotationUnits::deg);
 
   goStraight(-60, 10000);
   pneumatics_close.set(false);
   pneumatics_open.set(true);
   vex::task::sleep(4000);

  // goStraight(55,10000);
  
  LeftPush.startRotateTo(params.getValue("down_value"), vex::rotationUnits::deg);
  RightPush.startRotateTo(params.getValue("down_value"), vex::rotationUnits::deg);
  Rotate(turningAngle(785-gyroerror, robot.getTheta()),6000);

  

  goStraight(-15, 8000);

  
  
  Rotate(turningAngle(1570-gyroerror,robot.getTheta()), 6000,2000);
  //Rotate(-785, 8000 ,2000);
  // goStraight(6, 5000);

  // Rotate(-1570,8000);
  
  
 // vex::task::sleep(800);
 
  LeftPush.startRotateTo(params.getValue("vertical_value"), vex::rotationUnits::deg);
  RightPush.startRotateTo(params.getValue("vertical_value"), vex::rotationUnits::deg);

  // pneumatics_close.set(false);
  // pneumatics_open.set(true);

  vex::task::sleep(500);
  goStraight(20,  2000);
  
  vex::task::sleep(400);

  pneumatics_close.set(true);
  pneumatics_open.set(false);

  vex::task::sleep(700);
  //LeftUpIntake.spin(vex::directionType::fwd,5000,vex::voltageUnits::mV);
  //RightUpIntake.spin(vex::directionType::fwd,5000,vex::voltageUnits::mV);


  //while(1);

 // LeftPush.startRotateTo(params.getValue("down_value"), vex::rotationUnits::deg, 50,vex::velocityUnits::pct);
 // RightPush.startRotateTo(params.getValue("down_value"), vex::rotationUnits::deg,50, vex::velocityUnits::pct);

while(PushBumper.value()!=1){
  LeftPush.spin(vex::directionType::rev,10000,vex::voltageUnits::mV);
  RightPush.spin(vex::directionType::rev,10000,vex::voltageUnits::mV);
}

LeftPush.stop(vex::brakeType::hold);
RightPush.stop(vex::brakeType::hold);
LeftPush.resetRotation();
RightPush.resetRotation();

//第一列四个方块收完
pneumatics_close.set(true);
pneumatics_open.set(false); 

LeftUpIntake.spin(vex::directionType::fwd,8000,vex::voltageUnits::mV);
RightUpIntake.spin(vex::directionType::fwd,8000,vex::voltageUnits::mV);
vex::task::sleep(50);
LeftPush.startRotateTo(params.getValue("down_value"), vex::rotationUnits::deg, 50,vex::velocityUnits::pct);
RightPush.startRotateTo(params.getValue("down_value"), vex::rotationUnits::deg,50, vex::velocityUnits::pct);


goStraight(-25, 10000);
//while(1);
Rotate(700-gyroerror,6000);
 //Rotate(turningAngle(robot.getTheta(), 6280-1570-600), 8000);

goStraight(-15, 8000);

//Intake(13000);
LeftIntake.spin(vex::directionType::fwd,13000,vex::voltageUnits::mV);
RightIntake.spin(vex::directionType::fwd,13000,vex::voltageUnits::mV);
LeftUpIntake.spin(vex::directionType::fwd,8000,vex::voltageUnits::mV);
RightUpIntake.spin(vex::directionType::fwd,8000,vex::voltageUnits::mV);

//吸第五个方块
//Intake(11000);
goStraight(30,4000); 
vex::task::sleep(200);
goStraight(-35, 8000);
 //Intake(-13000);
 //vex::task::sleep(100);

Rotate(350-gyroerror, 4000);
pneumatics_close.set(false);
pneumatics_open.set(false);
vex::task::sleep(50);
pneumatics_close.set(true);
pneumatics_open.set(false); 

//吸第六个方块
goStraight(30, 4000);
vex::task::sleep(200);

goStraight(-10, 4000);

Rotate(turningAngle(0-gyroerror, robot.getTheta()),6000);
//Intake(13000);

// //导轨降低
// while(PushBumper.value()!=1){
//   LeftPush.spin(vex::directionType::rev,8000,vex::voltageUnits::mV);
//   RightPush.spin(vex::directionType::rev,8000,vex::voltageUnits::mV);
// }

// LeftPush.stop(vex::brakeType::hold);
// RightPush.stop(vex::brakeType::hold);
// LeftPush.resetRotation();
// RightPush.resetRotation();

Intake(13000);
//回头吸第七第八个
params.setValue("decel_proportion4goStraight",0.4);
//params.setValue("sleeptimeBetweenMoves", 500);
goStraight(45,8000);
//goStraight(10,8000);

//Intake(0);

//params.setValue("decel_proportion4goStraight",0.7);
//转身吸第九个

LeftUpIntake.spin(vex::directionType::fwd,5000,vex::voltageUnits::mV);
RightUpIntake.spin(vex::directionType::fwd,5000,vex::voltageUnits::mV);
//goStraight(-15, 5000);
//RightIntakeClamp.spin(vex::directionType::rev,12000,vex::voltageUnits::mV);
//vex::task::sleep(100);
//RightIntakeClamp.spin(vex::directionType::fwd,6500,vex::voltageUnits::mV);

Rotate(turningAngle(1570-gyroerror, robot.getTheta()), 6000);
LeftUpIntake.spin(vex::directionType::fwd,10000,vex::voltageUnits::mV);
RightUpIntake.spin(vex::directionType::fwd,10000,vex::voltageUnits::mV);
LeftIntake.spin(vex::directionType::fwd,13000,vex::voltageUnits::mV);
RightIntake.spin(vex::directionType::fwd,13000,vex::voltageUnits::mV);
goStraight(40, 6000);

robot.chassis.Move(4000, -4000);
vex::task::sleep(100);
robot.chassis.Brake("brake");
goStraight(15, 5000);
vex::task::sleep(100);
//goStraight(-15, 4000);
///robot.chassis.Move(4000, -4000);
//vex::task::sleep(100);
//robot.chassis.Brake("brake");


//Intake(0);

//移动到得分区
goStraight(-75, 5000);
Rotate(turningAngle(785-gyroerror, robot.getTheta()),5000);
goStraight(-15, 5000);
Rotate(turningAngle(-50-gyroerror,robot.getTheta()), 5000);
goStraight(32, 5000);
turn(-400,7000);
//Rotate(turningAngle(150-gyroerror, robot.getTheta()),2000);
//Rotate(turningAngle(150-gyroerror, robot.getTheta()),3500);
//goStraight(10, 3000);
//Rotate(100,2000);
double t=Brain.timer(vex::timeUnits::msec);
while(Brain.timer(timeUnits::msec)-t<3500){
  LeftIntake.spin(vex::directionType::fwd,10000,vex::voltageUnits::mV);
  RightIntake.spin(vex::directionType::fwd,10000,vex::voltageUnits::mV);
  LeftUpIntake.spin(vex::directionType::rev,5000,vex::voltageUnits::mV);
  RightUpIntake.spin(vex::directionType::rev,5000,vex::voltageUnits::mV);
  Auto_Push();
}
//goStraight(3, 2000);
Intake(0);
pneumatics_close.set(false);
pneumatics_open.set(true);


LeftPush.startRotateTo(params.getValue("down_value"), vex::rotationUnits::deg, 50,vex::velocityUnits::pct);
RightPush.startRotateTo(params.getValue("down_value"), vex::rotationUnits::deg,50, vex::velocityUnits::pct);

vex::task::sleep(500);
RightIntakeClamp.stop(vex::brakeType::coast);
LeftIntakeClamp.spin(vex::directionType::rev,13000,vex::voltageUnits::mV);

RightIntakeClamp.spin(vex::directionType::rev,13000,vex::voltageUnits::mV);
Intake(-2000);
//goStraight(-10, 2000);

//LeftIntakeClamp.spin(vex::directionType::rev,8000,vex::voltageUnits::mV);
vex::task::sleep(200);

goStraight(-30, 13000);

RightIntakeClamp.stop(vex::brakeType::coast);
LeftIntakeClamp.stop(vex::brakeType::coast);
Intake(0);


}