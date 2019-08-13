#include "Iris.h"
#include <string>
#include <fstream>
#include "data/DataForClassification.h"

using namespace std;
using namespace snn;

Iris::Iris()
{
	this->sizeOfData = 4;
	this->numberOfLabel = 3;
	this->sizeOfTrainingSet = 150;
	this->sizeOfTestingSet = this->sizeOfTrainingSet;
}

void Iris::loadData()
{
	string line;
	const string path = "../Data/iris/iris.txt";
	ifstream file(path);
	int count = 0;
	vector<vector<string>> individuals;
	individuals.reserve(this->sizeOfTrainingSet);
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


	vector<vector<float>> inputsTraining;
	vector<vector<float>> labelsTraining;


	inputsTraining.resize(this->sizeOfTrainingSet);
	labelsTraining.resize(this->sizeOfTrainingSet);
	for (int i = 0; i < this->sizeOfTrainingSet; i++)
	{
		inputsTraining[i].resize(this->sizeOfData);
		labelsTraining[i].resize(this->numberOfLabel);
	}


	for (int i = 0; i < this->sizeOfTrainingSet; i++)
	{
		for (int j = 0; j < this->sizeOfData; j++)
			inputsTraining[i][j] = stof(individuals[i][j]);

		if (individuals[i][4] == "setosa")
		{
			labelsTraining[i][0] = 1;
			labelsTraining[i][1] = 0;
			labelsTraining[i][2] = 0;
		}
		else if (individuals[i][4] == "versicolor")
		{
			labelsTraining[i][0] = 0;
			labelsTraining[i][1] = 1;
			labelsTraining[i][2] = 0;
		}
		else if (individuals[i][4] == "virginica")
		{
			labelsTraining[i][0] = 0;
			labelsTraining[i][1] = 0;
			labelsTraining[i][2] = 1;
		}
		else
			throw exception("Cannot load iris data set");
	}
	
	this->data = new DataForClassification(inputsTraining, labelsTraining);
}
