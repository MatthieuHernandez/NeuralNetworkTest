#include "activationFunction.h"

using namespace std;

vector<ActivationFunction*> ActivationFunction::listOfActivationFunction;

void ActivationFunction::initialize()
{
	listOfActivationFunction.reserve(4);

	listOfActivationFunction.push_back(new Sigmoid());
	listOfActivationFunction.push_back(new ImprovedSigmoid());
	listOfActivationFunction.push_back(new TanH());
	listOfActivationFunction.push_back(new ReLU());
	listOfActivationFunction.push_back(new Gaussian());
}

ActivationFunction* ActivationFunction::getActivationFunction(activationFunctionType type)
{
	switch (type)
	{
		case sigmoid:
			return new Sigmoid();
		case iSigmoid:
			return new ImprovedSigmoid();
		case tanH:
			return new TanH();
		case reLU:
			return new ReLU();
		case gaussian:
			return new Gaussian();
		default:
			throw std::exception();
	}
}
