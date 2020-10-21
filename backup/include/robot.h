#ifndef ROBOT_H
#define ROBOT_H
#include <IRsensor.h>
#include <gyroScope.h>
#include "map.h"
#include "chassisControl.h"
#include "vex.h"
#include "parameters.h"
#define PI 3.1416

class Robot
{
private:
    //params of robot:
    double m_robotWidth         =    params.getValue("robotWidth")        ;                        //TODO:测距传感器是否在机器最外侧
    double m_wheelDiameter      =    params.getValue("wheelDiameter")     ;   //all length in half_inches
    double m_wheelDistance      =    params.getValue("wheelDistance")     ;   //length between left and right wheels
    double m_MotorGearRatio     =    params.getValue("MotorGearRatio")    ;
    double m_WheelGearRatio     =    params.getValue("WheelGearRatio")     ;   //
    int m_initAngle=0;      //100*rad
    int m_posx=0, m_posy=0;   //central point coordinate
    int m_currentAngle;   //100*rad

  public:
    Robot(int side)
    {
      //robot has to stick to the wall.
      m_initAngle = side == 0? 0: 3140;
    }
    
    Chassis chassis;

    //set current Angle using gyro
    void setCurrentAngle(){
      m_currentAngle = (mygyro.getSensorAngle() + m_initAngle) % 6280;
    }
    //set pos_x and pos_y, use ToF sensor to regulate
    void setCurrentPos(int x,int y){
        m_posx = x;
        m_posy = y;
    }
    int getX() const{ return m_posx; }  
    int getY() const{ return m_posy; }  //must setPos before using!!!

    int getTheta() {
      setCurrentAngle();
      return m_currentAngle; 
    }

    int getRobotWidth() const{ return m_robotWidth; }
    int getWheelDiameter() const{ return m_wheelDiameter; }
    double getWheelParameter() const{ return m_wheelDiameter * 2 * PI; }
    double getWheelDistance() const{ return m_wheelDistance;}

};

Robot robot(0);

#endif
