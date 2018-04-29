#include <algorithm>
#include <vector>
#include "Data.h"

using namespace std;

void Data::loadData()
{
}

vector<float>& Data::getNextTrainingData(bool isRandom)
{
	return this->getNextData(training, isRandom);
}

vector<float>& Data::getNextTrainingLabel()
{
	return this->getNextLabel(training);
}

vector<float>& Data::getNextTestingData()
{
	return this->getNextData(testing, false);
}

vector<float>& Data::getNextTestingLabel()
{
	return this->getNextLabel(testing);
}

void Data::shuffle()
{
	const auto random = rand();
	for (int i = 0; i < 2; ++i)
	{
		srand(random);
		random_shuffle(sets[training].data.begin(), sets[training].data.end());
	}
}

vector<float>& Data::getNextData(const set set, bool isRandom)
{
	if (set == training && this->sets[set].index == this->sets[set].size)
	{
		this->shuffle();
		this->sets[set].index = 0;
	}
	else
		this->sets[set].index++;

	return sets[set].data[sets[set].index];
}

vector<float>& Data::getNextLabel(const set set)
{
	return sets[set].labels[sets[set].index];
}
