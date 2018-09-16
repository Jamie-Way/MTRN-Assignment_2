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


using namespace std;

VehicleModel MyVehicle::GetModel()
{
	return model;
}

MyVehicle::MyVehicle(VehicleModel Mode)
{
	model = Mode;	
}

void MyVehicle::draw()
{
	Shape *vm = NULL;
	shapes.clear();
	int rolling = 0;

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
				rolling = 1;
			}
			else
			{
				rolling = 0;
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
	
	for (vector<Shape*>::iterator iter = shapes.begin(); iter != shapes.end(); ++iter)
	{
		glPushMatrix();
		positionInGL();

		Cyclinder *psteer;
		Cyclinder *pRotation;
		pRotation = dynamic_cast<Cyclinder *>(*iter);
		if (psteer = dynamic_cast<Cyclinder *>(*iter))
		{
			
			if (rolling == 1.0)
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

MyVehicle::~MyVehicle()
{

}