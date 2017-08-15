#include<cmath>
#include"VPoint.h"

class circle{
	private:
	double radius; 						//  radius of the circle
	VPoint center; 						//  center of the circle 
	public:
	circle();
	circle(VPoint p);
	circle(double rad);					//constructors	
	VPoint ClosestPoint(VPoint p);
	polar_point ClosestPoint(polar_point p);	// to replace a point outside a circle to the closest point on the circle
	bool IsPointOnCircle(VPoint &p);
	bool IsPointOnCircle(polar_point &p);		// Both are functions to check whether a given point lies on the circle 
	VPoint MidPointOnCircle(VPoint p, VPoint q);
	VPoint MidPointOnCircle(polar_point p, polar_point q);	// find the midpoint on the circle of two points lying on the same circle
};
