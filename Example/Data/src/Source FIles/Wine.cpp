#include "Wine.h"
#include <string>
#include <fstream>

using namespace std;
using namespace snn;

Wine::Wine()
{
	this->sizeOfData = 13;
	this->numberOfLabel = 3;
	this->sizeOfTrainingSet = 178;
	this->sizeOfTestingSet = this->sizeOfTrainingSet;
}

void Wine::loadData()
{
	string line;
	const string path = "../Data/Wine/wine.data.txt";
	ifstream file(path);
	int count = 0;
	vector<vector<string>> individuals;
	individuals.reserve(this->sizeOfTrainingSet);
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

	vector<vector<float>> inputsTraining(this->sizeOfTrainingSet);
	vector<vector<float>> labelsTraining(this->sizeOfTrainingSet);

	for (int i = 0; i < this->sizeOfTrainingSet; i++)
	{
		inputsTraining[i].resize(this->sizeOfData);
		labelsTraining[i].resize(this->numberOfLabel);
	}


	for (int i = 0; i < this->sizeOfTrainingSet; i++)
	{
		for (int j = 0; j < this->sizeOfData; j++)
		{
			inputsTraining[i][j] = stof(individuals[i][j + 1]);
		}

		if (individuals[i][0] == "1")
		{
			labelsTraining[i][0] = 1;
			labelsTraining[i][1] = 0;
			labelsTraining[i][2] = 0;
		}
		else if (individuals[i][0] == "2")
		{
			labelsTraining[i][0] = 0;
			labelsTraining[i][1] = 1;
			labelsTraining[i][2] = 0;
		}
		else if (individuals[i][0] == "3")
		{
			labelsTraining[i][0] = 0;
			labelsTraining[i][1] = 0;
			labelsTraining[i][2] = 1;
		}
		else
			throw exception("Cannot load wine data set");
	}

	// Doesn't work if wine's values isn't normalize
	// Normalization
	/*for (int j = 0; j < this->sizeOfData; j++)
	{
		float maxValue = -1024;
		for (int i = 0; i < this->sizeOfTrainingSet; i++)
		{
			if (inputsTraining[i][j] > maxValue)
				maxValue = inputsTraining[i][j];
		}
		for (int i = 0; i < this->sizeOfTrainingSet; i++)
		{
			inputsTraining[i][j] /= maxValue;
		}
	}*/
	this->data = new StraightforwardData(classification, inputsTraining, labelsTraining);
}


