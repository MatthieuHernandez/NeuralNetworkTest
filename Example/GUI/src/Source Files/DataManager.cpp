#include "DataManager.h"
#include "MNIST.h"
#include "Iris.h"
#include "Wine.h"
#include "CurrencyRatesEurToUsd.h"
#include "MnistVisualizationWidget.h"
#include "CIFAR_10.h"
#include "Cifar10VisualizationWidget.h"

using namespace std;

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
		controllers[index]->inputs.structure = vector<unsigned int>
		{
			static_cast<unsigned int>(controllers[index]->getData().sizeOfData),
			13,
			static_cast<unsigned int>(controllers[index]->getData().numberOfLabel)
		};
		controllers[index]->inputs.activationFunction = vector<activationFunction>
		{
			sigmoid,
			sigmoid
		};
		controllers[index]->inputs.learningRate = 0.5f;
		controllers[index]->inputs.momentum = 0.0;
		break;

	case indexWine:
		controllers[index]->inputs.structure = vector<unsigned int>
		{
			static_cast<unsigned int>(controllers[index]->getData().sizeOfData),
			20,
			8,
			static_cast<unsigned int>(controllers[index]->getData().numberOfLabel)
		};
		controllers[index]->inputs.activationFunction = vector<activationFunction>
		{
			sigmoid,
			sigmoid,
			sigmoid,
		};
		controllers[index]->inputs.learningRate = 0.01f;
		controllers[index]->inputs.momentum = 0.0f;
		break;

	case indexMNIST:
		controllers[index]->inputs.structure = vector<unsigned int>
		{
			static_cast<unsigned int>(controllers[index]->getData().sizeOfData),
			150,
			80,
			static_cast<unsigned int>(controllers[index]->getData().numberOfLabel)
		};
		controllers[index]->inputs.activationFunction = vector<activationFunction>
		{
			sigmoid,
			sigmoid,
			sigmoid
		};
		controllers[index]->inputs.learningRate = 0.1f;
		controllers[index]->inputs.momentum = 0.0f;
		break;

	case indexCIFAR_10:
		controllers[index]->inputs.structure = vector<unsigned int>
		{
			static_cast<unsigned int>(controllers[index]->getData().sizeOfData),
			150,
			80,
			static_cast<unsigned int>(controllers[index]->getData().numberOfLabel)
		};
		controllers[index]->inputs.activationFunction = vector<activationFunction>
		{
			sigmoid,
			sigmoid,
			sigmoid
		};
		controllers[index]->inputs.learningRate = 0.01f;
		controllers[index]->inputs.momentum = 0.85f;
		break;

	case indexCurrencyRates:
		controllers[index]->inputs.structure = vector<unsigned int>
		{
			static_cast<unsigned int>(controllers[index]->getData().sizeOfData),
			250,
			60,
			static_cast<unsigned int>(controllers[index]->getData().numberOfLabel)
		};
		controllers[index]->inputs.activationFunction = vector<activationFunction>
		{
			sigmoid,
			sigmoid,
			tanH
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
