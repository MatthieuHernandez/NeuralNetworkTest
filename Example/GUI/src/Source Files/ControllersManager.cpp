#include "ControllersManager.h"
#include "MNIST.h"
#include "Iris.h"
#include "ParisTrees.h"


ControllersManager::ControllersManager()
{
	controllers.resize(End, nullptr);
}

Controller& ControllersManager::getController(int index)
{
	if (controllers[index] == nullptr)
	{
		switch (index)
		{
		case indexMNIST:
			controllers[index] = new Controller(*new MNIST());
			controllers[index]->initializeNeuralNetwork(vector<unsigned int>
			                                            {
				                                            static_cast<unsigned int>(controllers[index]->getData().sizeOfData),
				                                            150,
				                                            80,
				                                            static_cast<unsigned int>(controllers[index]->getData().numberOfLabel)
			                                            },
			                                            vector<activationFunction>
			                                            {
				                                            sigmoid,
				                                            sigmoid,
				                                            sigmoid
			                                            },
			                                            0.05f,
			                                            0.0f);
			break;
		case indexIris:
			controllers[index] = new Controller(*new Iris());
			controllers[index]->initializeNeuralNetwork(vector<unsigned int>
			                                            {
				                                            static_cast<unsigned int>(controllers[index]->getData().sizeOfData),
				                                            20,
				                                            10,
				                                            static_cast<unsigned int>(controllers[index]->getData().numberOfLabel)
			                                            },
			                                            vector<activationFunction>
			                                            {
				                                            sigmoid,
				                                            sigmoid,
				                                            sigmoid
			                                            },
			                                            0.05f,
			                                            0.0f);
			break;
		case indexParisTrees:
			controllers[index] = new Controller(*new ParisTrees());
			controllers[index]->initializeNeuralNetwork(vector<unsigned int>
			                                            {
				                                            static_cast<unsigned int>(controllers[index]->getData().sizeOfData),
				                                            50,
				                                            static_cast<unsigned int>(controllers[index]->getData().numberOfLabel)
			                                            },
			                                            vector<activationFunction>
			                                            {
				                                            sigmoid,
				                                            sigmoid,
			                                            },
			                                            0.05f,
			                                            0.0f);
			break;
		default:
			throw new exception();
		}
	}
	return *controllers[index];
}
