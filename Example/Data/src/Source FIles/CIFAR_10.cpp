#include "CIFAR_10.h"
#include <fstream>
#include "../../DataException.h"

using namespace std;
using namespace snn;

CIFAR_10::CIFAR_10()
{
	this->sizeOfData = 3072; // 32*32*3
	this->numberOfLabel = 10;
	this->sizeOfTrainingSet = 50000;
	this->sizeOfTestingSet = 10000;
}

void CIFAR_10::loadData()
{
	string path = "../Data/CIFAR-10/";
	const string path_CIFAR_10[6] =
	{
		path + "data_batch_1.bin",
		path + "data_batch_2.bin",
		path + "data_batch_3.bin",
		path + "data_batch_4.bin",
		path + "data_batch_5.bin",
		path + "test_batch.bin"

	};
	this->readImages(path_CIFAR_10);
	//this->unshuffle();
}

void CIFAR_10::readImages(const string path_CIFAR_10[])
{
	ifstream lerningFiles[5];
	ifstream testingFile;

	vector<vector<float>> inputsTraining;
	vector<vector<float>> labelsTraining;
	vector<vector<float>> inputsTesting;
	vector<vector<float>> labelsTesting;

	for (int i = 0; i < 5; i++)
	{
		lerningFiles[i].open(path_CIFAR_10[i], ios::in | ios::binary);
		this->readSet(inputsTraining,
		              labelsTraining,
		              lerningFiles[i]);
	}

	testingFile.open(path_CIFAR_10[5], ios::in | ios::binary);
	this->readSet(inputsTesting,
	              labelsTesting,
	              testingFile);

	this->data = new StraightforwardData(classification, inputsTraining, labelsTraining, inputsTesting, labelsTesting);
}

void CIFAR_10::readSet(std::vector<std::vector<float>>& inputs,
                       std::vector<std::vector<float>>& labels,
                       std::ifstream& file)
{
	if (!file.is_open())
	{
		throw FileOpeningFailed();
	}

	for (int i = 0; !file.eof(); i++)
	{
		unsigned char c = file.get();

		const vector<float> labelsTemp(10, 0);
		labels.push_back(labelsTemp);

		if (!file.eof())
			labels.back()[c] = 1.0;
		else
			labels.resize(labels.size() - 1);

		const vector<float> imageTemp;
		inputs.push_back(imageTemp);
		inputs.back().reserve(this->sizeOfData);

		for (int j = 0; !file.eof() && j < this->sizeOfData; j++)
		{
			c = file.get();

			const float value = static_cast<int>(c) / 255.0f * 2.0f - 1.0f;
			inputs.back().push_back(value);
		}
	}

	file.close();
}
