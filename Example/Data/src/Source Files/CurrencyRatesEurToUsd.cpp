#include "CurrencyRatesEurToUsd.h"
#include <string>
#include <fstream>

using namespace std;


CurrencyRatesEurToUsd::CurrencyRatesEurToUsd()
{
	this->sizeOfData = numberOfInputRates + dateTimeSize;
	this->numberOfLabel = 1;
	this->dataTemp.resize(this->sizeOfData);
	this->dateTimeTemp.resize(this->dateTimeSize);
	this->ouputTemp.resize(1);
}

CurrencyRatesEurToUsd::~CurrencyRatesEurToUsd()
{
}

void CurrencyRatesEurToUsd::loadData()
{
	this->loadCSV(2016);
	this->sets[training].size = this->dateTimes.size() - numberOfInputRates - intervalBetweenTwoTrade;
	this->sets[testing].size = this->sets[training].size;
}

void CurrencyRatesEurToUsd::loadCSV(int year)
{
	string line;
	string path = "../Data/EURUSD/DAT_ASCII_EURUSD_M1_" + to_string(year) + ".csv"; // DAT_ASCII_EURUSD_M1_2016.csv
	ifstream file(path);
	int count = 0;

	if (!file.is_open())
	{
		throw exception((" Cannot open : " + path).c_str());
	}
	getline(file, line);
	while (getline(file, line, ';'))
	{
		this->dateTimes.push_back(this->getDateTimeFromLine(line));

		getline(file, line, ';');
		getline(file, line, ';');
		getline(file, line, ';');
		getline(file, line, ';');
		this->rates.push_back(stof(line));
		getline(file, line);

		if (file.eof())
		{
			count++;
			return;
		}

		if (line != "0")
			throw exception(("Parsing error : " + path).c_str());
		count++;
	}
	file.close();
}

inline vector<float>& CurrencyRatesEurToUsd::getDateTimeFromLine(string& line)
{
	/*this->dateTimeTemp[year] = (stof(line.substr(0, 4)) - 2000) / 16;
	this->dateTimeTemp[month] = stof(line.substr(4, 2)) / 12;
	this->dateTimeTemp[day] = stof(line.substr(6, 2)) / 30;
	this->dateTimeTemp[hour] = stof(line.substr(9, 2)) / 24;
	this->dateTimeTemp[minute] = stof(line.substr(11, 2)) / 60;
	this->dateTimeTemp[second] = stof(line.substr(13, 2)) / 60;*/

	return this->dateTimeTemp;
}


vector<float>& CurrencyRatesEurToUsd::getTrainingData(int index)
{
	//index += numberOfInputRates;
	/*for (int i = 0; i < dateTimeSize; i++)
		this->dataTemp[i] = dateTimes[index][i];*/

	for (int i = 0; i < numberOfInputRates; i++)
		this->dataTemp[i] = (rates[index - i] - rates[index - i - 1]) / rates[index - i - 1] * multiplicationFactor;
	/*this->dataTemp[0] = rates[index];
	this->dataTemp[1] = rates[index + intervalBetweenTwoTrade];*/
	return this->dataTemp;
}

vector<float>& CurrencyRatesEurToUsd::getTestingData(const int index)
{
	return this->getTrainingData(index);
}

vector<float>& CurrencyRatesEurToUsd::getTrainingOutputs(const int index)
{
	this->ouputTemp[0] = rates[index + intervalBetweenTwoTrade] - rates[index] * multiplicationFactor/5;
	return this->ouputTemp;
}

vector<float>& CurrencyRatesEurToUsd::getTestingOutputs(const int index)
{
	this->ouputTemp[0] = rates[index + intervalBetweenTwoTrade] - rates[index] * multiplicationFactor/5;

	if (this->ouputTemp[0] > 0.0f)
		this->ouputTemp[0] = 1.0f;
	else
		this->ouputTemp[0] = 0.0f;
	return this->ouputTemp;
}