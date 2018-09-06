#ifndef ALLTOALL_H
#define ALLTOALL_H

#include "layer.h"
#include "perceptron.h"

class AllToAll : public Layer
{
public :

	AllToAll();
	AllToAll(int numberOfInputs, int numberOfNeurons, activationFunctionType function, float learningRate,
	         float momentum);
	std::vector<float>& output(const std::vector<float>& inputs) override;
	std::vector<float>& backOutput(std::vector<float>& inputsError) override;
	void train(std::vector<float>& inputsError) override;

	LayerType getType() const override;

	Layer& equal(const Layer& layer) override;
	bool operator==(const AllToAll& layer) const;
	bool operator!=(const AllToAll& layer) const;
};

#endif // ALLTOALL_H
