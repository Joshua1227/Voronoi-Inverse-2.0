#include"VPoint.h"
double DegreesToRadian(double deg){
	return deg*M_PI/180;
}

VPoint::VPoint(){
	x = 0.0;
	y = 0.0;
}

VPoint::VPoint(double nx, double ny){
	x = nx; 
	y = ny;
}

VPoint polar_point::ConvertToCoordinate(){		// A function to convert polar coordinates to cartesian coordinates
	VPoint q;
	q.x = r*cos(DegreesToRadian(theta));
	q.y = r*sin(DegreesToRadian(theta));
	return q;
}

polar_point VPoint::ConvertToPolar(){	// A function to convert cartesian cooredinates to polar cooordinates
	polar_point q;
	q.r = sqrt(pow(x, 2.0) + pow(y, 2.0));
	q.theta = atan2(y, x) * 180/M_PI;
	return q;
}

void polar_point::angle_correction(){
	while(theta >= 360)
		theta = theta - 360;
	while (theta < 0)
		theta = theta + 360;
}
