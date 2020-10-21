#include "vex.h"
#include "push.h"
#include "move_and_intake.h"
#include "utils.h"
#include "autonMove.h"
void Blue(){
  LeftPush.resetRotation();
  RightPush.resetRotation();
  int theta0 = robot.getTheta();
  
  //Push(-4000);
  
 /* LeftPush.resetRotation();RightPush.resetRotation();
  goStraight(-55, 5000);

// params.setValue("char *param", double val)
  
  pneumatics_close.set(false);
  pneumatics_open.set(true);
  
 Rotate(-785, 8000,2000);
 goStraight(-15, 5000);
  
  Rotate(-785, 8000,2000);
 // goStraight(6, 5000);

 // Rotate(-1570,8000);
  
  LeftPush.startRotateTo(params.getValue("vertical_value"), vex::rotationUnits::deg);
  RightPush.startRotateTo(params.getValue("vertical_value"), vex::rotationUnits::deg);
  vex::task::sleep(1000);
  

  
  goStraight(15,  2000);

  
  vex::task::sleep(300);

  pneumatics_close.set(true);
  pneumatics_open.set(false);

  
  vex::task::sleep(300);

 // LeftPush.startRotateTo(params.getValue("down_value"), vex::rotationUnits::deg, 50,vex::velocityUnits::pct);
 // RightPush.startRotateTo(params.getValue("down_value"), vex::rotationUnits::deg,50, vex::velocityUnits::pct);
 LeftPush.spin(vex::directionType::rev,8000,vex::voltageUnits::mV);
 RightPush.spin(vex::directionType::rev,8000,vex::voltageUnits::mV);
 
  vex::task::sleep(1500);
 if(PushBumper.value()==1){
   LeftPush.stop(vex::brakeType::hold);
   RightPush.stop(vex::brakeType::hold);
   LeftPush.resetRotation();
   RightPush.resetRotation();
 }
 */
 LeftPush.startRotateTo(params.getValue("down_value"), vex::rotationUnits::deg, 50,vex::velocityUnits::pct);
 RightPush.startRotateTo(params.getValue("down_value"), vex::rotationUnits::deg,50, vex::velocityUnits::pct);
 pneumatics_close.set(true);
 pneumatics_open.set(false);
 goStraight(-25, 4000);
// Rotate(-785, 8000);
 //goStraight(10, 8000);
 Rotate(-600, 8000);
 Intake(13000);
 goStraight(-10, 4000);
 goStraight(20, 4000);
 goStraight(-20, 4000);
 Rotate(-400, 8000);
 goStraight(20, 4000);
 vex::task::sleep(1000);
 Rotate(2570,8000);


 while(1);
//goStraight(18, 4000);
Rotate(-785, 8000);
//LeftIntake.spin(vex::directionType::rev,13000,vex::voltageUnits::mV);
//RightIntake.spin(vex::directionType::rev,13000,vex::voltageUnits::mV);

Intake(13000);
vex::task::sleep(500);
goStraight(15, 4000);
vex::task::sleep(200);
//Intake(0);
//goStraight(-15, 4000);
Rotate(785, 8000);

goStraight(15, 4000);


while(0);
  //Rotate(-1570, 8000);

 // Intake(13000);

  Rotate(-350, 3000);
  goStraight(20, 4000, 1, 3000);
  //vex::task::sleep(1000);
  Intake(0);
  goStraight(-20,4000);
  
  Rotate(-100, 3000);
  
  Intake(13000);
  goStraight(45, 4000);
  vex::task::sleep(1000);
  Intake(0);
  goStraight(-45,4000);

  
  Intake(13000);
  Rotate(-1570,4000);
  goStraight(5, 2000);
  vex::task::sleep(200);
  Intake(0);
  goStraight(-5, 2000);
  Rotate(1570,4000);

  while(1);

  Rotate(-500, 6000);
  goStraight(90, 3000);
  Intake(13000);
  vex::task::sleep(500);
  goStraight(-70, 3000);

  Rotate(157, 6000);
  goStraight(70, 3000,1,4000);
  goStraight(-70, 3000);

  turn(657, 6000);
  
  goStraight(60, 4000,1,7000);

  Intake(0);


  


  //LeftPush.rotateTo(params.getValue("down_value"), vex::rotationUnits::deg);
  //RightPush.rotateTo(params.getValue("down_value"), vex::rotationUnits::deg);
  


}