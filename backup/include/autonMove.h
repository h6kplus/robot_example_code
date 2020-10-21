#ifndef AUTONMOVE_H
#define AUTONMOVE_H
#include "robot.h"
#include "utils.h"
#include "parameters.h"
#include "gyroScope.h"
#include "move_and_intake.h"


void turn(int delta_theta, double top_speed){  //top_Turnringspeed: mV

  double t=Brain.timer(vex::timeUnits::msec);   //reset the timer

    
  switch ((int)top_speed/1000){
    case 2:;
    case 3: params.setValue("turn_overshoot", 0);
            break;
    case 4: ;
    case 5: params.setValue("turn_overshoot", 100);
            break;
    case 6:
    case 7: 
    case 8: params.setValue("turn_overshoot", 500);
            break;
    case 9:
    case 10: params.setValue("turn_overshoot", 600);
            break;
    case 11:
    case 12: params.setValue("turn_overshoot", 0);
             break;
  }
  
  int isCounterClockwise = (delta_theta>0) ? 1 : -1; //是否逆时针转动
  int total_AngularDisplacement = abs(delta_theta);    //in 1000*rad
  double AccelDecel_AngularDisplacement = 0.2*total_AngularDisplacement;
  //coordinates are for gyro
  int theta0 = robot.getTheta(), currentTheta;

  //LW: Left wheel; RW: Right wheel; LM: Left Motor; RM: Right Motor
  double LM_topRotateSpeed = top_speed * (-1)*isCounterClockwise,
         RM_topRotateSpeed = top_speed * isCounterClockwise;
  double LM_currentRotateSpeed, RM_currentRotateSpeed;

  Brain.Screen.print("get startAngle:");
  Brain.Screen.print(theta0);
  Brain.Screen.newLine();


  //////////////////////////////////////////acceleration phase////////////////////////////////////////////////////
  Brain.Screen.print("accel turn phase");
  Brain.Screen.newLine();
  

  while(1){
    if(Brain.timer(vex::timeUnits::msec)-t>2000)break;
    LM_currentRotateSpeed = (top_speed *currentTheta/AccelDecel_AngularDisplacement+ params.getValue("accel_initMotorVolt")) * -isCounterClockwise;
    RM_currentRotateSpeed = (top_speed *currentTheta/AccelDecel_AngularDisplacement+ params.getValue("accel_initMotorVolt")) * isCounterClockwise; 

    //reach top-speed
    if (fabs(LM_currentRotateSpeed)>top_speed) LM_currentRotateSpeed = top_speed * -isCounterClockwise;
    if (fabs(RM_currentRotateSpeed)>top_speed) RM_currentRotateSpeed = top_speed * isCounterClockwise;

    robot.chassis.Move(LM_currentRotateSpeed, RM_currentRotateSpeed);

    //determine breaking condition using gyro.
    currentTheta=abs(turningAngle(robot.getTheta(),theta0));
    if (currentTheta > fabs(AccelDecel_AngularDisplacement)) break;  
  }
  Brain.Screen.newLine();
  Brain.Screen.print("accelbreakpoint: ");
  Brain.Screen.print(abs(currentTheta));
  Brain.Screen.newLine();
  
  //////////////////////////////////////////const-speed phase////////////////////////////////////////////////////
  Brain.Screen.print("const-speed turn phase");
  Brain.Screen.newLine();

  while(1){
    if(Brain.timer(vex::timeUnits::msec)-t>5000)break;   

    robot.chassis.Move(LM_topRotateSpeed, RM_topRotateSpeed);
    currentTheta=abs(turningAngle(robot.getTheta(),theta0));

    if(currentTheta > total_AngularDisplacement-AccelDecel_AngularDisplacement-params.getValue("turn_overshoot")) break;
  }

  Brain.Screen.print("constspeedbreakpoint: ");
  Brain.Screen.print(currentTheta);
  Brain.Screen.newLine();

  //////////////////////////////////////////deceleration phase////////////////////////////////////////////////////
  Brain.Screen.print("decel phase");
  Brain.Screen.newLine();

  int constphase_stopangle = currentTheta;

  while(1){
    if(Brain.timer(vex::timeUnits::msec)-t>5000)break;

    LM_currentRotateSpeed = ((1-(currentTheta-constphase_stopangle)/AccelDecel_AngularDisplacement)*top_speed + params.getValue("decel_constMotorVolt")) * -isCounterClockwise;
    RM_currentRotateSpeed = ((1-(currentTheta-constphase_stopangle)/AccelDecel_AngularDisplacement)*top_speed + params.getValue("decel_constMotorVolt")) * isCounterClockwise;
    if (fabs(LM_currentRotateSpeed)>top_speed) LM_currentRotateSpeed = top_speed * -isCounterClockwise;
    if (fabs(RM_currentRotateSpeed)>top_speed) RM_currentRotateSpeed = top_speed * isCounterClockwise;

    robot.chassis.Move(LM_currentRotateSpeed, RM_currentRotateSpeed);

    currentTheta=abs(turningAngle(robot.getTheta(),theta0));
    if(currentTheta > total_AngularDisplacement-params.getValue("turn_overshoot")) break;
  }
  
  Brain.Screen.print("decelbreakpoint: ");
  Brain.Screen.print(abs(currentTheta));
  Brain.Screen.newLine();

  //////////////////////////////////////////stop phase////////////////////////////////////////////////////
  robot.chassis.Brake("brake");
  vex::task::sleep(100);             //消除惯性
  robot.chassis.Brake("hold");

  vex::task::sleep(params.getValue("sleeptimeBetweenMoves"));

  currentTheta=turningAngle(robot.getTheta(),theta0);
  Brain.Screen.print("turn ends");
  Brain.Screen.newLine();
  Brain.Screen.print(currentTheta);
}
void goStraight(int dist, double top_speed, bool IntakeBlocks=0, double intakeTime=0){    //top_speed: mV   //dist in half_inches!!!
  
  robot.chassis.Reset();                        //reset the encoder
  double t=Brain.timer(vex::timeUnits::msec);   //reset the timer

  int isMovingFoward = dist>0 ?1 :-1; //1: move forward, -1: move backward
  double total_Displacement = abs(dist),
       //  total_Rotation = total_Displacement / robot.getWheelParameter() * 360;    //in deg
       total_Rotation = total_Displacement * 1.27 / chassis_ration;
  double topRotateSpeed = top_speed * isMovingFoward;
  //double AccelDecel_Rotation = top_speed / 35; //experimented formula
  double AccelDecel_Rotation = total_Rotation*0.1;
  
  if(AccelDecel_Rotation < total_Rotation/2) AccelDecel_Rotation = total_Rotation/2 ;

  int startAngle,currentAngle;

  startAngle = robot.getTheta();
  Brain.Screen.print("get startAngle:");
  Brain.Screen.print(startAngle);
  Brain.Screen.newLine();
  
  //rotated dist are for encoders, LM means left motor; RM means right motor
  double LM_currentRotation    , RM_currentRotation,
         LM_rotationError      , RM_rotationError;
  double LM_currentRotateSpeed , RM_currentRotateSpeed;

  //////////////////////////////////////////acceleration phase////////////////////////////////////////////////////
  Brain.Screen.print("accel phase");
  Brain.Screen.newLine();

  while(1){
    if(IntakeBlocks)break;
    if(Brain.timer(vex::timeUnits::msec)-t>2000)break;

    currentAngle=robot.getTheta();

    LM_currentRotation = fabs(robot.chassis.LeftRotation()), RM_currentRotation = fabs(robot.chassis.RightRotation());
    //LM_currentRotateSpeed = (LM_currentRotation * params.getValue("accelKp") + params.getValue("accel_initMotorVolt")) * isMovingFoward;
    //RM_currentRotateSpeed = (RM_currentRotation * params.getValue("accelKp") + params.getValue("accel_initMotorVolt")+600) * isMovingFoward;
    LM_currentRotateSpeed = (top_speed*LM_currentRotation/AccelDecel_Rotation + params.getValue("accel_initMotorVolt"))*isMovingFoward;
    RM_currentRotateSpeed = (top_speed*RM_currentRotation/AccelDecel_Rotation + params.getValue("accel_initMotorVolt"))*isMovingFoward;

    
    //keep moving in straight line using gyro
    if(abs(turningAngle(currentAngle, startAngle))>params.getValue("min_straightDriveAngle")){
      RM_currentRotateSpeed -= top_speed*params.getValue("Kp4StraightDrive")*turningAngle(currentAngle, startAngle);
      LM_currentRotateSpeed += top_speed*params.getValue("Kp4StraightDrive")*turningAngle(currentAngle, startAngle);

      if(fabs(RM_currentRotateSpeed)>13000)RM_currentRotateSpeed=13000*isMovingFoward;
      if(fabs(LM_currentRotateSpeed)>13000)LM_currentRotateSpeed=13000*isMovingFoward;
      
      if(fabs(RM_currentRotateSpeed)<500){Brain.Screen.print("vel=0");break;}
      if(fabs(LM_currentRotateSpeed)<500){Brain.Screen.print("vel=0");break;}
    }
    else{
    LM_currentRotation = fabs(robot.chassis.LeftRotation()), RM_currentRotation = fabs(robot.chassis.RightRotation());
    // LM_currentRotateSpeed = (LM_currentRotation * params.getValue("accelKp") + params.getValue("accel_initMotorVolt")) * isMovingFoward;
    //  RM_currentRotateSpeed = (RM_currentRotation * params.getValue("accelKp") + params.getValue("accel_initMotorVolt")+600) * isMovingFoward;
     LM_currentRotateSpeed = (top_speed*LM_currentRotation/AccelDecel_Rotation + params.getValue("accel_initMotorVolt"))*isMovingFoward;
     RM_currentRotateSpeed = (top_speed*RM_currentRotation/AccelDecel_Rotation + params.getValue("accel_initMotorVolt"))*isMovingFoward;
    }
    
    //reach top-speed
    if (fabs(LM_currentRotateSpeed)>fabs(topRotateSpeed)) LM_currentRotateSpeed = topRotateSpeed;
    if (fabs(RM_currentRotateSpeed)>fabs(topRotateSpeed)) RM_currentRotateSpeed = topRotateSpeed;

    robot.chassis.Move(LM_currentRotateSpeed, RM_currentRotateSpeed);
  
    if(LM_currentRotation>AccelDecel_Rotation && RM_currentRotation>AccelDecel_Rotation) break;
  }
  
  //////////////////////////////////////////const-speed phase////////////////////////////////////////////////////  
  Brain.Screen.print("const-speed phase");
  Brain.Screen.newLine();

  t=Brain.timer(vex::timeUnits::msec);
  while(1){
    if(IntakeBlocks) {
      pneumatics_close.set(true);
      pneumatics_open.set(false);
     // LeftPush.startRotateTo(params.getValue("down_value"), vex::rotationUnits::deg);
    //  RightPush.startRotateTo(params.getValue("down_value"), vex::rotationUnits::deg);
      Intake(13000);
     // if(Brain.timer(vex::timeUnits::msec)-t>intakeTime)break;
      if(total_Rotation-LM_currentRotation < AccelDecel_Rotation &&
        total_Rotation-RM_currentRotation < AccelDecel_Rotation)break;
    }
    if(Brain.timer(vex::timeUnits::msec)-t>8000)break; 

    currentAngle=robot.getTheta();
    
    if(abs(turningAngle(currentAngle, startAngle))>params.getValue("min_straightDriveAngle")){
      RM_currentRotateSpeed -= top_speed*params.getValue("Kp4StraightDrive")*turningAngle(currentAngle, startAngle);
      LM_currentRotateSpeed += top_speed*params.getValue("Kp4StraightDrive")*turningAngle(currentAngle, startAngle);
      if(RM_currentRotateSpeed>13000)RM_currentRotateSpeed=13000;
      if(LM_currentRotateSpeed>13000)LM_currentRotateSpeed=13000;
      if(RM_currentRotateSpeed<500){Brain.Screen.print("vel=0");break;}
      if(LM_currentRotateSpeed<500){Brain.Screen.print("vel=0");break;}
      Brain.Screen.print(turningAngle(currentAngle, startAngle));
      Brain.Screen.print("lv:");
      Brain.Screen.print(robot.chassis.LeftVelocity());
      Brain.Screen.print("rv:");
      Brain.Screen.print(robot.chassis.RightVelocity());
      Brain.Screen.newLine();
    }
    else{
    LM_currentRotateSpeed=top_speed * isMovingFoward;
    RM_currentRotateSpeed=(top_speed+600) * isMovingFoward;
    }

    robot.chassis.Move(LM_currentRotateSpeed, RM_currentRotateSpeed);     //TODO: 如何确定加速阶段已达最大速, 可将accel和constspeed写在一起

    //determine breaking conditions
    LM_currentRotation = fabs(robot.chassis.LeftRotation()), RM_currentRotation = fabs(robot.chassis.RightRotation());
    if( total_Rotation-LM_currentRotation < AccelDecel_Rotation &&
        total_Rotation-RM_currentRotation < AccelDecel_Rotation ) break;
  }
  if(IntakeBlocks){
    LeftIntake.stop(vex::brakeType::hold);
    RightIntake.stop(vex::brakeType::hold);
    LeftUpIntake.stop(vex::brakeType::hold);
    RightUpIntake.stop(vex::brakeType::hold);
    robot.chassis.Brake("hold");
    return;
  }
  
  //////////////////////////////////////////deceleration phase////////////////////////////////////////////////////
  Brain.Screen.print("decel phase");
  Brain.Screen.newLine();
  double left_error , left_integral  =0, left_last_error =0, left_D ,
         right_error, right_integral =0, right_last_error=0, right_D;

  //double time=Brain.timer(vex::timeUnits::msec)
  double frequency=0;
  
  params.setValue("decelKp", top_speed/AccelDecel_Rotation);
  while(1){
    //refresh left_error and right_error every 1 Msec.
    if(Brain.timer(vex::timeUnits::msec)-frequency>1){   //must execute the first time
      LM_currentRotation = fabs(robot.chassis.LeftRotation());
      RM_currentRotation = fabs(robot.chassis.RightRotation());
      left_error = fabs(total_Rotation - LM_currentRotation);
      right_error = fabs(total_Rotation - RM_currentRotation);
      frequency = Brain.timer(vex::timeUnits::msec);
    }
    //if(Brain.timer(vex::timeUnits::msec)-time>timelimit)break;    TODO

    //PID control
    left_integral    =   left_integral  + left_error ;
    right_integral   =   right_integral + right_error;
    left_last_error  =   left_error ;
    right_last_error =   right_error;
    left_D           =   left_error  - left_last_error ;
    right_D          =   right_error - right_last_error;


    LM_currentRotateSpeed = (params.getValue("decelKp")*left_error  + params.getValue("decelKi")*left_integral +
                             params.getValue("decelKd")*left_D      + params.getValue("decel_constMotorVolt"))*isMovingFoward;
    RM_currentRotateSpeed = (params.getValue("decelKp")*right_error + params.getValue("decelKi")*right_integral +
                             params.getValue("decelKd")*right_D     + params.getValue("decel_constMotorVolt"))*isMovingFoward;
    if (fabs(LM_currentRotateSpeed)>topRotateSpeed) LM_currentRotateSpeed = topRotateSpeed ;
    if (fabs(RM_currentRotateSpeed)>topRotateSpeed) RM_currentRotateSpeed = topRotateSpeed ;
    
    //TODO:是否需要维持直线 
    
    robot.chassis.Move(LM_currentRotateSpeed, RM_currentRotateSpeed);
        
    if(left_error>1||right_error>1) t=Brain.timer(vex::timeUnits::msec);
    if(Brain.timer(vex::timeUnits::msec)-t>=250)break;

    //determine breaking conditions        
    LM_currentRotation = fabs(robot.chassis.LeftRotation());
    RM_currentRotation = fabs(robot.chassis.RightRotation());

    if( total_Rotation-LM_currentRotation < 0 && total_Rotation-RM_currentRotation < 0) break;
  }


  //////////////////////////////////////////stop phase////////////////////////////////////////////////////
  //robot.chassis.Brake("brake");
  vex::task::sleep(100);             //消除惯性
  robot.chassis.Brake("hold");
  
  Brain.Screen.print("goStraight ends");

  currentAngle=robot.getTheta();
  if(abs(turningAngle(startAngle,currentAngle))>50) turn(turningAngle(startAngle,currentAngle), 2000);
  vex::task::sleep(params.getValue("sleeptimeBetweenMoves"));
}

void AutoPutBlocks(){
  double t= Brain.timer(vex::timeUnits::msec);
  double target_rotation=850, acceldecel_rotation=target_rotation*0.20;
  double Slideway_vel=0;
  double Slideway_top_vel=13000;
  double kp;
  pneumatics_close.set(true);
  pneumatics_open.set(false);
  while(1){
  LeftPush.spin(vex::directionType::rev, 13000, vex::voltageUnits::mV);
  RightPush.spin(vex::directionType::rev, 13000, vex::voltageUnits::mV);
  if (PushBumper.value()==1) {
    
    LeftPush.stop(vex::brakeType::hold);
    RightPush.stop(vex::brakeType::hold);
    LeftPush.resetRotation();
    RightPush.resetRotation();
    break;

  }
  }


  while(1){
    Slideway_vel = Slideway_top_vel * LeftPush.rotation(vex::rotationUnits::deg)/acceldecel_rotation+2000;
    LeftPush.spin(vex::directionType::fwd, Slideway_vel, vex::voltageUnits::mV);
    RightPush.spin(vex::directionType::fwd, Slideway_vel, vex::voltageUnits::mV);
    if(LeftPush.rotation(vex::rotationUnits::deg)>acceldecel_rotation)break;
  }
  while(1){
    LeftPush.spin(vex::directionType::fwd, Slideway_top_vel, vex::voltageUnits::mV);
    RightPush.spin(vex::directionType::fwd, Slideway_top_vel, vex::voltageUnits::mV);
    if(LeftPush.rotation(vex::rotationUnits::deg)>target_rotation-acceldecel_rotation)break;
  }
  while(1){
    LeftIntake.spin(vex::directionType::fwd,13000,vex::voltageUnits::mV);
    RightIntake.spin(vex::directionType::fwd,13000,vex::voltageUnits::mV);
    Slideway_vel = Slideway_top_vel * (1 - (LeftPush.rotation(vex::rotationUnits::deg)-(target_rotation-acceldecel_rotation))/acceldecel_rotation)+1000;
    LeftPush.spin(vex::directionType::fwd, Slideway_vel, vex::voltageUnits::mV);
    RightPush.spin(vex::directionType::fwd, Slideway_vel, vex::voltageUnits::mV);
   //if(Brain.timer(msec)-t>3000)break;
  }
  Brain.Screen.print("ok");
  LeftPush.stop(vex::brakeType::brake);RightPush.stop(vex::brakeType::brake);
  LeftIntake.stop(vex::brakeType::hold);
  RightIntake.stop(vex::brakeType::hold);
  vex::task::sleep(100);
  LeftPush.stop(vex::brakeType::hold);RightPush.stop(vex::brakeType::hold);
 vex::task::sleep(100);

  pneumatics_close.set(false);
  pneumatics_open.set(true);

  //Slideway1.spinFor(-target_rotation, deg, 100, vex::velocityUnits::pct);
  //Slideway2.spinFor(-target_rotation, deg, 100, vex::velocityUnits::pct);

}
void Rotate(int delta_theta, double speed, double fixing_speed=2000){
  
  int theta0=robot.getTheta();
  int targetTheta; 
  int currentTheta;

  targetTheta = (theta0+delta_theta+6280)%6280 ;
  turn(delta_theta,speed);
  currentTheta=robot.getTheta();

  if(abs(turningAngle(targetTheta, currentTheta))>50)turn(turningAngle(targetTheta, currentTheta),fixing_speed);
  
}

#endif