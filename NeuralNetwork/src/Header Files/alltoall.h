#ifndef ALLTOALL_H
#define ALLTOALL_H

#include "layer.h"
#include "perceptron.h"

class AllToAll : public Layer
{
private :


public :

	AllToAll(int numberOfInputs, int numberOfNeurons, activationFunctionType function, float learningRate, float momentum);
	std::vector<float>& output(const std::vector<float>& inputs) override;
	std::vector<float>& backOutput(std::vector<float>& inputsError) override;
	void train(std::vector<float>& inputsError) override;
};

#endif // ALLTOALL_H