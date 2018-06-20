#include "perceptron.h"
#include <iostream>

using namespace std;

Perceptron::Perceptron(const uint numberOfInputs, 
					   ActivationFunction *activationFunction, 
					   const float learningRate, 
					   const float momentum)
{
	this->numberOfInputs = numberOfInputs;
	this->activationFunction = activationFunction;
	this->learningRate = learningRate;
	this->momentum = momentum;

	this->previousDeltaWeights.resize(numberOfInputs, 0);
	this->lastInputs.resize(numberOfInputs, 0);
	this->errors.resize(numberOfInputs, 0);
	lastOutput = 0;

	this->weights.resize(numberOfInputs);
	for(auto &&w : weights)
	{
		w = randomInitializeWeight();
	}
	this->bias = 1.0f;
}

float Perceptron::randomInitializeWeight() const
{
	const float rangeMax = 2.4f / sqrt(this->numberOfInputs);
	return (rand() / static_cast<float>(RAND_MAX) * 2.0f - 1.0f) * rangeMax;
}

float Perceptron::output(const vector<float>& inputs)
{
	lastInputs = inputs;
	float sum = 0;
	for (uint w = 0; w < numberOfInputs; ++w)
	{
		sum += inputs[w] * weights[w];
	}
	sum += bias;
	sum = activationFunction->function(sum);
	lastOutput = sum;
	return sum;
}

std::vector<float>& Perceptron::backOutput(float error)
{
	error = error * activationFunction->derivate(lastOutput);
	this->train(lastInputs, error);

	for (uint w = 0; w < numberOfInputs; ++w)
	{
		errors[w] = error * weights[w];
	}
	return errors;
}

void Perceptron::train(const std::vector<float>& inputs, const float error)
{
	for (uint w = 0; w < numberOfInputs; ++w)
	{
		//if (abs(weights[w]) < abs(100000))
		//{
			auto deltaWeights = learningRate * error * inputs[w];
			deltaWeights += momentum * previousDeltaWeights[w];
			weights[w] += deltaWeights;
			previousDeltaWeights[w] = deltaWeights;
		//}
		//else
		//	throw std::exception();
	}
}

void Perceptron::addAWeight()
{
	numberOfInputs++;
	weights.push_back(randomInitializeWeight());
}

uint Perceptron::isValid()
{
	if (bias != 1 && bias != 0)
	{
		cout << bias << endl;
		return 4;
	}
	if (numberOfInputs < 1 || numberOfInputs != weights.size())
	{
		cout << numberOfInputs << endl;
		cout << weights.size() << endl;
		cout << "" << endl;
		return 6;
	}
	for (uint w = 0; w < numberOfInputs; w++)
	{
		if (weights[w] < -100000 || weights[w] > 10000)
		{
			return 7;
		}
	}

	return 0;
}

vector<float> Perceptron::getWeights() const
{
	return weights;
}

void Perceptron::setWeights(const vector<float>& weights)
{
	this->weights = weights;
}

float Perceptron::getWeight(const uint w) const
{
	return weights[w];
}

void Perceptron::setWeight(const uint w, const float weight)
{
	this->weights[w] = weight;
}

float Perceptron::getBias() const
{
	return bias;
}

void Perceptron::setBias(const float bias)
{
	this->bias = bias;
}

uint Perceptron::getNumberOfInputs() const
{
	return numberOfInputs;
}

bool Perceptron::operator==(const Perceptron& perceptron)
{
	if (this->bias != perceptron.bias
		|| this->numberOfInputs != perceptron.numberOfInputs
		|| this->weights.size() != perceptron.weights.size())
		return false;
	for (uint w = 0; w < numberOfInputs; ++w)
		if (this->weights[w] != perceptron.weights[w])
			return false;
	return true;
}

bool Perceptron::operator!=(const Perceptron& perceptron)
{
	return !this->operator==(perceptron);
}

string Perceptron::display()
{
	string str = "Weight : ";
	for (auto weight : weights)
	{
		str += to_string(weight) + " ";
	}
	str += "Bias : " + to_string(bias);
	return str;
}
