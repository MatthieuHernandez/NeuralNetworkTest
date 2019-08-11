#pragma once
#include "neuralNetwork/StraightforwardNeuralNetwork.h"
#include "DataSet.h"
#include <QObject>


class Controller : public QObject
{
Q_OBJECT

private :
	std::unique_ptr<DataSet> data = nullptr;
	std::unique_ptr<snn::StraightforwardNeuralNetwork> neuralNetwork = nullptr;

	void initializeData();
	void resetOutput();

public:
	Controller(DataSet& data);
	virtual ~Controller() = default;


	void DeleteNeuralNetwork();
	void initializeNeuralNetwork(const QString& dataSetName);

	void save(const QString& fileName);
	void load(const QString& fileName);

	snn::StraightforwardNeuralNetwork& getNeuralNetwork() const;
	DataSet& getData() const;

	struct Inputs
	{
		std::vector<int> structure;
		std::vector<activationFunctionType> activationFunction;
		float learningRate{};
		float momentum{};
		int numberOfTrainingsBetweenTwoEvaluations{};
	} inputs;

signals :

	void updateNumberOfIteration();
};
