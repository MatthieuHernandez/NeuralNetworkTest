#include "neuralNetwork.h"
#include "Data.h"

class Controller
{
private :

	void InitializeData();
	void initializeNeuralNetwork();

	std::unique_ptr<NeuralNetwork> neuralNetwork;


public:

	Controller();
	~Controller();

	void initialize();
	void compute();
};

