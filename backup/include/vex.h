#ifndef VEX_H
#define VEX_H
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include "v5.h"
#include "v5_vcs.h"
vex::brain Brain;
vex::controller Controller = vex::controller();

//////////////////////////////motors////////////////////////////////
// wheel motors:
vex::motor LeftWheel1(vex::PORT2,vex::gearSetting::ratio6_1,false);  // 8个600rpm底盘马达
vex::motor LeftWheel2(vex::PORT3,vex::gearSetting::ratio6_1,true);
vex::motor LeftWheel3(vex::PORT4,vex::gearSetting::ratio6_1,false);
vex::motor LeftWheel4(vex::PORT5,vex::gearSetting::ratio6_1,true);
vex::motor RightWheel1(vex::PORT9,vex::gearSetting::ratio6_1,true);
vex::motor RightWheel2(vex::PORT8,vex::gearSetting::ratio6_1,false);
vex::motor RightWheel3(vex::PORT7,vex::gearSetting::ratio6_1,true);
vex::motor RightWheel4(vex::PORT6,vex::gearSetting::ratio6_1,false);

// // functional motors
vex::motor LeftIntake(vex::PORT12,vex::gearSetting::ratio36_1,false); // 4个100rpm吸方块马达
vex::motor RightIntake(vex::PORT20,vex::gearSetting::ratio36_1,true);
vex::motor LeftUpIntake(vex::PORT13,vex::gearSetting::ratio36_1,false);
vex::motor RightUpIntake(vex::PORT19,vex::gearSetting::ratio36_1,true);
vex::motor LeftPush(vex::PORT1,vex::gearSetting::ratio36_1,false); // 2个100rpm底座马达
vex::motor RightPush(vex::PORT10,vex::gearSetting::ratio36_1,true);

//sensors using smart ports as generic serial port:
vex::motor myGyroscope(vex::PORT18,vex::gearSetting::ratio18_1,false);
// vex::motor myPneumatics(vex::PORT19,vex::gearSetting::ratio18_1,false);

//vex's sensors using the ordinary three-wire ports:
vex::pneumatics pneumatics_close = vex::pneumatics(Brain.ThreeWirePort.A);
vex::pneumatics pneumatics_open = vex::pneumatics(Brain.ThreeWirePort.B);

vex::bumper PushBumper = vex::bumper(Brain.ThreeWirePort.C);
vex::limit ChooseLimit = vex::limit(Brain.ThreeWirePort.D); 



#endif
