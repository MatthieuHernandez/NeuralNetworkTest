#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "neuralNetwork.h"
#include "Data.h"

class Controller
{
private :

	Data* data;
	NeuralNetwork* neuralNetwork;


public:

	Controller(Data& data);
	~Controller() = default;

	void initializeData();
	void initializeNeuralNetwork(std::vector<unsigned int> structure,
								 std::vector<activationFunction> activationFunction,
								 float learningRate,
								 float momentum);

	void compute();

	NeuralNetwork& getNeuralNetwork() const;
	Data& getData() const;
};

#endif // CONTROLLER_H
