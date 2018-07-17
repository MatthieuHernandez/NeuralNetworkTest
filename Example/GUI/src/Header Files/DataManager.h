#pragma once
#include "Controller.h"
#include "DataVisualisationWidget.h"

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
	DataVisualisationWidget* getDataVisualization(int index);

private:

	std::vector<Controller*> controllers;
	std::vector<DataVisualisationWidget*> visualizations;
};
