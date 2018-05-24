#include <algorithm>
#include <vector>
#include "Data.h"
#include "../../../../NeuralNetwork/src/Header Files/perceptron.h"

using namespace std;

void Data::loadData()
{
}

void Data::shuffle()
{
	rand();
	if (indexes.empty())
	{
		indexes.resize(sets[training].size);
		for (int i = 0;  i < indexes.size(); i++)
			indexes[i] = i;
	}

	random_shuffle(indexes.begin(), indexes.end());
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
