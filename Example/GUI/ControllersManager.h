#pragma once
#include "Controller.h"

enum indexData
{
	indexMNIST = 0,
	indexIris,
	indexParisTrees,
	End
};

class ControllersManager
{
public:

	ControllersManager();

	Controller& getController(int index);


private:

	std::vector<Controller*> controllers;
};

