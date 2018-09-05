#ifndef TRAPEZODIALPRISM_H
#define TRAPEZODIALPRISM_H

#include "Shape.hpp"

class TrapezodialPrism : public Shape
{
	double A;
	double B;
	double Height;
	double OffCutA;
	double Depth;

public:
	TrapezodialPrism();
	~TrapezodialPrism();
	TrapezodialPrism(double a, double b, double height, double offcuta, double depth);
	void draw();
};
#endif

