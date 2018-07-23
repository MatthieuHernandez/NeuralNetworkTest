#include "CIFAR_10.h"
#include <fstream>
#include "../../DataException.h"

using namespace std;

CIFAR_10::CIFAR_10()
{
	this->sizeOfData = 3072; // 32*32*3
	this->numberOfLabel = 10;
	this->sets[training].size = 60000;
	this->sets[testing].size = 10000;
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
	this->unshuffle();
}

void CIFAR_10::readImages(const string path_CIFAR_10[])
{
	ifstream lerningFiles[5];
	ifstream testingFile;

	for (int i = 0; i < 5; i++)
	{
		lerningFiles[i].open(path_CIFAR_10[i], ios::in | ios::binary);
		this->readSet(testing, lerningFiles[i]);
	}

	testingFile.open(path_CIFAR_10[5], ios::in | ios::binary);
	this->readSet(training, testingFile);
}

void CIFAR_10::readSet(const set set, std::ifstream& file)
{
	if (!file.is_open()
		&& !file.is_open())
	{
		throw FileOpeningFailed();
	}

	unsigned char c;
	vector<float> v(10);

	for (int i = 0; !file.eof(); i++)
	{
		c = file.get();

		v = {0};
		sets[set].labels.push_back(v);

		if (!file.eof())
			sets[set].labels.back()[c] = 1.0;
		else
			sets[set].labels.resize(sets[set].labels.size() - 1);

		const vector<float> imageTemp;
		sets[set].data.push_back(imageTemp);
		sets[set].data.back().reserve(this->sizeOfData);

		for (i = 0; this->sizeOfData; i++)
		{
			c = file.get();

			const float value = static_cast<int>(c) / 255.0f * 2.0f - 1.0f;
			sets[set].data.back().push_back(value);
		}
	}

	file.close();
}
