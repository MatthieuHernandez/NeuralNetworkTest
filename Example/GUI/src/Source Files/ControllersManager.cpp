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
			break;
		case indexIris:
			controllers[index] = new Controller(*new Iris());
			break;
		case indexParisTrees:
			controllers[index] = new Controller(*new ParisTrees());
			break;
		}
	}
	return *controllers[index];
}
