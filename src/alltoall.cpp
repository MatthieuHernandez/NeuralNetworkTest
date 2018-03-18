#include "alltoall.h"
#include <algorithm>

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
    this->outputs.resize(numberOfNeurons, 0);

    for(uint n = 0; n < numberOfNeurons; ++n)
    {
        this->neurons.emplace_back(numberOfInputs, function, learningRate, momentum);
    }
}

vector<float> AllToAll::output(vector<float> &inputs)
{
    for(uint n = 0; n < numberOfNeurons; ++n)
    {
        outputs[n] = neurons[n].output(inputs);
    }
    return outputs;
}

vector<float> AllToAll::backOutput(vector<float> &inputError)
{
    fill(errors.begin(), errors.end(), 0);

    for(uint n = 0; n < numberOfNeurons; ++n)
    {
        transform(inputError.begin(), inputError.end(), errors.begin(), errors.end(), plus<float>());
    }
    return errors;
}
