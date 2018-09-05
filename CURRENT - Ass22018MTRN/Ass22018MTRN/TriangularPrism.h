#ifndef TRIANGULARPRISM_H
#define TRIANGULARPRISM_H

#include "Shape.hpp"

class TriangularPrism : public Shape
{
	double A;
	double B;
	double Depth;
	double Theta;

public:
	TriangularPrism();
	~TriangularPrism();
	TriangularPrism(double a, double b, double depth, double angle);
	void draw();
};
#endif
