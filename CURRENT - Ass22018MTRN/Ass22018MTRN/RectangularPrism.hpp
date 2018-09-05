#ifndef RECTANGULARPRISM_HPP
#define RECTANGULARPRISM_HPP

#include "Shape.hpp"

class RectangularPrism : public Shape
{
	double Height;
	double Length;
	double Depth;

public:
	RectangularPrism();
	~RectangularPrism();
	RectangularPrism(double length, double depth, double height);
	void draw();
};
#endif
