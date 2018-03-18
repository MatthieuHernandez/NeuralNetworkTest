#ifndef LAYER_H
#define LAYER_H

#include "perceptron.h"

class Layer
{
protected:

	uint numberOfInputs = 0;
	uint numberOfNeurons = 0;
	std::vector<float> errors;
	std::vector<float> outputs;
	std::vector<Perceptron> neurons;
	float learningRate = 0;
	float momentum = 0;


public:

	~Layer() = default;
	std::vector<float> output(std::vector<float>& inputs);
	std::vector<float> backOutput(std::vector<float>& inputs);

	bool operator==(const Layer& layer);
	bool operator!=(const Layer& layer);
};

#endif // LAYER_H
