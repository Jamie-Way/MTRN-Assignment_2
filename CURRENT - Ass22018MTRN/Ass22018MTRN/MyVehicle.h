#ifndef MYVEHICLE_H
#define MYVEHICLE_H

#include "Vehicle.hpp"
#include "Messages.hpp"
#include <vector>

using namespace std;

class MyVehicle : public Vehicle
{
	VehicleModel model;

public:
	MyVehicle(VehicleModel Mode);
	~MyVehicle();
	VehicleModel GetModel();
	void draw();
};
#endif
