#include <algorithm>
#include <vector>
#include "Data.h"
#include "../../../../NeuralNetwork/src/Header Files/perceptron.h"

using namespace std;

void Data::loadData()
{
	unshuffle();
}

void Data::clearData()
{
	this->sets[training].labels.clear();
	this->sets[training].data.clear();
	this->sets[testing].labels.clear();
	this->sets[testing].data.clear();
	this->sets[training].size = 0;
	this->sets[testing].size = 0;
}

void Data::shuffle()
{
	rand();
	if (indexes.empty())
	{
		indexes.resize(sets[training].size);
		for (int i = 0; i < indexes.size(); i++)
			indexes[i] = i;
	}

	random_shuffle(indexes.begin(), indexes.end());
}

void Data::unshuffle()
{
	indexes.clear();
	indexes.resize(sets[training].size);
	for (int i = 0; i < indexes.size(); i++)
		indexes[i] = i;
}

vector<float>& Data::getTrainingData(const int index)
{
	return this->sets[training].data[indexes[index]];
}

vector<float>& Data::getTestingData(const int index)
{
	return this->sets[testing].data[index];
}

vector<float>& Data::getTrainingOutputs(const int index)
{
	return this->sets[training].labels[indexes[index]];
}
