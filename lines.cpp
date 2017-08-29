#include<cmath>
#include"lines.h"
#include<iostream>
#include"VPoint.h"

line::line(){
	std::cout<<"enter the x coordinate of the start point of the line"<<std::endl;
	std::cin>>start.x;
	std::cout<<"enter the y coordinate of the start point of the line"<<std::endl;
	std::cin>>start.y;
	std::cout<<"enter the angle at which the line is inclined"<<std::endl;
	std::cin>>direction;
}

line::line(VPoint begin){
	start = begin;
	std::cout<<"enter the angle at which the line is inclined"<<std::endl;
	std::cin>>direction;
}

line::line(VPoint begin, double angle){
	start = begin;
	direction = angle;
	//std::cout<<"start point of line is ("<<start.x<<", "<<start.y<<")"<<std::endl;
	//std::cout<<"direction of the line is "<<direction<<std::endl;
}

polar_point line::MirrorPoint(polar_point p){
	double angle_diff = p.theta - direction;
	polar_point q;
	q.theta = direction - angle_diff;
	q.r = p.r;
	q.angle_correction();
	return q;
}

VPoint line::MirrorPoint(VPoint p){
	polar_point q = p.ConvertToPolar();
	q = MirrorPoint(q);
	return q.ConvertToCoordinate();
}
double line::angle(){
	return direction;
}
