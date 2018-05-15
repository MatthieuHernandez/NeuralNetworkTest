#include "ControllersManager.h"
#include "MNIST.h"
#include "Iris.h"
#include "ParisTrees.h"

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
		//controllers[index]->inputs.momentum = 0.995;
		break;

	case indexParisTrees:
		controllers[index]->inputs.structure = vector<unsigned int>
		{
			static_cast<unsigned int>(controllers[index]->getData().sizeOfData),
			50,
			static_cast<unsigned int>(controllers[index]->getData().numberOfLabel)
		};
		controllers[index]->inputs.activationFunction = vector<activationFunction>
		{
			sigmoid,
			sigmoid,
		};
		controllers[index]->inputs.learningRate = 0.04f;
		controllers[index]->inputs.momentum = 0.0f;
		break;

	default:
		throw new exception();
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

		case indexParisTrees:
			controllers[index] = new Controller(*new ParisTrees());
			break;

		default:
			throw new exception();
		}
		this->initializeInputsNNs(index);
	}
	return controllers[index];
}
