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
	void autoSave(const QString& dataSetName);


public:

	Controller(DataSet& data);
	virtual ~Controller() = default;


	void DeleteNeuralNetwork();
	void initializeNeuralNetwork();

	//void compute(const bool* stop, const bool* autoSave, const QString& autoSaveFileName);
	//void evaluate(const bool* stop, const bool autoSave = false, const QString& autoSaveFileName = nullptr);
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
