#include "ControllersManager.h"
#include "MNIST.h"
#include "Iris.h"
#include "Wine.h"
#include "CurrencyRatesEurToUsd.h"

ControllersManager::ControllersManager()
{
	controllers.resize(End, nullptr);
}

void ControllersManager::initializeInputsNNs(int index)
{
	switch (index)
	{
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
		controllers[index]->inputs.learningRate = 0.5f;
		controllers[index]->inputs.momentum = 0.0f;
		break;
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

	case indexCurrencyRates:
		controllers[index]->inputs.structure = vector<unsigned int>
		{
			static_cast<unsigned int>(controllers[index]->getData().sizeOfData),
			20,
			static_cast<unsigned int>(controllers[index]->getData().numberOfLabel)
		};
		controllers[index]->inputs.activationFunction = vector<activationFunction>
		{
			sigmoid,
			tanH
		};
		controllers[index]->inputs.learningRate = 0.01f;
		controllers[index]->inputs.momentum = 0.2f;
		break;

	default:
		throw exception();
	}
}

Controller* ControllersManager::getController(int index)
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

		default:
			throw exception("The data doesn't exist !");
		}
		this->initializeInputsNNs(index);
	}
	return controllers[index];
}
