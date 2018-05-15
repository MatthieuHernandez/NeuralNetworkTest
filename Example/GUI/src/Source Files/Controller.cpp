#include "Controller.h"
#include <ctime>
#include <windows.h>
#include "MNIST.h"

using namespace std;

Controller::Controller(Data& data)
{
	this->data = &data;
	this->neuralNetwork = nullptr;
	this->initializeData();
	this->inputs.numberOfTrainbyRating = this->data->sets[training].size;
}

void Controller::initializeData()
{
	this->data->loadData();
}

void Controller::initializeNeuralNetwork()
{
	this->neuralNetwork = new NeuralNetwork(this->inputs.structure,
	                                        this->inputs.activationFunction,
	                                        this->inputs.learningRate,
	                                        this->inputs.momentum);
}

void Controller::compute(bool* stop)
{
	for (outputs.numberOfIteration = 0; !(*stop); outputs.numberOfIteration++)
	{
		for (outputs.currentIndex = 0; outputs.currentIndex < data->sets[testing].size && !(*stop); outputs.currentIndex++)
		{
			auto label = data->getLabel(outputs.currentIndex, testing);

			neuralNetwork->calculateClusteringRateForClassificationProblem(data->sets[testing].data[outputs.currentIndex], label);
		}
		outputs.clusteringRate = neuralNetwork->getClusteringRate();
		if (outputs.clusteringRate > outputs.clusteringRateMax)
		{
			outputs.clusteringRateMax = outputs.clusteringRate;
		}
		emit updateNumberOfIteration();

		data->shuffle();
		for (outputs.currentIndex = 0; outputs.currentIndex < this->inputs.numberOfTrainbyRating && !(*stop); outputs.currentIndex++)
		{
			neuralNetwork->train(data->sets[training].data[outputs.currentIndex],
			                     data->sets[training].labels[outputs.currentIndex]);
		}
	}
}

NeuralNetwork& Controller::getNeuralNetwork() const
{
	return *neuralNetwork;
}

Data& Controller::getData() const
{
	return *data;
}
