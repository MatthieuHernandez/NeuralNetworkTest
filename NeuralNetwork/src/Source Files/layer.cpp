#include "layer.h"

using namespace std;

Perceptron* Layer::getNeuron(int neuronNumber)
{
	return &this->neurons[neuronNumber];
}

template<class Archive>
void Layer::serialize(Archive & ar, const unsigned int version)
{
    ar & numberOfInputs ;
	ar & numberOfNeurons;
	//ar & errors;
	//ar & outputs;
	//ar & neurons;
	ar & learningRate;
	ar & momentum;
}

Layer& Layer::equal(const Layer& layer)
{
	this->numberOfInputs = layer.numberOfInputs;
	this->numberOfNeurons = layer.numberOfNeurons;
	this->errors = layer.errors;
	this->outputs = layer.outputs;
	this->neurons = layer.neurons;
	this->learningRate = layer.learningRate;
	this->momentum = layer.momentum;
	return *this;
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
