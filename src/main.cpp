#include "vex.h"
#include "push.h"
#include "move_and_intake.h"
#include "status.h"
#include "red.cpp"
#include "blue.cpp"
#include "autonMove.h"
using namespace vex;
vex::competition Competition;

int choose=1; //一共两套自动程序
void pre_auton( void ) { //选自动程序
    // while(1){
    // static double choose_timer = Brain.timer(vex::timeUnits::msec);
    // if (Brain.timer(vex::timeUnits::msec) - choose_timer > 1000) {
    //   if (ChooseLimit.pressing()){
    //       choose = choose%2 + 1;
    //       choose_timer = Brain.timer(vex::timeUnits::msec);
    //   }
    // } 
    switch(choose)
    {
      case 1:Brain.Screen.printAt(  10, 220, "Red");break;
      case 2:Brain.Screen.printAt(  10, 220, "Blue");break;
    }
  
}

void autonomous( void ) { //自动程序
choose=1;
      switch(choose)
    {
      case 1:Red();break;
      case 2:Blue();break;
    }
}



void usercontrol( void ) {
  int C1,C2,C3,C4,L1,L2,R1,R2,X,Y,A,B,L,R,U,D,left_velocity,right_velocity; //定义遥控器遥感和按键
  double clamp_timer=0; //定义气动计时器
  double leave_timer, push_start_timer=0; //定义X按下的计时器
  int move_straight,turn,push_foward,push_back,cube_in,cube_out,clamp,score,leave;
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
    //  遥感功能  
    move_straight=C3;
    turn=C1;
    clamp=A;
    push_foward=X;
    push_back=B;
    score=L1;
    leave=L2;
    cube_in=R1;
    cube_out=R2;
    //智能一键放方块,需要按住
    if(score){
      Auto_Push();
      continue;
    }
    else if(leave){
      leave_timer=Brain.timer(timeUnits::msec);
      Auto_Leave(leave_timer,push_start_timer);
      continue;
    }
    else if(Brain.timer(timeUnits::msec)-score>500)push_start_timer=Brain.timer(timeUnits::msec);

    // 基本气动系统控制以及输出
    if(cube_in){  //吸方块时夹子夹紧
      pneumatics_close.set(true);
      pneumatics_open.set(false);  
    }
    else if(clamp && Brain.timer(timeUnits::msec)-clamp_timer>500){
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
    if(push_foward)PID_Push();
    else if(push_back)Push(-13000);
    else if(cube_in){
      if((RightPush.rotation(vex::rotationUnits::deg)+LeftPush.rotation(vex::rotationUnits::deg))/2>params.getValue("down_value")+25)Push(-6500);
      else if((RightPush.rotation(vex::rotationUnits::deg)+LeftPush.rotation(vex::rotationUnits::deg))/2<params.getValue("down_value")-25)Push(6500);
      else Push(0);
    }
    else Push(0);

    // 底盘控制
    if(abs(turn)<10)turn=0;
    if(abs(move_straight)<10)move_straight=0;
    if(turn>60)turn=60+0.5*(turn-60);
    if(turn<-60)turn=-60-0.5*(turn+60);
    // 吸方块控制及输出
    if(cube_in){ //吸的时候需要关闭夹子
      pneumatics_close.set(true);
      pneumatics_open.set(false);    
      Intake(13000);
    }
    else if(cube_out) Intake(-13000);
    else Intake(0);
    

    //底盘输出
    left_velocity=move_straight+turn;
    right_velocity=move_straight-turn;
    move(left_velocity,right_velocity);



    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {

 // while(1)Rotate(-1570,8000);
  
    //  goStraight(300,3000);
  /*while(1){
    Brain.Screen.print(robot.getTheta());
    Brain.Screen.newLine();
  }
  goStraight(-49, 5000);

  
  Rotate(-785, 8000,2000);
  goStraight(-25, 5000);
 // Rotate(1570,8000);*/
  //while(1);
  pre_auton();  
  Competition.autonomous( autonomous );
  Competition.drivercontrol( usercontrol );
    //vex::task t1(status);     
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}