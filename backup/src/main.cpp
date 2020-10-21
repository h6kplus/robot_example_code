#include "vex.h"
#include "push.h"
#include "move_and_intake.h"
#include "status.h"
#include "red.cpp"
#include "blue.cpp"
#include "parameters.h"
using namespace vex;
vex::competition Competition;

int choose=2; //一共两套自动程序
void pre_auton( void ) { //选自动程序
return;
    while(1){
    static double choose_timer = Brain.timer(vex::timeUnits::msec);
    if (Brain.timer(vex::timeUnits::msec) - choose_timer > 1000) {
      if (ChooseLimit.pressing()){
          choose = choose%2 + 1;
          choose_timer = Brain.timer(vex::timeUnits::msec);
      }
    } 
    switch(choose)
    {
      case 1:Brain.Screen.printAt(  10, 220, "Red");break;
      case 2:Brain.Screen.printAt(  10, 220, "Blue");break;
    }
  }
}

void autonomous( void ) { //自动程序
choose=2;
      switch(choose)
    {
      case 1:Red();break;
      case 2:Blue();break;
    }
}
void usercontrol( void ) {
  int C1,C2,C3,C4,L1,L2,R1,R2,X,Y,A,B,L,R,U,D,left_velocity,right_velocity; //定义遥控器遥感和按键
  double clamp_timer=0; //定义气动计时器
  double X_timer=0; //定义X按下的计时器
  double push_start_timer=0;  //定义开始自动推方块计时器
  Brain.resetTimer();
  while (1) {
    // 获取遥控器指令
    C1=Controller.Axis1.position(vex::percentUnits::pct);
    C2=Controller.Axis2.position(vex::percentUnits::pct);
    C3=Controller.Axis3.position(vex::percentUnits::pct);
    C4=Controller.Axis4.position(vex::percentUnits::pct);
    L1=Controller.ButtonL1.pressing();
    L2=Controller.ButtonL2.pressing();
    R1=Controller.ButtonR1.pressing();        
    R2=Controller.ButtonR2.pressing();
    X=Controller.ButtonX.pressing();
    Y=Controller.ButtonY.pressing();
    A=Controller.ButtonA.pressing();
    B=Controller.ButtonB.pressing();
    L=Controller.ButtonLeft.pressing();
    R=Controller.ButtonRight.pressing();        
    U=Controller.ButtonUp.pressing();
    D=Controller.ButtonDown.pressing();  
    //智能一键放方块,需要按住
    if(X){
      X_timer=Brain.timer(timeUnits::msec);
      Auto_Push(X_timer,push_start_timer);
      continue;
    }
    else if(Brain.timer(timeUnits::msec)-X_timer>500)push_start_timer=Brain.timer(timeUnits::msec);

    // 基本气动系统控制以及输出
    if(A && Brain.timer(timeUnits::msec)-clamp_timer>500){
    clamp_timer = Brain.timer(timeUnits::msec);
      if(pneumatics_close.value()){ // 打开夹子
          pneumatics_close.set(false);
          pneumatics_open.set(true);
      }
      else {  // 关闭夹子
          pneumatics_close.set(true);
          pneumatics_open.set(false);                    
      }
    }

    // 基本底座控制及输出
    if(R1)PID_Push();
    else if(R2)Push(-13000);
    else Push(0);

    // 底盘控制
    if(U)C3+=50;
    if(D)C3-=50;
    if(L)C1-=30;
    if(R)C1+=30;
    if(abs(C1)<10)C1=0;
    if(abs(C3)<10)C3=0;
    if(C1>60)C1=60+0.5*(C1-60);
    if(C1<-60)C1=-60-0.5*(C1+60);
    // 吸方块控制及输出
    if(L1){ //吸的时候需要关闭夹子
      pneumatics_close.set(true);
      pneumatics_open.set(false);    
      Intake(13000);
      if((RightPush.rotation(vex::rotationUnits::deg)+LeftPush.rotation(vex::rotationUnits::deg))/2>params.getValue("down_value")+25)Push(-8000);
      if((RightPush.rotation(vex::rotationUnits::deg)+LeftPush.rotation(vex::rotationUnits::deg))/2<params.getValue("down_value")-25)Push(5000);
    }
    else if(L2) Intake(-13000);
    else Intake(0);
    

    //底盘输出
    left_velocity=C3+C1;
    right_velocity=C3-C1;
    move(left_velocity,right_velocity);



    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  
    //  goStraight(300,3000);
  /*while(1){
    Brain.Screen.print(robot.getTheta());
    Brain.Screen.newLine();
  }
  goStraight(-49, 5000);

  
  Rotate(-785, 8000,2000);
  goStraight(-25, 5000);
 // Rotate(1570,8000);
  while(1);*/
   pre_auton();  
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    //vex::task t1(status);     
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}