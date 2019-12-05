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

	struct Inputs
	{
		std::vector<int> structure;
		std::vector<snn::activationFunctionType> activationFunctions;
		snn::StraightforwardOption option;
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

	bool getAutoSave() const;
	void setAutoSave(bool value);
	
	bool getMultithreading() const;
	void setMultithreading(bool value);

	float getLearningRate() const;
	void setLearningRate(float value);

	float getMomentum() const;
	void setMomentum(float value);

	float getStructure(int layer) const;
	void setStructure(int layer, float value);

	int getNumberOfLayer() const;

	float getActivationFunctions(int layer);
	void setActivationFunctions(int layer, snn::activationFunctionType value);

	void addLayer(int index);
	void removeLayer(int index);


signals :

	void updateNumberOfIteration();
};
