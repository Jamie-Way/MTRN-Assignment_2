#ifdef _APPLE_
#include <OpenGl/gl.h>
#elif defined(WIN32)
#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#else
#include <gl/GL.h>
#endif

#include "TrapezodialPrism.h"

TrapezodialPrism::TrapezodialPrism()
{

}
TrapezodialPrism::TrapezodialPrism(double a, double b, double height, double offcuta, double depth)
{
	A = a;
	B = b;
	Height = height;
	OffCutA = offcuta;
	Depth = depth;
}
void TrapezodialPrism::draw()
{
	glColor3f(red, green, blue);
	glTranslatef(x, y, z);
	glRotatef(rotation, 0, 1, 0);

	//Left Face
	glBegin(GL_QUADS);
	glVertex3f(-A / 2.0, 0.0, -Depth / 2.0);						//point1
	glVertex3f(-A / 2.0, 0.0, Depth / 2.0);							//point2
	glVertex3f((-A / 2.0) + OffCutA, Height, Depth / 2.0);			//point3
	glVertex3f((-A / 2.0) + OffCutA, Height, -Depth / 2.0);			//point4
	glEnd();
	//RightFace
	glBegin(GL_QUADS);
	glVertex3f(+A / 2.0, 0.0, -Depth / 2.0);						//point5
	glVertex3f(+A / 2.0, 0.0, Depth / 2.0);							//point6
	glVertex3f((A / 2.0 - (A - OffCutA - B)), Height, Depth / 2.0);	//point7
	glVertex3f((A / 2.0 - (A - OffCutA - B)), Height, -Depth / 2.0);	//point8
	glEnd();
	//Top Face
	glBegin(GL_QUADS);
	glVertex3f((A / 2.0 - (A - OffCutA - B)), Height, -Depth / 2.0);	//point8
	glVertex3f((-A / 2.0) + OffCutA, Height, -Depth / 2.0);			//point4
	glVertex3f((-A / 2.0) + OffCutA, Height, Depth / 2.0);			//point3
	glVertex3f((A / 2.0 - (A - OffCutA - B)), Height, Depth / 2.0);	//point7
	glEnd();
	//Bottom Face
	glBegin(GL_QUADS);
	glVertex3f(-A / 2.0, 0.0, -Depth / 2.0);						//point1
	glVertex3f(-A / 2.0, 0.0, Depth / 2.0);							//point2
	glVertex3f(+A / 2.0, 0.0, -Depth / 2.0);						//point5
	glVertex3f(+A / 2.0, 0.0, Depth / 2.0);							//point6
	glEnd();
	//Front Face
	glBegin(GL_QUADS);
	glVertex3f(-A / 2.0, 0.0, -Depth / 2.0);						//point1
	glVertex3f(+A / 2.0, 0.0, -Depth / 2.0);						//point5
	glVertex3f((A / 2.0 - (A - OffCutA - B)), Height, -Depth / 2.0);//point8
	glVertex3f((-A / 2.0) + OffCutA, Height, -Depth / 2.0);			//point4
	glEnd();
	//Back Face
	glBegin(GL_QUADS);
	glVertex3f(-A / 2.0, 0.0, Depth / 2.0);							//point2
	glVertex3f(+A / 2.0, 0.0, Depth / 2.0);							//point6
	glVertex3f((A / 2.0 - (A - OffCutA - B)), Height, Depth / 2.0);	//point7
	glVertex3f((-A / 2.0) + OffCutA, Height, Depth / 2.0);			//point3
	glEnd();
	glFlush();
}
TrapezodialPrism::~TrapezodialPrism()
{
}