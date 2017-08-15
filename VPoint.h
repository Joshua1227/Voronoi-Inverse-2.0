#ifndef VPoint_h
#define VPoint_h
#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif
#include<cmath>
/*
	A structure that stores 2D point for catesian and polar forms
*/

struct polar_point;
struct VPoint
{
	double x, y;
	
	VPoint();

	VPoint(double nx, double ny);
	
	polar_point ConvertToPolar();	// A function to convert cartesian cooredinates to polar cooordinates
};

struct polar_point{  						//  polar coordinates

	double r, theta; 

	VPoint ConvertToCoordinate();	// A function to convert polar coordinates to cartesian coordinates

	void angle_correction();	// A function to correct the angle when it goes above or below 360 degrees
};
#endif
