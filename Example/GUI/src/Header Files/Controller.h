#pragma once
#include "neural_network/StraightforwardNeuralNetwork.hpp"
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

	struct Inputs
	{
		int NumberOfInputs;
		std::vector<snn::internal::LayerModel> structure;
		bool autoSaveWhenBetter;
        std::string saveFilePath;
		bool useMultithreading;
		bool learningRate;
		bool momentum;
		//int numberOfTrainingsBetweenTwoEvaluations{};
	} inputs;

	Controller(DataSet& data);
	virtual ~Controller() = default;


	void DeleteNeuralNetwork();
	void initializeNeuralNetwork(const QString& dataSetName);

	void save(const QString& fileName);
	void load(const QString& fileName);

	snn::StraightforwardNeuralNetwork& getNeuralNetwork() const;
	DataSet& getData() const;

	void addLayer(int index);
	void removeLayer(int index);


signals :

	void updateNumberOfIteration();
};
