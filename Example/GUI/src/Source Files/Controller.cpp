#include "Controller.h"
#include "MNIST.h"
#include <QDateTime>
using namespace std;
using namespace snn;

Controller::Controller(Data& data)
{
	this->data = unique_ptr<DataSet>(&data);
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
	this->neuralNetwork->trainingStop();
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


/*void Controller::compute(const bool* stop, const bool* autoSave, const QString& autoSaveFileName = nullptr)
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
}*/

/*void Controller::evaluate(const bool* stop, const bool autoSave, const QString& autoSaveFileName)
{
	neuralNetwork->startTesting();
	for (outputs.currentIndex = 0; outputs.currentIndex < data->sets[testing].size; outputs.currentIndex++)
	{
		if (*stop)
			return;
		if (data->problem == classification)
		{
			neuralNetwork->evaluateForClassificationProblem(
				data->getTestingData(outputs.currentIndex),
				data->getTestingLabel(outputs.currentIndex));
		}
		else
		{
			neuralNetwork->evaluateForRegressionProblemSeparateByValue(
				data->getTestingData(outputs.currentIndex),
				data->getTestingOutputs(outputs.currentIndex), 0.0f);
		}
	}
	outputs.clusteringRate = neuralNetwork->getGlobalClusteringRate();
	outputs.weightedClusteringRate = neuralNetwork->getWeightedClusteringRate();
	outputs.f1Score = neuralNetwork->getF1Score();
	if (neuralNetwork->getGlobalClusteringRate() > outputs.clusteringRateMax)
	{
		outputs.clusteringRateMax = neuralNetwork->getGlobalClusteringRate();
		if (autoSave)
			this->autoSave(autoSaveFileName);
	}
}*/

void Controller::autoSave(const QString& dataSetName)
{
	auto date = QDateTime::currentDateTime().toString("yyyy-MM-dd");
	auto clusteringRate = QString::number(neuralNetwork->getGlobalClusteringRate());
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

StraightforwardNeuralNetwork& Controller::getNeuralNetwork() const
{
	return *neuralNetwork;
}

Data& Controller::getData() const
{
	return *data;
}
