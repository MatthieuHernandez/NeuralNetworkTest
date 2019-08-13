#include "MNIST.h"
#include <fstream>
#include "../../DataException.h"
#include "data/DataForClassification.h"

using namespace std;
using namespace snn;

MNIST::MNIST()
{
	this->sizeOfData = 784;
	this->numberOfLabel = 10;
	this->sizeOfTrainingSet = 60000;
	this->sizeOfTestingSet = 10000;
}

void MNIST::loadData()
{
	string path = "../Data/mnist/";
	const string path_MNIST[4] = {
		path + "t10k-images.idx3-ubyte",
		path + "t10k-labels.idx1-ubyte",
		path + "train-images.idx3-ubyte",
		path + "train-labels.idx1-ubyte"
	};
	this->readImages(path_MNIST);
	//this->unshuffle();
}

void MNIST::readImages(const string path_MNIST[])
{
	ifstream imagesTestFile;
	ifstream labelsTestFile;
	ifstream imagesTrainFile;
	ifstream labelsTrainFile;

	imagesTestFile.open(path_MNIST[0], ios::in | ios::binary);
	labelsTestFile.open(path_MNIST[1], ios::in | ios::binary);
	imagesTrainFile.open(path_MNIST[2], ios::in | ios::binary);
	labelsTrainFile.open(path_MNIST[3], ios::in | ios::binary);

	vector<vector<float>> inputsTraining;
	vector<vector<float>> labelsTraining;
	vector<vector<float>> inputsTesting;
	vector<vector<float>> labelsTesting;

	this->readSet(inputsTraining, labelsTraining, imagesTrainFile, labelsTrainFile);
	this->readSet(inputsTesting, labelsTesting, imagesTestFile, labelsTestFile);

	this->data = new DataForClassification(inputsTraining, labelsTraining, inputsTesting, labelsTesting);
}

void MNIST::readSet(vector<vector<float>>& inputs,
                      vector<vector<float>>& labels,
                      ifstream& images,
                      ifstream& imageLabels)
{
	if (!images.is_open()
		&& !imageLabels.is_open())
	{
		throw FileOpeningFailed();
	}
	int i;
	unsigned char c;

	for (i = 0; !imageLabels.eof(); i++)
	{
		c = imageLabels.get();

		const vector<float> labelsTemp(10, 0);
		labels.push_back(labelsTemp);

		if (!imageLabels.eof())
			labels.back()[c] = 1.0;
		else
			labels.resize(labels.size() - 1);
	}
	int shift = 0;

	for (i = 0; !images.eof(); i++)
	{
		const vector<float> imageTemp;
		inputs.push_back(imageTemp);
		inputs.back().reserve(this->sizeOfData);
		if (!images.eof())
			for (int j = 0; !images.eof() && j < this->sizeOfData;)
			{
				c = images.get();

				if (shift > 15)
				{
					const float value = static_cast<int>(c) / 255.0f * 2.0f - 1.0f;
					inputs.back().push_back(value);
					j++;
				}
				else
					shift ++;
			}
	}
	images.close();
	imageLabels.close();
}
