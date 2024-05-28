#ifndef _SVPWM_H_
#define _SVPWM_H_

#define SQRT3 1.73205080f
#define PERIOD 500
#define PI 3.14159265f
typedef struct{
	float d;
	float q;
}RotationAxis;

typedef struct{
	float Alpha;
	float Beta;

}RectangularAxis;

typedef struct{
	float a;
	float b;
	float c;
}TriaxialAxis;
void Svpwm(RotationAxis* Original,float angle);
#endif

