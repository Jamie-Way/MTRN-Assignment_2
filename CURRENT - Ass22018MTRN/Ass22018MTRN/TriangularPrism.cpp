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

#define Pi 3.14159;

TriangularPrism::TriangularPrism()
{

}
TriangularPrism::TriangularPrism(double a, double b, double depth, double angle)
{
	B = b;
	A = a;
	Depth = depth;
	Theta = angle/180*Pi;


}
void TriangularPrism::draw()
{
	glPushMatrix();
	glColor3f(red, green, blue);
	glTranslatef(x, y, z);
	//glTranslatef(2.5, -0.8, 0.0);
	glRotatef(180, 0, 1, 0);
	glRotatef(rotation, 0, 1, 0);
	

	//Left Face
	glBegin(GL_QUADS);
	glVertex3f(A/2 - B*cos(Theta), B*sin(Theta), -Depth / 2.0);								//point 1
	glVertex3f(A/2, 0, -Depth/2);			//point 3
	glVertex3f(A / 2 - B*cos(Theta), B*sin(Theta), Depth / 2.0);								//point 4
	glVertex3f(A/2.0, 0.0, Depth / 2.0);									//point 6
	glEnd();
	//RightFace
	glBegin(GL_QUADS);
	glVertex3f(-A/2, 0.0, -Depth / 2.0);								//point 5
	glVertex3f(-A/2, 0.0, Depth / 2.0);									//point 6
	glVertex3f(A/2.0 - B * cos(Theta), B*sin(Theta), -Depth / 2.0); //point 3
	glVertex3f(A/2.0 - B * cos(Theta), B*sin(Theta), Depth / 2.0);	//point 4
	glEnd();
	//Bottom Face
	glBegin(GL_QUADS);
	glVertex3f(A / 2.0, 0.0, -Depth / 2.0);								//point 1
	glVertex3f(A / 2.0, 0.0, Depth / 2.0);								//point 2
	glVertex3f(-A / 2, 0.0, -Depth / 2.0);								//point 5
	glVertex3f(-A / 2, 0.0, Depth / 2.0);								//point 6
	glEnd();
	//Front Face
	glBegin(GL_QUADS);
	glVertex3f(A / 2.0, 0.0, -Depth / 2.0);								//point 1
	glVertex3f(A/2.0 - B * cos(Theta),B*sin(Theta), -Depth / 2.0);	//point 3
	glVertex3f(-A / 2, 0.0, -Depth / 2.0);								//point 5
	glVertex3f(-A / 2, 0.0, -Depth / 2.0);								//point 5
	glEnd();
	//Back Face
	glBegin(GL_QUADS);
	glVertex3f(A / 2.0, 0.0, +Depth / 2.0);								//point 1
	glVertex3f(A / 2.0 - B * cos(Theta), B*sin(Theta), +Depth / 2.0);	//point 3
	glVertex3f(-A / 2, 0.0, +Depth / 2.0);								//point 5
	glVertex3f(-A / 2, 0.0, +Depth / 2.0);							//point 6
	glEnd();
	//glFlush();
	glPopMatrix();
}
TriangularPrism::~TriangularPrism()
{

}