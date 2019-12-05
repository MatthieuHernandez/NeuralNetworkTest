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
}

void Controller::initializeNeuralNetwork(const QString& dataSetName)
{
	const auto date = QDateTime::currentDateTime().toString("yyyy-MM-dd");
	const auto fileName = "./Save/autosave_" + dataSetName + "_" + date;
	this->inputs.option.saveFilePath = fileName.toStdString();

	this->neuralNetwork = make_unique<StraightforwardNeuralNetwork>(this->inputs.structure,
	                                                                this->inputs.activationFunctions,
	                                                                this->inputs.option);
	this->resetOutput();
}

void Controller::save(const QString& fileName)
{
	neuralNetwork->saveAs(fileName.toStdString());
}

void Controller::load(const QString& fileName)
{
	neuralNetwork = make_unique<StraightforwardNeuralNetwork>(
		StraightforwardNeuralNetwork::loadFrom(fileName.toStdString()));
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

void Controller::setAutoSave(bool value)
{
	this->inputs.option.autoSaveWhenBetter = value;
}

bool Controller::getAutoSave() const
{
	return this->inputs.option.autoSaveWhenBetter;
}

void Controller::setMultithreading(bool value)
{
	this->inputs.option.useMultithreading = value;
}

bool Controller::getMultithreading() const
{
	return this->inputs.option.useMultithreading;
}

void Controller::setLearningRate(float value)
{
	this->inputs.option.learningRate = value;
}

float Controller::getLearningRate() const
{
	return this->inputs.option.learningRate;
}

void Controller::setMomentum(float value)
{
	this->inputs.option.momentum = value;
}

float Controller::getStructure(int layer) const
{
	return this->inputs.structure[layer];
}

int Controller::getNumberOfLayer() const
{
	return this->inputs.structure.size() - 1;
}

void Controller::setStructure(int layer, float value)
{
	this->inputs.structure[layer] = value;
}

float Controller::getActivationFunctions(int layer)
{
	return this->inputs.activationFunctions[layer];
}

void Controller::setActivationFunctions(int layer, activationFunctionType value)
{
	this->inputs.activationFunctions[layer] = value;
}

float Controller::getMomentum() const
{
	return this->inputs.option.momentum;
}

void Controller::addLayer(int index)
{
	const auto it1 = this->inputs.structure.begin();
	const auto it2 = this->inputs.activationFunctions.begin();
	const auto value = this->inputs.structure[index];
	const auto function = this->inputs.activationFunctions[index];
	this->inputs.structure.insert(it1 + index, value);
	this->inputs.activationFunctions.insert(it2 + index, function);
}

void Controller::removeLayer(int index)
{
	if (index < this->inputs.structure.size() - 1)
	{
		
		const auto it1 = this->inputs.structure.begin();
		const auto it2 = this->inputs.activationFunctions.begin();
		this->inputs.structure.erase(it1 + index);
		this->inputs.activationFunctions.erase(it2 + index);
	}
}
