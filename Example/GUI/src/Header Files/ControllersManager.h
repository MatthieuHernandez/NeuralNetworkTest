#pragma once
#include "Controller.h"

enum indexData
{
	indexIris = 0,
	indexMNIST,
	indexWine,
	indexCurrencyRates,
	End
};

class ControllersManager
{
public:

	ControllersManager();
	virtual ~ControllersManager() = default;

	void initializeInputsNNs(int index);

	Controller* getController(int index);

private:

	std::vector<Controller*> controllers;
};
