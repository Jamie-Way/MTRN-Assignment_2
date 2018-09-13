#ifndef CYCLINDER_H
#define CYCLINDER_H

#include "Shape.hpp"

class Cyclinder : public Shape
{
	double Radius;
	double Depth;
	double Speed;
	double Steer;
	double dt;

public:
	Cyclinder();
	~Cyclinder();
	Cyclinder(double radius, double depth);
	void draw();
	void getspeed(double RotRate, int time);
	double GetSpeed2();
	double GetRadius();
};
#endif

