#include "alltoall.h"
#include <algorithm>
#include <functional>

using namespace std;

AllToAll::AllToAll(const uint numberOfInputs,
                   const uint numberOfNeurons,
                   ActivationFunction *function,
                   float learningRate,
                   float momentum)
{
    this->numberOfInputs = numberOfInputs;
    this->numberOfNeurons = numberOfNeurons;
    this->learningRate = learningRate;
    this->momentum = momentum;
    this->neurons.reserve(numberOfNeurons);
	this->outputs.resize(numberOfNeurons);
    this->errors.resize(numberOfInputs);

    for(uint n = 0; n < numberOfNeurons; ++n)
    {
        this->neurons.emplace_back(numberOfInputs, function, learningRate, momentum);
    }
}

vector<float>& AllToAll::output(const vector<float> &inputs)
{
    for(uint n = 0; n < numberOfNeurons; ++n)
    {
        outputs[n] = neurons[n].output(inputs);
    }
    return outputs;
}

vector<float>& AllToAll::backOutput(vector<float> &inputsError)
{
	for (uint n = 0; n < numberOfInputs; ++n)
	{
		errors[n] = 0;
	}

	for (uint n = 0; n < numberOfNeurons; ++n)
	{
		auto result = neurons[n].backOutput(inputsError[n]);
		for (uint r = 0; r < result.size(); ++r)
			errors[r] += result[r];
	}
	if (errors.size() == 10)
		float t = 4;
	return errors;
}

/*vector<float> AllToAll::backOutput(vector<float> &inputsError)
{
	fill(errors.begin(), errors.end(), 0);
	  
	for (uint n = 0; n < numberOfNeurons; ++n)
	{
		auto result = neurons[n].backOutput(inputsError[n]);
		transform(result.begin(), result.end(), errors.begin(), errors.begin(), plus<float>());
	}
	return errors;
}*/

void AllToAll::train(vector<float> &inputsError)
{
	for (uint n = 0; n < numberOfNeurons; ++n)
	{
		neurons[n].backOutput(inputsError[n]);
	}
}