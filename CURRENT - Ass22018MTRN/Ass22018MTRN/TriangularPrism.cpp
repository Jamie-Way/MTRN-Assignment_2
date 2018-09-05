#ifdef _APPLE_
#include <OpenGl/gl.h>
#elif defined(WIN32)
#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#else
#include <gl/GL.h>
#endif

#include <math.h>
#include "TriangularPrism.h"

TriangularPrism::TriangularPrism()
{

}
TriangularPrism::TriangularPrism(double a, double b, double depth, double angle)
{
	B = b;
	A = a;
	Depth = depth;
	Theta = angle;
}
void TriangularPrism::draw()
{
	glColor3f(red, green, blue);
	glTranslatef(x, y, z);
	glRotatef(rotation, 0, 1, 0);

	//Left Face
	glBegin(GL_QUADS);
	glVertex3f(0.0, 0.0, -Depth / 2.0);
	glVertex3f(B * cos(Theta), B *sin(Theta), -Depth / 2.0);
	glVertex3f(B * cos(Theta), B *sin(Theta), Depth / 2.0);
	glVertex3f(0.0, 0.0, Depth / 2.0);
	glEnd();
	//RightFace
	glBegin(GL_QUADS);
	glVertex3f(A, 0.0, -Depth / 2.0);
	glVertex3f(A, 0.0, Depth / 2.0);
	glVertex3f(B *cos(Theta), B *sin(Theta), -Depth / 2.0);
	glVertex3f(B *cos(Theta), B *sin(Theta), Depth / 2.0);
	glEnd();
	//Bottom Face
	glBegin(GL_QUADS);
	glVertex3f(0.0, 0.0, Depth / 2.0);
	glVertex3f(0.0, 0.0, -Depth / 2.0);
	glVertex3f(A, 0.0, -Depth / 2.0);
	glVertex3f(A, 0.0, Depth / 2.0);
	glEnd();
	//Front Face
	glBegin(GL_QUADS);
	glVertex3f(B * cos(Theta), B * sin(Theta), -Depth / 2.0);
	glVertex3f(0.0, 0.0, -Depth / 2.0);
	glVertex3f(A, 0.0, -Depth / 2.0);
	glVertex3f(A, 0.0, -Depth / 2.0);
	glEnd();
	//Back Face
	glBegin(GL_QUADS);
	glVertex3f(B * cos(Theta), B * sin(Theta), +Depth / 2.0);
	glVertex3f(0.0, 0.0, +Depth / 2.0);
	glVertex3f(A, 0.0, +Depth / 2.0);
	glVertex3f(A, 0.0, +Depth / 2.0);
	glEnd();
	glFlush();
}
TriangularPrism::~TriangularPrism()
{
}