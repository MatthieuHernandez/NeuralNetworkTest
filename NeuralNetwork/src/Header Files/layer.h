#ifndef LAYER_H
#define LAYER_H
#include "perceptron.h"

enum LayerType
{
	allToAll = 0
};

class Layer
{
protected:

	int numberOfInputs = 0;
	int numberOfNeurons = 0;
	std::vector<float> errors;
	std::vector<float> outputs;
	std::vector<Perceptron> neurons;
	float learningRate = 0;
	float momentum = 0;


public:

	virtual ~Layer() = default;

	virtual std::vector<float>& output(const std::vector<float>& inputs) = 0;
	virtual std::vector<float>& backOutput(std::vector<float>& inputsError) = 0;
	virtual void train(std::vector<float>& inputsError) = 0;

	Perceptron* getNeuron(int neuronNumber);
	virtual LayerType getType() const = 0;

	virtual Layer& equal(const Layer& layer) = 0;
	virtual bool operator==(const Layer& layer) const ;
	virtual bool operator!=(const Layer& layer) const ;
};

#endif // LAYER_H
