#include "MNIST.h"
#include <fstream>
#include "../../DataException.h"

using namespace std;

MNIST::MNIST()
{
	this->sizeOfData = 784;
	this->numberOfLabel = 10;
	this->sets[training].size = 60000;
	this->sets[testing].size = 10000;
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
	this->unshuffle();
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

	this->readSet(testing, imagesTestFile, labelsTestFile);
	this->readSet(training, imagesTrainFile, labelsTrainFile);
}

void MNIST::readSet(const set set, ifstream& images, ifstream& labels)
{
	if (!images.is_open()
		&& !labels.is_open())
	{
		throw FileOpeningFailed();
	}
	int i;
	unsigned char c;

	for (i = 0; !labels.eof(); i++)
	{
		c = labels.get();

		const vector<float> labelsTemp(10, 0);
		sets[set].labels.push_back(labelsTemp);

		if (!labels.eof())
			sets[set].labels.back()[c] = 1.0;
		else
			sets[set].labels.resize(sets[set].labels.size() - 1);
	}
	int shift = 0;

	for (i = 0; !images.eof(); i++)
	{
		const vector<float> imageTemp;
		sets[set].data.push_back(imageTemp);
		sets[set].data.back().reserve(this->sizeOfData);
		if (!images.eof())
			for (int j = 0; !images.eof() && j < this->sizeOfData;)
			{
				c = images.get();

				if (shift > 15)
				{
					const float value = static_cast<int>(c) / 255.0f * 2.0f - 1.0f;
					sets[set].data.back().push_back(value);
					j++;
				}
				else
					shift ++;
			}
	}
	images.close();
	labels.close();
}
