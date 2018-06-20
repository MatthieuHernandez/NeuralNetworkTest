#ifndef ALLTOALL_H
#define ALLTOALL_H

#include "layer.h"
#include "perceptron.h"

class AllToAll : public Layer
{
private :


public :

	AllToAll(uint numberOfInputs, uint numberOfNeurons, ActivationFunction* function, float learningRate, float momentum);
	std::vector<float>& output(const std::vector<float>& inputs) override;
	std::vector<float>& backOutput(std::vector<float>& inputsError) override;
	void train(std::vector<float>& inputsError) override;
};

#endif // ALLTOALL_H