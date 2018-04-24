#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "neuralNetwork.h"
#include "Data.h"

class Controller
{
private :

	void initializeData();
	void initializeNeuralNetwork(std::vector<unsigned int> structure,
	                             std::vector<activationFunction> activationFunction,
	                             float learningRate,
	                             float momentum);

	std::unique_ptr<NeuralNetwork> neuralNetwork;


public:

	Data* data;

	Controller(Data& data);
	~Controller() = default;

	void compute();
};

#endif // CONTROLLER_H
