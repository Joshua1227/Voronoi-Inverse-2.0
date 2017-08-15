#include<cmath>
#include<iostream>
#include"VPoint.h"

class line{
	private:
	VPoint start;			//the starting point of the line
	double direction;		//angle of the slope of the line
	public:
	double angle();
	line();
	line(VPoint begin);
	line(double angle);
	line(VPoint begin, double angle);	// constructors
	polar_point MirrorPoint(polar_point p);	
	VPoint MirrorPoint(VPoint p);		// to find the mirror image of a point on a line
};
