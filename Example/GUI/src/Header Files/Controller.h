#pragma once
#include <QObject>
#include "neuralNetwork.h"
#include "Data.h"

using namespace data;

class Controller : public QObject
{
Q_OBJECT

private :

	std::unique_ptr<Data> data = nullptr;
	std::unique_ptr<NeuralNetwork> neuralNetwork = nullptr;

	void initializeData();

public:

	Controller(Data& data);
	virtual ~Controller() = default;

	

	void initializeNeuralNetwork();

	void compute(const bool* stop);
	void evaluate(const bool* stop);
	void save(const QString& fileName);
	void load(const QString& fileName);

	NeuralNetwork& getNeuralNetwork() const;
	Data& getData() const;

	struct Inputs
	{
		std::vector<int> structure;
		std::vector<activationFunctionType> activationFunction;
		float learningRate{};
		float momentum{};
		int numberOfTrainbyRating{};

	} inputs;

	struct Ouputs
	{
		int currentIndex = 0;
		int numberOfIteration = 0;
		float clusteringRate = -1.0f;
		float clusteringRateMax = -1.0f;

	} outputs;

signals :

	void updateNumberOfIteration();
};
