#include "Iris.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

Iris::Iris()
{
	this->sizeOfData = 4;
	this->numberOfLabel = 3;
	this->sets[training].size = 150;
}

Iris::~Iris()
{
}

void Iris::loadData()
{
	string line;
	string path = "../TestIris/iris.txt";
	ifstream file(path);
	int count = 0;
	vector<vector<string>> individuals;
	vector<string> temp;
	if (!file.is_open())
	{
		throw exception((" Cannot open :" + path).c_str());
	}
	else
	{
		getline(file, line); // labels
		while (getline(file, line))
		{
			//cout << line << endl;
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
	}
	sets[training].data.resize(150);
	sets[training].labels.resize(150);
	for (int i = 0; i < 150; i++) // c <= 500
	{
		sets[training].data[i].resize(4);
		sets[training].labels[i].resize(3);
	}


	for (int i = 0; i < 150; i++) // c <= 500
	{
		sets[training].data[i][0] = stof(individuals[i][0]);
		sets[training].data[i][1] = stof(individuals[i][1]);
		sets[training].data[i][2] = stof(individuals[i][2]);
		sets[training].data[i][3] = stof(individuals[i][3]);

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
