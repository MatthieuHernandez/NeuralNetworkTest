#include "Controller.h"
#include "MNIST.h"
#include <QDateTime>

using namespace std;

Controller::Controller(Data& data)
{
	this->data = unique_ptr<Data>(&data);
	this->initializeData();
	this->inputs.numberOfTrainbyRating = this->data->sets[training].size;
}

void Controller::initializeData()
{
	try
	{
		this->data->loadData();
	}
	catch (exception e)
	{
		auto message = static_cast<string>("Reading data error : ") + e.what();
		exception(message.c_str());
	}
}

void Controller::resetOutput()
{
	outputs.clusteringRate = 0.0f;
	outputs.clusteringRateMax = 0.0f;
	outputs.currentIndex = 0;
	outputs.numberOfIteration = 0;
}

void Controller::DeleteNeuralNetwork()
{
	this->neuralNetwork.reset(nullptr);
	this->resetOutput();
}

void Controller::initializeNeuralNetwork()
{
	this->neuralNetwork = make_unique<NeuralNetwork>(this->inputs.structure,
	                                                 this->inputs.activationFunction,
	                                                 this->inputs.learningRate,
	                                                 this->inputs.momentum);
	this->resetOutput();
}


void Controller::compute(const bool* stop, const bool* autoSave, const QString& autoSaveFileName = nullptr)
{
	for (outputs.numberOfIteration = 0; !(*stop); outputs.numberOfIteration++)
	{
		this->evaluate(stop, *autoSave, autoSaveFileName);
		emit updateNumberOfIteration();
		data->shuffle();

		for (outputs.currentIndex = 0; outputs.currentIndex < this->inputs.numberOfTrainbyRating && !(*stop); outputs.
		     currentIndex++)
		{
			neuralNetwork->train(data->getTrainingData(outputs.currentIndex),
			                     data->getTrainingOutputs(outputs.currentIndex));
		}
	}
}

void Controller::evaluate(const bool* stop, const bool autoSave, const QString& autoSaveFileName)
{
	for (outputs.currentIndex = 0; outputs.currentIndex < data->sets[testing].size; outputs.currentIndex++)
	{
		if (*stop)
			return;
		if (data->problem == classification)
		{
			neuralNetwork->calculateClusteringRateForClassificationProblem(
				data->getTestingData(outputs.currentIndex),
				data->getTestingLabel(outputs.currentIndex));
		}
		else
		{
			neuralNetwork->calculateClusteringRateForRegressionProblemSeparateByValue(
				data->getTestingData(outputs.currentIndex),
				data->getTestingOutputs(outputs.currentIndex), 0.0f);
		}
	}
	outputs.clusteringRate = neuralNetwork->getClusteringRate();
	if (outputs.clusteringRate > outputs.clusteringRateMax)
	{
		outputs.clusteringRateMax = outputs.clusteringRate;
		if(autoSave == true)
			this->autoSave(autoSaveFileName);
	}
}

void Controller::autoSave(const QString& dataSetName)
{
	auto date = QDateTime::currentDateTime().toString("yyyy-MM-dd");
	auto clusteringRate = QString::number(outputs.clusteringRate);
	auto fileName = "./Save/autosave_" + dataSetName + "_" + clusteringRate + "_" + date;
	neuralNetwork->saveAs(fileName.toStdString());
}

void Controller::save(const QString& fileName)
{
	neuralNetwork->saveAs(fileName.toStdString());
}

void Controller::load(const QString& fileName)
{
	neuralNetwork = make_unique<NeuralNetwork>(NeuralNetwork::loadFrom(fileName.toStdString()));
	this->resetOutput();
}

NeuralNetwork& Controller::getNeuralNetwork() const
{
	return *neuralNetwork;
}

Data& Controller::getData() const
{
	return *data;
}
