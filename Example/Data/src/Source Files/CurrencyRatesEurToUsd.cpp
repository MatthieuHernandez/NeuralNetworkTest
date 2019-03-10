#include "CurrencyRatesEurToUsd.h"
#include <string>
#include <fstream>

using namespace std;
using namespace snn;

CurrencyRatesEurToUsd::CurrencyRatesEurToUsd()
{
	this->dateTimeTemp = nullptr;
	this->sizeOfData = numberOfInputRates + dateTimeSize;
	this->numberOfLabel = 1;
	this->dataTemp.resize(this->sizeOfData);
	this->outputTemp.resize(1);
}

void CurrencyRatesEurToUsd::loadData()
{
	vector<vector<float>> inputs;
	vector<vector<float>> labels;

	this->loadCSV(2016);
	this->createData(inputs, labels);
	//this->unshuffle();	
	this->data = new StraightforwardData(classification, inputs, labels);
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
		this->dateTimes.push_back(this->getDateTimeFromLine(line)); // DateTime Stamp

		getline(file, line, ';'); // Bar OPEN Bid Quote;
		getline(file, line, ';'); // Bar HIGH Bid Quote;
		getline(file, line, ';'); // Bar LOW Bid Quote;
		getline(file, line, ';'); // Bar CLOSE Bid Quote;
		this->rates.push_back(stof(line));
		getline(file, line); // Volume (always 0)

		if (line != "0")
			throw exception(("Parsing error : " + path[0]).c_str());
		count++;

		if (file.eof())
			return;
	}
	file.close();
}

void CurrencyRatesEurToUsd::createData(vector<vector<float>>& inputs, vector<vector<float>>& labels)
{
	for (int i = numberOfInputRates; i < (static_cast<int>(dateTimes.size()) - intervalBetweenTwoTrade); i++)
	{
		if (isAGap(i) || isWrongDate(i))
		{
			numberOfGap ++;
			i += numberOfInputRates-1;
			continue;
		}
		if(i < numberOfInputRates)
		 continue;

		this->createTrainingData(i - this->sizeOfTrainingSet, inputs);
		this->createTrainingOutputs(i,labels);
	}
	this->sizeOfTrainingSet = static_cast<int>(labels.size());
}

inline
bool CurrencyRatesEurToUsd::isAGap(const int index)
{
	return this->dateTimes[index] != this->dateTimes[index + 1].addSecs(-60);
}

inline
bool CurrencyRatesEurToUsd::isWrongDate(const int index)
{
	return this->dateTimes[index].date() <= QDate(2015, 12, 31)
		|| this->dateTimes[index].date() >= QDate(2017, 01, 01);
}

inline QDateTime& CurrencyRatesEurToUsd::getDateTimeFromLine(string& line)
{
	const QDate date(stoi(line.substr(0, 4)), stoi(line.substr(04, 2)), stoi(line.substr(06, 2)));
	const QTime time(stoi(line.substr(9, 2)), stoi(line.substr(11, 2)), stoi(line.substr(13, 2)));
	dateTimeTemp = new QDateTime(date, time);
	return *dateTimeTemp;
}


void CurrencyRatesEurToUsd::createTrainingData(const int index, vector<vector<float>>& inputs)
{
	for (int i = 0; i < numberOfInputRates; i++)
		this->dataTemp[i] = (rates[index - i] - rates[index - i - 1]) / rates[index - i - 1] * multiplicationFactor;

	this->dataTemp[numberOfInputRates + 0] = (static_cast<float>(this->dateTimes[index].date().year()) - 2000.0f) / 16.0f;
	this->dataTemp[numberOfInputRates + 1] = static_cast<float>(this->dateTimes[index].date().month()) / 12.0f;
	this->dataTemp[numberOfInputRates + 2] = static_cast<float>(this->dateTimes[index].date().day()) / 31.0f;
	this->dataTemp[numberOfInputRates + 3] = static_cast<float>(this->dateTimes[index].time().hour()) / 24.0f;
	this->dataTemp[numberOfInputRates + 4] = static_cast<float>(this->dateTimes[index].time().minute()) / 60.0f;
	this->dataTemp[numberOfInputRates + 5] = static_cast<float>(this->dateTimes[index].time().second()) / 60.0f;

	inputs.push_back(this->dataTemp);
}

void CurrencyRatesEurToUsd::createTrainingOutputs(const int index, vector<vector<float>>& labels)
{
	this->outputTemp[0] = (rates[index + intervalBetweenTwoTrade] - rates[index]) * multiplicationFactor / 5.0f;

	labels.push_back(this->outputTemp);
}
