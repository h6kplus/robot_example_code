#ifndef GYROSCOPE_H
#define GYROSCOPE_H
#include "vex.h"
#include "utils.h"
class Gyroscope
{
private:
  uint8_t buffer[256];
public:

  Gyroscope(){
    vexGenericSerialEnable(myGyroscope.index(),  0);
    vexGenericSerialBaudrate(myGyroscope.index(), 115200);
  }
  //sensorAngle in 100*rad
  int getSensorAngle(){
    int32_t numsRead, angleRead;
    int i;
    
    while(1){
      vex::task::sleep(40);
      numsRead = vexGenericSerialReceive(myGyroscope.index(), buffer, sizeof(buffer));

      //Brain.Screen.print(numsRead);
      //Brain.Screen.print(" ");
      if(numsRead==0){
        Brain.Screen.print("!!!WARNING!!!no gyro value read!! check if burnt");
        Brain.Screen.newLine();
        continue;
      }
     // for(int i=0;i<sizeof(buffer)/numsRead +1;i++){
     // Brain.Screen.print((buffer[i]));}
     // Brain.Screen.print(" ");

      i=0;
      while(1){
        if(buffer[i]==255)break;
        i+=1;
      }
      //Brain.Screen.print(buffer[1]-1);
      
      //Brain.Screen.print(buffer[2]-1);
      
      //Brain.Screen.print(buffer[3]-1);
      
      //Brain.Screen.print(buffer[4]-1);
      //Brain.Screen.print((buffer[1]-1)*1000);
      //Brain .Screen.print(" ");
      angleRead = (buffer[i+1]-1)*1000+(buffer[i+2]-1)*100+(buffer[i+3]-1)*10+(buffer[i+4]-1);
      
      if(angleRead<0 || angleRead>=6280){
        Brain.Screen.print("wrong gyro num!");
        Brain.Screen.newLine();
        continue;
      }
      
      return angleRead;
    }
  }
};
Gyroscope mygyro;
#endif