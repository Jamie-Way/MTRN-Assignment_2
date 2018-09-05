/*
#pragma once
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
#include "Disk.h"

using namespace std;

Disk::Disk()
{

}

Disk::Disk(double radiush)
{
	Radius = radius;

}
void Disk::Disk()
{
	glColor3f(red, green, blue);
	glTranslatef(x, y, z);
	glRotatef(rotation, 0.0, 1.0, 0.0);


	gluDisk(pCyclinder, 0, Radius, 20, 1);

}
*/