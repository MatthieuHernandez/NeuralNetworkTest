#pragma once
#include "Controller.h"
#include <ui_DataVisualisation.h>

enum indexData
{
	indexIris = 0,
	indexMNIST,
	indexWine,
	indexCurrencyRates,
	End
};

class DataManager
{
public:

	DataManager();
	virtual ~DataManager() = default;

	void initializeInputsNNs(int index);

	Controller* getController(int index);

private:

	std::vector<Controller*> controllers;
	std::vector<Ui::DataVisualisation> visualizations;
};
