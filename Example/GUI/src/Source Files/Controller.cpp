#include "Controller.h"
#include <ctime>
#include <windows.h>
#include <algorithm>
#include "MNIST.h"

using namespace std;

Controller::Controller(Data& data)
{
	this->data = &data;
	this->neuralNetwork = nullptr;
	this->initializeData();
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
	for (outputs.numberOfIteration = 0; !(*stop);)
	{
		emit updateNumberOfIteration();
		for (outputs.currentIndex = 0; outputs.currentIndex < 100/*data->sets[testing].size*/ && !(*stop); outputs.currentIndex++)
		{
			neuralNetwork->calculateClusteringRateForClassificationProblem(data->sets[testing].data[outputs.currentIndex],
			                                                               *max_element(data->sets[testing].data[outputs.currentIndex].begin(),
			                                                                            data->sets[testing].data[outputs.currentIndex].end()));
		}

		outputs.numberOfIteration++;

		outputs.clusteringRate = neuralNetwork->getClusteringRate();
		if (outputs.clusteringRate > outputs.clusteringRateMax)
		{
			outputs.clusteringRateMax = outputs.clusteringRate;
		}
		for (outputs.currentIndex = 0; outputs.currentIndex < 100/*this->inputs.numberOfTrainbyRating*/ && !(*stop); outputs.currentIndex++)
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