#ifdef _APPLE_
#include <OpenGl/gl.h>
#elif defined(WIN32)
#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#else
#include <gl/GL.h>
#endif

#include <iostream>
#include <math.h>
#include "Cyclinder.h"

#include "KeyManager.hpp"
#include "Vehicle.hpp"
#include "Messages.hpp"

using namespace std;

Cyclinder::Cyclinder()
{

}

Cyclinder::Cyclinder(double radius, double depth)
{
	Radius = radius;
	Depth = depth;
	Speed = NULL;
	Steer = NULL;
	dt = 1.0;	

}
void Cyclinder::draw()
{
	glPushMatrix();
	glColor3f(red, green, blue);
	glTranslatef(x, y, z);
	glTranslatef(0.0, Radius, -Depth/2);

	glRotatef(rotation, 0.0, 1.0, 0.0);

	if (Speed != NULL)
	{
		glRotatef(Speed, 0.0, 0.0, -1.0);
	}
	if (Steer != NULL)
	{
		glRotatef(rotation, 0.0, 1.0, 0.0);
		//setRotation(-steering);
	}

	GLUquadric* pCyclinder;
	pCyclinder = gluNewQuadric();

	//Spokes
	glBegin(GL_QUADS);
	//Sets position
	glVertex3f(0.0, Radius, 0.0);
	glVertex3f(0.0, Radius,0.0);
	//Defines triangles
	glVertex3f(-Radius * cos(45), -Radius * sin(45), 0.0);
	glVertex3f(Radius * cos(45), Radius * sin(45), 0.0);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0.0, Radius, Depth);			
	glVertex3f(0.0, Radius, Depth);
	glVertex3f(-Radius * cos(45), -Radius * sin(45), Depth);
	glVertex3f(Radius * cos(45), Radius * sin(45), Depth);
	glEnd();

	//Barrel of wheels
	gluQuadricNormals(pCyclinder, GLU_SMOOTH);
	gluCylinder(pCyclinder, Radius, Radius, Depth, 20, 1);
	//gluDisk(pCyclinder, 0, Radius, 20, 1);
	glFlush();
	glPopMatrix();

}

void Cyclinder::getspeed(double RotRate,int time) 
{
	double prevtime = time - dt;
	dt = time - prevtime;
	Speed = Speed + ((RotRate*dt)/Radius);
	while (Speed > 360) Speed -= 360;
	while (Speed < 0) Speed += 360;
	cout << Speed << endl;
}
Cyclinder::~Cyclinder()
{
}