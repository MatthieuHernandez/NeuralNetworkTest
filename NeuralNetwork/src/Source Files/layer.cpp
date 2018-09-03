#include "layer.h"

using namespace std;

void Layer::operator=(const Layer& layer)
{
	this->numberOfInputs = layer.numberOfInputs;
	this->numberOfNeurons = layer.numberOfNeurons;
	this->errors = layer.errors;
	this->outputs = layer.outputs;
	this->neurons = layer.neurons;
	this->learningRate = layer.learningRate;
	this->momentum = layer.momentum;
}

bool Layer::operator==(const Layer& layer) const
{
	return this->numberOfInputs == layer.numberOfInputs
		&& this->numberOfNeurons == layer.numberOfNeurons
		&& this->errors == layer.errors
		&& this->outputs == layer.outputs
		&& this->neurons == layer.neurons
		&& this->learningRate == layer.learningRate
		&& this->momentum == layer.momentum;
}

bool Layer::operator!=(const Layer& layer) const
{
	return !this->operator==(layer);
}
