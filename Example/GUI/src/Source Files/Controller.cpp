#include "Controller.h"
#include <ctime>

using namespace std;

Controller::Controller(Data& data)
{
	this->data = &data;
	this->neuralNetwork = nullptr;
}

void Controller::initializeData()
{
	this->data->loadData();
}

/*this->neuralNetwork = std::make_unique<NeuralNetwork>(
vector<unsigned int>{static_cast<unsigned int>(MNIST.sizeOfImages), 150, 80, static_cast<unsigned int>(MNIST.numberOfLabel)},
vector<activationFunction>{sigmoid, sigmoid, sigmoid}, 0.05f, 0.0f);*/
void Controller::initializeNeuralNetwork(vector<unsigned int> structure,
                                         vector<activationFunction> activationFunction,
                                         float learningRate,
                                         float momentum)
{
	this->neuralNetwork = new NeuralNetwork(structure, activationFunction, learningRate, momentum);
}

void Controller::compute()
{
	// TODO
	/*auto clusteringRateMax = -1.0f;
	auto epochMax = 0;

	auto numberOfClockCycles = clock();
	for (int count = 1; ; count++)
	{

		for (int index = 0; index < data.testing.size; index++)
		{
			neuralNetwork->
				calculateClusteringRateForClassificationProblem(MNIST.testing.images[index], getLabel(index, testing));
		}
		const auto clusteringRate = neuralNetwork->getClusteringRate();
		if (clusteringRate > clusteringRateMax)
		{
			clusteringRateMax = clusteringRate;
			epochMax = count;
		}
		cout << "clustering rate : " << clusteringRate << " epoch : " << count << " time : " << (float)(clock() - numberOfClockCycles) /
			CLOCKS_PER_SEC << " secondes" << endl;
		numberOfClockCycles = clock();

		cout << "clustering rate max : " << clusteringRateMax << " epoch : " << epochMax << endl;
		clusteringRateVector.push_back(clusteringRate * 100);
		graphClusteringRate();
		ui->labelClusteringRateMax->setText(
			QString::fromStdString(
			(string)"Clustering max : " + data::to_string_with_precision(clusteringRateMax * 100, 2) + "%"));
		QApplication::processEvents();

		const int index_max = MNIST.trainig.size;

		for (int index = 0; index < index_max; index++)
		{
			neuralNetwork->train(MNIST.trainig.images[index], MNIST.trainig.labels[index]);
			if (index % 1000 == 0)
			{
				ui->labelCount->setText(QString::fromStdString((string)"Count : " + to_string(index)));
				QApplication::processEvents();
			}
		}
		ui->labelCount->setText(QString::fromStdString((string)"Count : " + to_string(index_max)));
		QApplication::processEvents();
	}*/
}

NeuralNetwork& Controller::getNeuralNetwork() const
{
	return *neuralNetwork;
}

Data& Controller::getData() const
{
	return *data;
}
