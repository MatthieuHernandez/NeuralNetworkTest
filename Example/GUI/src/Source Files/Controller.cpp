#include "Controller.h"
#include "MNIST.h"
#include <QDateTime>
using namespace std;
using namespace snn;

Controller::Controller(DataSet& data)
{
	this->data = unique_ptr<DataSet>(&data);
	this->initializeData();
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
	this->neuralNetwork = make_unique<StraightforwardNeuralNetwork>(this->inputs.structure,
	                                                                this->inputs.activationFunction,
	                                                                this->inputs.learningRate,
	                                                                this->inputs.momentum);
	this->resetOutput();
}

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
	neuralNetwork = make_unique<StraightforwardNeuralNetwork>(StraightforwardNeuralNetwork::loadFrom(fileName.toStdString()));
	this->resetOutput();
}

StraightforwardNeuralNetwork& Controller::getNeuralNetwork() const
{
	return *neuralNetwork;
}

DataSet& Controller::getData() const
{
	return *data;
}
