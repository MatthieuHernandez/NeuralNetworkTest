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
	this->createData();
}

void CurrencyRatesEurToUsd::loadCSV(int year)
{
	string line;
	ifstream file(path[0]);
	int count = 0;

	if (!file.is_open())
	{
		throw exception(("Cannot open : " + path[0]).c_str());
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

		if (line != "0")
			throw exception(("Parsing error : " + path[0]).c_str());
		count++;

		if (file.eof())
			return;
	}
	file.close();
}

void CurrencyRatesEurToUsd::createData()
{
	this->clearData();

	const auto totalSize = this->dateTimes.size() - (numberOfInputRates + intervalBetweenTwoTrade);

	for(int i = 0; i < totalSize; i++)
	{
		if(isAGap(i))
			i += numberOfInputRates;

		this->createTrainingData(i-this->sets[training].size);
		this->createTrainingOutputs(i);
	}
	this->sets[training].size = this->sets[training].labels.size();
	this->sets[testing] = this->sets[training];
}

bool CurrencyRatesEurToUsd::isAGap(const int index)
{
	QDateTime dateTime1 = 

	if((this->dateTimes[i][second] == this->dateTimes[j][second])
	&& (this->dateTimes[i][hour] == this->dateTimes[j][hour] || (this->dateTimes[i][second] == 1 && this->dateTimes[j][second] == 0))


		return false;
	return true;
}

inline vector<float>& CurrencyRatesEurToUsd::getDateTimeFromLine(string& line)
{
	this->dateTimeTemp[year] = (stof(line.substr(0, 4)) - 2000.0f) / 16.0f;
	this->dateTimeTemp[month] = stof(line.substr(4, 2)) / 12.0f;
	this->dateTimeTemp[day] = stof(line.substr(6, 2)) / 30.0f;
	this->dateTimeTemp[hour] = stof(line.substr(9, 2)) / 24.0f;
	this->dateTimeTemp[minute] = stof(line.substr(11, 2)) / 60.0f;
	this->dateTimeTemp[second] = stof(line.substr(13, 2)) / 60.0f;

	return this->dateTimeTemp;
}


vector<float>& CurrencyRatesEurToUsd::createTrainingData(int index)
{
	this->sets[training].data.push_back()
	//index += numberOfInputRates;
	/*for (int i = 0; i < dateTimeSize; i++)
		this->dataTemp[i] = dateTimes[index][i];*/

	for (int i = 0; i < numberOfInputRates; i++)
		this->dataTemp[i] = (rates[index - i] - rates[index - i - 1]) / rates[index - i - 1] * multiplicationFactor;
	/*this->dataTemp[0] = rates[index];
	this->dataTemp[1] = rates[index + intervalBetweenTwoTrade];*/
	return this->dataTemp;
}

vector<float>& CurrencyRatesEurToUsd::createTrainingOutputs(const int index)
{
	this->sets[training].labels.push_back()
	this->ouputTemp[0] = (rates[index + intervalBetweenTwoTrade] - rates[index]) * multiplicationFactor / 5;
	return this->ouputTemp;
}
