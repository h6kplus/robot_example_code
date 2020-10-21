#ifndef MAP_H
#define MAP_H
#include<string.h>
extern bool fieldmap[282][282];
extern int cubex[47],cubey[47],towerx[5],towery[5];

int getFieldWidth(){ return sizeof(fieldmap)/sizeof(fieldmap[0]);}  //returns 282

void makemap(){
	int i,j,k;
	cubex[0] = 33;cubey[0] = 140;
	cubex[1] = 46;cubey[1] = 127;
	cubex[2] = 46;cubey[2] = 154;
	cubex[3] = 53;cubey[3] = 194;
	cubex[4] = 53;cubey[4] = 240;
	cubex[5] = 67;cubey[5] = 53;
	cubex[6] = 78;cubey[6] = 53;
	cubex[7] = 78;cubey[7] = 100;
	cubex[8] = 90;cubey[8] = 53;
	cubex[9] = 90;cubey[9] = 100;
	cubex[10] = 90;cubey[10] = 147;
	cubex[11] = 100;cubey[11] = 53;
	cubex[12] = 100;cubey[12] = 100;
	cubex[13] = 100;cubey[13] = 147;
	cubex[14] = 100;cubey[14] = 194;
	cubex[15] = 127;cubey[15] = 70;
	cubex[16] = 127;cubey[16] = 140;
	cubex[17] = 127;cubey[17] = 210;
	cubex[18] = 135;cubey[18] = 5;
	cubex[19] = 135;cubey[19] = 16;
	cubex[20] = 140;cubey[20] = 57;
	cubex[21] = 140;cubey[21] = 83;
	cubex[22] = 140;cubey[22] = 127;
	cubex[23] = 140;cubey[23] = 154;
	cubex[24] = 140;cubey[24] = 198;
	cubex[25] = 140;cubey[25] = 224;
	cubex[26] = 140;cubey[26] = 276;

	for (i = 27; i<47;++i){
		cubex[i]=280 - cubex[46-i];
		cubey[i]=cubey[46-i];
	}
	towerx[0]=46;towery[0]=140;
	towerx[1]=140;towery[1]=70;
	towerx[2]=140;towery[2]=140;
	towerx[3]=140;towery[3]=210;
	towerx[4]=235;towery[2]=140;
	memset(fieldmap,true,sizeof(fieldmap));
	for (i = 0; i<= 46;++i){
		for (j = -5;j<=5;++j){
			for (k = -5;k<=5;++k){
				fieldmap[cubex[i]+j][cubey[i]+k] = false;
			}
		}
	}
	for (i = 0; i<= 4;++i){
		for (j = -8;j<=8;++j){
			for (k = -8;k<=8;++k){
				fieldmap[towerx[i]+j][towery[i]+k] = false;
			}
		}
	}
}

void deletecube(int cubenum){
	int j,k;
	for (j = -5;j<=5;++j){
		for (k = -5;k<=5;++k){
			fieldmap[cubex[cubenum]+j][cubey[cubenum]+k] = true;
		}
	}
	
}
#endif
