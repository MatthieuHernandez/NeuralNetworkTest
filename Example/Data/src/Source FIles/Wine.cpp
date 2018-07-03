#include "Wine.h"
#include <string>
#include <fstream>

using namespace std;

Wine::Wine()
{
	this->sizeOfData = 13;
	this->numberOfLabel = 3;
	this->sets[training].size = 178;
	this->sets[testing].size = this->sets[training].size;
}

void Wine::loadData()
{
	string line;
	const string path = "../Data/Wine/wine.data.txt";
	ifstream file(path);
	int count = 0;
	vector<vector<string>> individuals;
	const vector<string> temp;
	if (!file.is_open())
	{
		throw exception((" Cannot open :" + path).c_str());
	}
	while (getline(file, line))
	{
		individuals.push_back(temp); 
		for (int i = 0; line != line.substr(line.find(',') + 1); i++)
		{
			individuals[count].push_back(line.substr(0, line.find(',')));
			line = line.substr(line.find(',') + 1);
		}
		individuals[count].push_back(line.substr(0, line.find(',')));
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

		if (individuals[i][0] == "1")
		{
			sets[training].labels[i][0] = 1;
			sets[training].labels[i][1] = 0;
			sets[training].labels[i][2] = 0;
		}
		else if (individuals[i][0] == "2")
		{
			sets[training].labels[i][0] = 0;
			sets[training].labels[i][1] = 1;
			sets[training].labels[i][2] = 0;
		}
		else if (individuals[i][0] == "3")
		{
			sets[training].labels[i][0] = 0;
			sets[training].labels[i][1] = 0;
			sets[training].labels[i][2] = 1;
		}
		else
			throw exception("Cannot load wine data set");
	}
	sets[testing] = sets[training];
}
