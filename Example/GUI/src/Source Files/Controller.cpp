#include "Controller.h"
#include <QDateTime>

using namespace std;
using namespace snn;

Controller::Controller(Dataset& data)
{
    this->data = unique_ptr<Dataset>(&data);
}

void Controller::resetOutput()
{
	this->neuralNetwork->stopTraining();
}

void Controller::deleteNeuralNetwork()
{
	this->neuralNetwork.reset();
}

void Controller::initializeNeuralNetwork(const QString& dataSetName)
{
	const auto date = QDateTime::currentDateTime().toString("yyyy-MM-dd");
	const auto fileName = "./Save/autosave_" + dataSetName + "_" + date;
	this->inputs.saveFilePath = fileName.toStdString();

	this->neuralNetwork = make_unique<StraightforwardNeuralNetwork>(this->inputs.structure);
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

Dataset& Controller::getDataset() const
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
