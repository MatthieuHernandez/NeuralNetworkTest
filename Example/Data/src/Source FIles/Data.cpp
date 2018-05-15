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
	rand();
	srand(random);
	random_shuffle(sets[training].data.begin(), sets[training].data.end());
	srand(random);
	random_shuffle(sets[training].labels.begin(), sets[training].labels.end());
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


int Data::getLabel(int index, set displayedSet)
{
	for (int i = 0; i < this->numberOfLabel; i++)
	{
		if (this->sets[displayedSet].labels[index][i] == 1)
			return i;
	}
	throw exception("wrong label");
}
