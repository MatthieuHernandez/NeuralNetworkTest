#include "MNIST.h"
#include <fstream>

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
	string path = "mnist/";
	const string path_MNIST[4] = {
		path + "t10k-images.idx3-ubyte",
		path + "t10k-labels.idx1-ubyte",
		path + "train-images.idx3-ubyte",
		path + "train-labels.idx1-ubyte"};

	this->readImages(path_MNIST);
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

    this->readSet(this->testing, imagesTestFile, labelsTestFile);
	this->readSet(this->training, imagesTrainFile, labelsTrainFile);
}

void MNIST::readSet(const set set, ifstream &images, ifstream &labels)
{
    if(!images.is_open()
    && !labels.is_open())
    {
		throw new OpenFailFailedException();
    }
    int i;
    unsigned char c;

    for(i = 0; !labels.eof(); i++)
    {
        c = labels.get();

        vector<float> v;
        v.resize(10, 0.0);
        sets[set].labels.push_back(v);

        if(!labels.eof())
			sets[set].labels.back()[c] = 1.0;
    }
	auto shift = 0;
	for(i = 0; !images.eof(); i++)
    {
	    const vector<float> v;
		sets[set].data.push_back(v);

        for(int j = 0; !images.eof() && j < 784;)
        {
            c = images.get();

            if(shift > 15)
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
