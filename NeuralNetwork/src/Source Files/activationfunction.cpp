#include "activationfunction.h"

std::vector<ActivationFunction*> ActivationFunction::listOfActivationFunction;

void ActivationFunction::initialize()
{
	listOfActivationFunction.reserve(4);

	listOfActivationFunction.push_back(new Sigmoid());
	listOfActivationFunction.push_back(new TanH());
	listOfActivationFunction.push_back(new ReLU());
	listOfActivationFunction.push_back(new Gaussian());
}