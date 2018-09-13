#ifdef _APPLE_
#include <OpenGl/gl.h>
#elif defined(WIN32)
#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <Windows.h>
#else
#include <gl/GL.h>
#endif

#include <vector>
#include "MyVehicle.h"
#include "RectangularPrism.hpp"
#include "TriangularPrism.h"
#include "TrapezodialPrism.h"
#include "Cyclinder.h"
#include "Shape.hpp"
#include "Messages.hpp"


#define PI 3.14159;


using namespace std;

VehicleModel MyVehicle::GetModel()
{
	return model;
}

MyVehicle::MyVehicle(VehicleModel Mode)
{
	model = Mode;
	/*
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
	*/
}

void MyVehicle::draw()
{
	Shape *vm = NULL;
	shapes.clear();
	//<pRotation> = dynamic_cast<Cyclinder *>(*iter);

	for (vector<ShapeInit>::iterator iter = model.shapes.begin(); iter != model.shapes.end(); ++iter)
	{
		switch (iter->type) {

		case CYLINDER:
			vm = new Cyclinder(iter->params.cyl.radius, iter->params.cyl.depth);

			if (iter->params.cyl.isSteering == true)
			{
				vm->setRotation(-steering);
			}
			else
			{
				vm->setRotation(iter->rotation);
			}

			if (iter->params.cyl.isRolling == true)
			{
				/*int time = glutGet(GLUT_ELAPSED_TIME);
				iter->Cyclinder::getspeed(speed,time);
				vm->setRotation(speed);
				positionInGL();
				glRotatef(speed, 0.0, 0.0, -1.0);
				pRotation->getspeed(speed, time);
				vm->glRotatef(speed, 0.0, 0.0, -1.0);*/


				//gl.Translate(0.0,speed,0.0);
			}
			break;

		case RECTANGULAR_PRISM:
			vm = new RectangularPrism(iter->params.rect.xlen, iter->params.rect.zlen, iter->params.rect.ylen);
			vm->setRotation(iter->rotation);
			break;

		case TRIANGULAR_PRISM:
			vm = new TriangularPrism(iter->params.tri.alen, iter->params.tri.blen, iter->params.tri.depth, iter->params.tri.angle);
			vm->setRotation(iter->rotation);
			break;
			
		case TRAPEZOIDAL_PRISM:
			vm = new TrapezodialPrism(iter->params.trap.alen, iter->params.trap.blen, iter->params.trap.height, iter->params.trap.aoff, iter->params.trap.depth);
			vm->setRotation(iter->rotation);
			break;

		
		}
		vm->setColor(iter->rgb[0], iter->rgb[1], iter->rgb[2]);
		vm->setPosition(iter->xyz[0], iter->xyz[1], iter->xyz[2]);
		addShape(vm);
		
	}
	
	int prevtime = 0;												//Is this the wrong place for this?

	for (vector<Shape*>::iterator iter = shapes.begin(); iter != shapes.end(); ++iter)
	{
		glPushMatrix();
		positionInGL();
		//glTranslated(x, y, z); 
		//glRotated(-rotation, 0, 1, -0);
		
		Cyclinder *Cyl = dynamic_cast<Cyclinder*> (*iter);
			

		if (Cyl != NULL)
		{
			int dt = 0;
			int time = glutGet(GLUT_ELAPSED_TIME);					//Finds the current time since program started (in ms)
			dt = time - prevtime;									//Time elapsed since last call

			double speed = Cyl->GetSpeed2();						//Speed of vehicle in meters per second
			double radius = Cyl->GetRadius();						//Radius of the wheel

			double circ = 2 * radius * PI;							//Circumference of the wheel in meters (PI defined at top of page)
			double RevSpeed = speed / circ;							//Calculates the number of revolutions of wheel per second
			double RotationDeg = RevSpeed * 360;					//Amount of degrees that wheel must rotate in one second

			if(dt == 1000) {										//Called every 1000ms
				Cyl->getspeed(RotationDeg, time);					//Rotate wheel by this amount (might happen too quickly though)
				dt = 0;												//Resets dt
			}
				
			prevtime = time;										//Updates the previous time counter
			//Cyl->getspeed(speed, time);
			//glRotatef(speed*time, 0.0, 0.0, -1.0);
		}



		(*iter)->draw();
		glPopMatrix();
		
	}
}

/*
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
*/

MyVehicle::~MyVehicle()
{

}