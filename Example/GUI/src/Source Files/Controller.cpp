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
	this->inputs.saveFilePath = fileName.toStdString();

	this->neuralNetwork = make_unique<StraightforwardNeuralNetwork>(this->inputs.NumberOfInputs, this->inputs.structure);
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

void Controller::addLayer(int index)
{
	const auto it1 = this->inputs.structure.begin();
	const auto value = this->inputs.structure[index];
	this->inputs.structure.insert(it1 + index, value);
}

void Controller::removeLayer(int index)
{
	if (index < this->inputs.structure.size() - 1)
	{
		
		const auto it1 = this->inputs.structure.begin();
		this->inputs.structure.erase(it1 + index);
	}
}
