#ifdef _APPLE_
#include <OpenGl/gl.h>
#elif defined(WIN32)
#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#else
#include <gl/GL.h>
#endif

#include <vector>
#include "MyVehicle.h"
#include "RectangularPrism.hpp"
#include "TriangularPrism.h"
#include "TrapezodialPrism.h"
#include "Cyclinder.h"


MyVehicle::MyVehicle()
{
	//For Marking
	Shape *mh = NULL;
	mh = new RectangularPrism(8.0, 4.0, 4.0);
	mh->setRotation(0.0);
	mh->setColor(1.0, 0.0, 0.0);
	mh->setPosition(0.0, 0.0, 20.0);
	addShape(mh);

	mh = new TriangularPrism(4.0, 4.0, 4.0, 45);
	mh->setRotation(45.0);
	mh->setColor(0.0, 1.0, 0.0);
	mh->setPosition(-20.0, 0.0, 20.0);
	addShape(mh);

	mh = new TrapezodialPrism(4.0, 2.0, 4.0, 1.0, 4.0);
	mh->setRotation(0.0);
	mh->setColor(0.0, 0.0, 1.0);
	mh->setPosition(-20.0, 0.0, -20.0);
	addShape(mh);

	mh = new Cyclinder(10.0, 10.0);
	mh->setRotation(90.0);
	mh->setColor(1.0, 1.0, 1.0);
	mh->setPosition(20.0, 0.0, -20.0);
	addShape(mh);
	
	
	Shape *sh = NULL;
	sh = new RectangularPrism(8.0, 4.0, 4.0);
	sh->setRotation(0.0);
	sh->setColor(0.0, 1.0, 0.0);
	sh->setPosition(0.0, 0.0, 0.0);
	addShape(sh);

	sh = new TriangularPrism(4.0,4.0,4.0,45);
	sh->setRotation(0.0);
	sh->setColor(1.0, 0.0, 0.0);
	sh->setPosition(2.0, 0.0, 0.0);
	addShape(sh);

	sh = new TrapezodialPrism(4.0, 2.0, 4.0, 1.0, 4.0);
	sh->setRotation(0.0);
	sh->setColor(0.0, 0.0, 1.0);
	sh->setPosition(8.0, 0.0, 0.0);
	addShape(sh);

	//Front Wheels
	sh = new Cyclinder(1.0, 1.0);
	sh->setRotation(0.0);
	sh->setColor(1.0, 1.0, 1.0);
	sh->setPosition(8.0, 0.0, -2.5);
	addShape(sh);

	sh = new Cyclinder(1.0, 1.0);
	sh->setRotation(0.0);
	sh->setColor(1.0, 1.0, 1.0);
	sh->setPosition(8.0, 0.0, 1.5);
	addShape(sh);

	sh = new Cyclinder(1.0, 1.0);
	sh->setRotation(0.0);
	sh->setColor(1.0, 1.0, 1.0);
	sh->setPosition(8.0, 0.0, 1.5);
	addShape(sh);

	//BackWheels
	sh = new Cyclinder(1.0, 1.0);
	sh->setRotation(0.0);
	sh->setColor(.0, 0.0, 1.0);
	sh->setPosition(0.0, 0.0, -2.5);
	addShape(sh);

	sh = new Cyclinder(1.0, 1.0);
	sh->setRotation(0.0);
	sh->setColor(0.0, 0.0, 1.0);
	sh->setPosition(0.0, 0.0, 1.5);
	addShape(sh);
	sh = new Cyclinder(1.0, 1.0);
	sh->setRotation(0.0);
	sh->setColor(0.0, 0.0, 1.0);
	sh->setPosition(-3.0, 0.0, -2.5);
	addShape(sh);

	sh = new Cyclinder(1.0, 1.0);
	sh->setRotation(0.0);
	sh->setColor(0.0, 0.0, 1.0);
	sh->setPosition(-3.0, 0.0, 1.5);
	addShape(sh);
	
	
}

void MyVehicle::draw()
{
	//Cyclinder *psteer;
	Cyclinder *pRotation = NULL;
	for (vector<Shape*>::iterator iter = shapes.begin(); iter != shapes.end(); ++iter)
	{
		glPushMatrix();
		positionInGL();
		// move to the vehicle’s local frame of reference
		Cyclinder *psteer;
		//psteer = dynamic_cast<Cyclinder *>(*iter);
		pRotation = dynamic_cast<Cyclinder *>(*iter);
		if (psteer = dynamic_cast<Cyclinder *>(*iter))
		{
			//If wheel is red and blue they it is a front wheel and steers
			if (psteer->getRed() == 1.0)
			{
				psteer->setRotation(-steering);
			}
			if (psteer->getBlue() == 1.0)
			{
				int time = glutGet(GLUT_ELAPSED_TIME);
				pRotation->getspeed(speed, time);
			}
			
		}

		// all the local drawing code
		(*iter)->draw();
		// move back to global frame of reference
		glPopMatrix();
	}
}

VehicleModel MyVehicle::GetModel()
{
	return model;
}

MyVehicle::~MyVehicle()
{

}