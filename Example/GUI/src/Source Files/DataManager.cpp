#include "DataManager.h"
#include "MNIST.h"
#include "Iris.h"
#include "Wine.h"
#include "CurrencyRatesEurToUsd.h"
#include "MnistVisualizationWidget.h"
#include "CIFAR_10.h"
#include "Cifar10VisualizationWidget.h"

using namespace std;
using namespace snn;

DataManager::DataManager()
{
	controllers.resize(End, nullptr);
	widgets.resize(End, nullptr);
}

void DataManager::initializeInputsNNs(int index)
{
	switch (index)
	{
	case indexIris:
		controllers[index]->inputs.NumberOfInputs = controllers[index]->getData().sizeOfData;
		controllers[index]->inputs.structure = vector<LayerModel>
		{
			AllToAll(13, sigmoid),
			AllToAll(controllers[index]->getData().numberOfLabel, sigmoid)
		};
		controllers[index]->inputs.learningRate = 0.1f;
		controllers[index]->inputs.momentum = 0.0;
		break;

	case indexWine:
		controllers[index]->inputs.NumberOfInputs = controllers[index]->getData().sizeOfData;
		controllers[index]->inputs.structure = vector<LayerModel>
		{
			AllToAll(20, sigmoid),
			AllToAll(8, sigmoid),
			AllToAll(controllers[index]->getData().numberOfLabel, sigmoid)
		};
		controllers[index]->inputs.learningRate = 0.01f;
		controllers[index]->inputs.momentum = 0.0;
		break;

	case indexMNIST:
		controllers[index]->inputs.NumberOfInputs = controllers[index]->getData().sizeOfData;
		controllers[index]->inputs.structure = vector<LayerModel>
		{
			AllToAll(150, sigmoid),
			AllToAll(80, sigmoid),
			AllToAll(controllers[index]->getData().numberOfLabel, sigmoid)
		};
		controllers[index]->inputs.learningRate = 0.1f;
		controllers[index]->inputs.momentum = 0.0;
		break;

	case indexCIFAR_10:
		controllers[index]->inputs.NumberOfInputs = controllers[index]->getData().sizeOfData;
		controllers[index]->inputs.structure = vector<LayerModel>
		{
			AllToAll(150, sigmoid),
			AllToAll(80, sigmoid),
			AllToAll(controllers[index]->getData().numberOfLabel, sigmoid)
		};
		controllers[index]->inputs.learningRate = 0.01f;
		controllers[index]->inputs.momentum = 0.85;
		break;

	case indexCurrencyRates:
		controllers[index]->inputs.NumberOfInputs = controllers[index]->getData().sizeOfData;
		controllers[index]->inputs.structure = vector<LayerModel>
		{
			AllToAll(250, sigmoid),
			AllToAll(60, sigmoid),
			AllToAll(controllers[index]->getData().numberOfLabel, snn::tanh)
		};
		controllers[index]->inputs.learningRate = 0.003f;
		controllers[index]->inputs.momentum = 0.0f;
		break;

	default:
		throw exception();
	}
}

Controller* DataManager::getController(int index)
{
	if (controllers[index] == nullptr)
	{
		switch (index)
		{
		case indexMNIST:
			controllers[index] = new Controller(*new MNIST());
			break;

		case indexIris:
			controllers[index] = new Controller(*new Iris());
			break;

		case indexWine:
			controllers[index] = new Controller(*new Wine());
			break;

		case indexCurrencyRates:
			controllers[index] = new Controller(*new CurrencyRatesEurToUsd());
			break;

		case indexCIFAR_10:
			controllers[index] = new Controller(*new CIFAR_10());
			break;

		default:
			throw exception("The data doesn't exist !");
		}
		this->initializeInputsNNs(index);
	}
	return controllers[index];
}


DataVisualizationWidget* DataManager::getWidget(int index)
{
	if (widgets[index] == nullptr)
	{
		switch (index)
		{
		case indexMNIST:
			widgets[index] = new MnistVisualizationWidget(nullptr, this->getController(index));
			break;

		case indexIris:
			widgets[index] = new DataVisualizationWidget(nullptr, this->getController(index));
			break;

		case indexWine:
			widgets[index] = new DataVisualizationWidget(nullptr, this->getController(index));
			break;

		case indexCurrencyRates:
			widgets[index] = new DataVisualizationWidget(nullptr, this->getController(index));
			break;

		case indexCIFAR_10:
			widgets[index] = new Cifar10VisualizationWidget(nullptr, this->getController(index));
			break;

		default:
			throw exception("The widget doesn't exist !");
		}
	}
	return widgets[index];
}
