#include "NeuralNetwork.h"

//=====================================================================
//  Getters and setters
//=====================================================================

void NeuralNetwork::setLearningRate(float learningRate)
{
    this->learningRate = learningRate;
}
float NeuralNetwork::getLearningRate() const
{
    return learningRate;
}

void NeuralNetwork::setMomentum(float value)
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

void NeuralNetwork::setLenghtOfShortRuns(uint lenght)
{
    this->lenghtOfShortRuns = lenght;
}

uint NeuralNetwork::getLenghtOfShortRuns() const
{
    return lenghtOfShortRuns;
}

//=====================================================================
//  Only getters
//=====================================================================

uint NeuralNetwork::getShortRunCounter() const
{
    return shortRunCounter;
}

uint NeuralNetwork::getNumberOfInputs() const
{
    return numberOfInput;
}

uint NeuralNetwork::getNumberOfHiddenLayers() const
{
    return numberOfHiddenLayers;
}

uint NeuralNetwork::getNumberOfNeuronsInHiddenLayers(int layerNumber) const
{
    return structureOfNetwork[layerNumber+1];
}

uint NeuralNetwork::getNumberOfResultsClassifiedWell() const
{
    return numberOfResultsClassifiedWell;
}

uint NeuralNetwork::getNumberOfNegativeResultsMisclassefied() const
{
    return numberOfResultsMisclassefied;
}

uint NeuralNetwork::getNumberOfOutputs() const
{
    return numberOfOutput;
}

float NeuralNetwork::getClusteringRate()
{
    float clusteringRate = (float)(numberOfResultsClassifiedWell) / (numberOfResultsClassifiedWell + numberOfResultsMisclassefied);
    numberOfResultsClassifiedWell = 0;
    numberOfResultsMisclassefied = 0;
    return clusteringRate;
}
