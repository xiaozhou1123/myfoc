#include "svpwm.h"
#include "math.h"
#include <stdio.h>
#include "config.h"
void InvPark(RotationAxis* Original,RectangularAxis* Result,float angle){
	float Rad = fmodf(angle,360.0)/180.0f * PI;
	
	Result->Alpha = Original->d * cos(Rad) - Original->q * sin(Rad);
	Result->Beta  = Original->d * sin(Rad) + Original->q * cos(Rad);
}

void InvClark(RectangularAxis* Original,TriaxialAxis* Result){
	
	Result->a = Original->Alpha;
	Result->b = ((-1.0f/2.0f)*Original->Alpha) + (SQRT3/2.0f)*Original->Beta;
	Result->c = ((-1.0f/2.0f)*Original->Alpha) - (SQRT3/2.0f)*Original->Beta;
}

static void _svpwm(RectangularAxis* Original){
	
float  K = SQRT3 * PERIOD / CONFIG_DC_VOLTAGE;
	float U1 =   Original->Beta;
	float U2 = (SQRT3/2.0f) * Original->Alpha - Original->Beta/2.0f; // -Z
	float U3 = -(SQRT3/2.0f) * Original->Alpha - Original->Beta/2.0f; //-Y

	
	int Sector = (U1>0?1:0)+2*(U2>0?1:0)+4*(U3>0?1:0);
	float Time_a,Time_b,Time_c;
	float t1,t2;//
	float t0;//
	
	
	switch(Sector){
		case 1:
			t1 = -K * U2;
			t2 = -K * U3;
			t0 = (PERIOD - t1 -t2)/2.0f;
			Time_a = t0+t1;
			Time_b = t0;
			Time_c = t0+t1+t2;
			break;
		case 2:
			t1 = -K * U3;
			t2 = -K * U1;
			t0 = (PERIOD - t1 -t2)/2.0f;
			Time_a = t0;
			Time_b = t0+t1+t2;
			Time_c = t0+t1;
			break;
		case 3:
			t1 = K * U2;
			t2 = K * U1;
			t0 = (PERIOD - t1 -t2)/2.0f;
			Time_a = t0;
			Time_b = t1+t0;
			Time_c = t2+t1+t0;
			break;
		case 4:
			t1 = -K * U1;
			t2 = -K * U2;
			t0 = (PERIOD - t1 -t2)/2.0f;
			Time_a = t1+t2+t0;
			Time_b = t1+t0;
			Time_c = t0;
			break;
		case 5:
			t1 = K * U1;
			t2 = K * U3;
			t0 = (PERIOD - t1 -t2)/2.0f;
			Time_a = t0+t1+t2;
			Time_b = t0;
			Time_c = t1+t0;
			break;
		case 6:
			t1 = K * U3;
			t2 = K * U2;
			t0 = (PERIOD - t1 -t2)/2.0f;
			Time_a = t1+t0;
			Time_b = t1+t2+t0;
			Time_c = t0;
			break;
		default:
			Time_a = 0;
			Time_b = 0;
			Time_c = 0;
	}
	//printf("%d\n",Sector);
	printf("%f ",Time_a/2.0f);
	printf("%f ",Time_b/2.0f);
	printf("%f\n",Time_c/2.0f);
}

RectangularAxis _temp;

void Svpwm(RotationAxis* Original,float angle){
	InvPark(Original,&_temp,angle);
	_svpwm(&_temp);
}
