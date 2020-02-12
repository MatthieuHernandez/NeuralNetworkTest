#pragma once
#include "neural_network/StraightforwardNeuralNetwork.hpp"
#include "../tests/dataset_tests/Dataset.hpp"
#include <QObject>


class Controller : public QObject
{
Q_OBJECT

private :
	std::unique_ptr<Dataset> data = nullptr;
	std::unique_ptr<snn::StraightforwardNeuralNetwork> neuralNetwork = nullptr;

	void resetOutput();

public:

	struct Inputs
	{
		int NumberOfInputs;
		std::vector<snn::LayerModel> structure;
		bool autoSaveWhenBetter;
        std::string saveFilePath;
		bool useMultithreading;
		float learningRate;
		float momentum;
		//int numberOfTrainingsBetweenTwoEvaluations{};
	} inputs;

	Controller(Dataset& data);
	virtual ~Controller() = default;


	void deleteNeuralNetwork();
	void initializeNeuralNetwork(const QString& dataSetName);

	void save(const QString& fileName);
	void load(const QString& fileName);

	snn::StraightforwardNeuralNetwork& getNeuralNetwork() const;
	Dataset& getDataset() const;

	void addLayer(int index);
	void removeLayer(int index);


signals :

	void updateNumberOfIteration();
};
