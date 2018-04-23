#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <list>
#include "neuralNetwork.h"
#include "Data.h"

class Controller
{
private :

	void initializeData(Data& data);
	void initializeNeuralNetwork(std::vector<unsigned int> structure,
	                             std::vector<activationFunction> activationFunction,
	                             float learningRate,
	                             float momentum);

	std::unique_ptr<NeuralNetwork> neuralNetwork;
	Data* data;


public:

	Controller();
	~Controller();

	void compute();
};

#endif // CONTROLLER_H
