#include "Controller.h"
#include "MNIST.h"

using namespace std;

Controller::Controller(Data& data)
{
	this->data = unique_ptr<Data>(&data);
	this->initializeData();
	this->inputs.numberOfTrainbyRating = this->data->sets[training].size;
}

void Controller::initializeData()
{
	try
	{
		this->data->loadData();
	}
	catch (exception e)
	{
		auto message = static_cast<string>("Reading data error : ") + e.what();
		exception(message.c_str());
	}
}

void Controller::initializeNeuralNetwork()
{
	this->neuralNetwork = make_unique<NeuralNetwork>(this->inputs.structure,
									                 this->inputs.activationFunction,
									                 this->inputs.learningRate,
									                 this->inputs.momentum);
}

void Controller::compute(bool* stop)
{
	outputs.clusteringRateMax = 0.0f;
	for (outputs.numberOfIteration = 0; !(*stop); outputs.numberOfIteration++)
	{
		for (outputs.currentIndex = 0; outputs.currentIndex < data->sets[testing].size && !(*stop); outputs.currentIndex
		     ++)
		{
			if (data->problem == classification)
			{
				neuralNetwork->calculateClusteringRateForClassificationProblem(
					data->getTestingData(outputs.currentIndex),
					data->getTestingLabel(outputs.currentIndex));
			}
			else
			{
				neuralNetwork->calculateClusteringRateForRegressionProblemSeparateByValue(
					data->getTestingData(outputs.currentIndex),
					data->getTestingOutputs(outputs.currentIndex), 0.0f);
			}
		}
		outputs.clusteringRate = neuralNetwork->getClusteringRate();
		if (outputs.clusteringRate > outputs.clusteringRateMax)
		{
			outputs.clusteringRateMax = outputs.clusteringRate;
		}
		emit updateNumberOfIteration();

		data->shuffle();
		for (outputs.currentIndex = 0; outputs.currentIndex < this->inputs.numberOfTrainbyRating && !(*stop); outputs.
		     currentIndex++)
		{
			neuralNetwork->train(data->getTrainingData(outputs.currentIndex),
			                     data->getTrainingOutputs(outputs.currentIndex));
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