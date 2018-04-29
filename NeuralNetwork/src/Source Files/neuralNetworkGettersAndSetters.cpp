#include "neuralNetwork.h"

//=====================================================================
//  Getters and setters
//=====================================================================

void NeuralNetwork::setLearningRate(const float learningRate)
{
    this->learningRate = learningRate;
}

float NeuralNetwork::getLearningRate() const
{
    return learningRate;
}

void NeuralNetwork::setMomentum(const float value)
{
    if(value >= 0.0f && value <= 1.0f)
    {
        this->momentum = value;
    }
    else
    {
		lastError = 16;
    }
}

float NeuralNetwork::getMomentum() const
{
    return this->momentum;
}

//=====================================================================
//  Only getters
//=====================================================================

int NeuralNetwork::getShortRunCounter() const
{
    return shortRunCounter;
}

int NeuralNetwork::getNumberOfInputs() const
{
    return numberOfInput;
}

int NeuralNetwork::getNumberOfHiddenLayers() const
{
    return numberOfHiddenLayers;
}

int NeuralNetwork::getNumberOfNeuronsInLayer(const int layerNumber) const
{
    return structureOfNetwork[layerNumber+1];
}

activationFunction NeuralNetwork::getActivationFunctionInLayer(int layerNumber) const
{
	return activationFunctionByLayer[layerNumber];
}

int NeuralNetwork::getNumberOfResultsClassifiedWell() const
{
    return numberOfResultsClassifiedWell;
}

int NeuralNetwork::getNumberOfNegativeResultsMisclassefied() const
{
    return numberOfResultsMisclassefied;
}

int NeuralNetwork::getNumberOfOutputs() const
{
    return numberOfOutputs;
}

float NeuralNetwork::getClusteringRate()
{
	const auto clusteringRate = static_cast<float>(numberOfResultsClassifiedWell) / (numberOfResultsClassifiedWell + numberOfResultsMisclassefied);
    numberOfResultsClassifiedWell = 0;
    numberOfResultsMisclassefied = 0;
    return clusteringRate;
}
