#include "Iris.h"
#include <string>
#include <fstream>

using namespace std;

Iris::Iris()
{
	this->sizeOfData = 4;
	this->numberOfLabel = 3;
	this->sets[training].size = 150;
}

void Iris::loadData()
{
	string line;
	const string path = "../Data/iris/iris.txt";
	ifstream file(path);
	int count = 0;
	vector<vector<string>> individuals;
	const vector<string> temp;
	if (!file.is_open())
	{
		throw exception((" Cannot open :" + path).c_str());
	}
	getline(file, line); // labels
	while (getline(file, line))
	{
		individuals.push_back(temp);
		for (int i = 0; line != line.substr(line.find('\t') + 1); i++)
		{
			individuals[count].push_back(line.substr(0, line.find('\t')));
			line = line.substr(line.find('\t') + 1);
		}
		individuals[count].push_back(line.substr(0, line.find('\t')));
		count++;
	}
	file.close();
	sets[training].data.resize(this->sets[training].size);
	sets[training].labels.resize(this->sets[training].size);
	for (int i = 0; i < this->sets[training].size; i++)
	{
		sets[training].data[i].resize(this->sizeOfData);
		sets[training].labels[i].resize(this->numberOfLabel);
	}


	for (int i = 0; i < this->sets[training].size; i++)
	{
		for (int j = 0; j < this->sizeOfData; j++)
			sets[training].data[i][j] = stof(individuals[i][j]);

		if (individuals[i][4] == "setosa")
		{
			sets[training].labels[i][0] = 1;
			sets[training].labels[i][1] = 0;
			sets[training].labels[i][2] = 0;
		}
		else if (individuals[i][4] == "versicolor")
		{
			sets[training].labels[i][0] = 0;
			sets[training].labels[i][1] = 1;
			sets[training].labels[i][2] = 0;
		}
		else if (individuals[i][4] == "virginica")
		{
			sets[training].labels[i][0] = 0;
			sets[training].labels[i][1] = 0;
			sets[training].labels[i][2] = 1;
		}
		else
			throw exception("Cannot load iris data set");
	}
	sets[testing] = sets[training];
}
