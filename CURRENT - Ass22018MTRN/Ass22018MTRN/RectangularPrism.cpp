#ifdef _APPLE_
#include <OpenGl/gl.h>
#elif defined(WIN32)
#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#else
#include <gl/GL.h>
#endif

#include "RectangularPrism.hpp"

RectangularPrism::RectangularPrism()
{

}
RectangularPrism::RectangularPrism(double length, double depth, double height)
{
	Height = height;
	Length = length;
	Depth = depth;
}
void RectangularPrism::draw()
{
	glPushMatrix();
	glColor3f(red, green, blue);
	glTranslatef(x, y, z);
	//glTranslatef(0.0, -0.8, 0.0);
	glRotatef(rotation, 0, 1, 0);
	

	//Left Face
	glBegin(GL_QUADS);
	glVertex3f(-Length / 2.0, 0.0, Depth / 2.0);
	glVertex3f(-Length / 2.0, Height, Depth / 2.0);
	glVertex3f(-Length / 2.0, Height, -Depth / 2.0);
	glVertex3f(-Length / 2.0, 0.0, -Depth / 2.0);
	glEnd();
	//RightFace
	glBegin(GL_QUADS);
	glVertex3f(+Length / 2.0, 0.0, Depth / 2.0);
	glVertex3f(+Length / 2.0, Height, Depth / 2.0);
	glVertex3f(+Length / 2.0, Height, -Depth / 2.0);
	glVertex3f(+Length / 2.0, 0.0, -Depth / 2.0);
	glEnd();
	//Top Faces
	glBegin(GL_QUADS);
	glVertex3f(-Length / 2.0, Height, Depth / 2.0);
	glVertex3f(-Length / 2.0, Height, -Depth / 2.0);
	glVertex3f(+Length / 2.0, Height, -Depth / 2.0);
	glVertex3f(+Length / 2.0, Height, Depth / 2.0);
	glEnd();
	//Bottom Face
	glBegin(GL_QUADS);
	glVertex3f(-Length / 2.0, 0.0, Depth / 2.0);
	glVertex3f(-Length / 2.0, 0.0, -Depth / 2.0);
	glVertex3f(+Length / 2.0, 0.0, -Depth / 2.0);
	glVertex3f(+Length / 2.0, 0.0, Depth / 2.0);
	glEnd();
	//Front Face
	glBegin(GL_QUADS);
	glVertex3f(-Length / 2.0, 0.0, -Depth / 2.0);
	glVertex3f(-Length / 2.0, Height, -Depth / 2.0);
	glVertex3f(+Length / 2.0, Height, -Depth / 2.0);
	glVertex3f(+Length / 2.0, 0.0, -Depth / 2.0);
	glEnd();
	//Back Face
	glBegin(GL_QUADS);
	glVertex3f(-Length / 2.0, 0.0, +Depth / 2.0);
	glVertex3f(-Length / 2.0, Height, +Depth / 2.0);
	glVertex3f(+Length / 2.0, Height, +Depth / 2.0);
	glVertex3f(+Length / 2.0, 0.0, +Depth / 2.0);
	glEnd();
	glFlush();
	glPopMatrix();
}
RectangularPrism::~RectangularPrism()
{
}