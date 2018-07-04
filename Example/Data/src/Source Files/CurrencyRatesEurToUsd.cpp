#include "CurrencyRatesEurToUsd.h"
#include <string>
#include <fstream>

using namespace std;

CurrencyRatesEurToUsd::CurrencyRatesEurToUsd()
{
	this->dateTimeTemp = nullptr;
	this->sizeOfData = numberOfInputRates + dateTimeSize;
	this->numberOfLabel = 1;
	this->dataTemp.resize(this->sizeOfData);
	this->ouputTemp.resize(1);
}

CurrencyRatesEurToUsd::~CurrencyRatesEurToUsd()
{
}

void CurrencyRatesEurToUsd::loadData()
{
	this->loadCSV(2016);
	this->createData();
	this->unshuffle();
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

	for (int i = numberOfInputRates; i < (dateTimes.size() - intervalBetweenTwoTrade); i++)
	{
		if (isAGap(i))
		{
			numberOfGap ++;
			i += numberOfInputRates;
			continue;
		}
		this->createTrainingData(i - this->sets[training].size);
		this->createTrainingOutputs(i);
	}
	this->sets[training].size = this->sets[training].labels.size();
	this->sets[testing] = this->sets[training];
}

bool CurrencyRatesEurToUsd::isAGap(const int index)
{
	return this->dateTimes[index] != this->dateTimes[index + 1].addSecs(-60);
}

inline QDateTime& CurrencyRatesEurToUsd::getDateTimeFromLine(string& line)
{
	QDate date(stoi(line.substr(0, 4)), stoi(line.substr(04, 2)), stoi(line.substr(06, 2)));
	QTime time(stoi(line.substr(9, 2)), stoi(line.substr(11, 2)), stoi(line.substr(13, 2)));
	dateTimeTemp = new QDateTime(date, time);
	return *dateTimeTemp;
}


void CurrencyRatesEurToUsd::createTrainingData(int index)
{
	for (int i = 0; i < numberOfInputRates; i++)
		this->dataTemp[i] = (rates[index - i] - rates[index - i - 1]) / rates[index - i - 1] * multiplicationFactor;

	this->dataTemp[numberOfInputRates + 0] = (static_cast<float>(this->dateTimes[index].date().year()) - 2000.0f) / 16.f;
	this->dataTemp[numberOfInputRates + 1] = static_cast<float>(this->dateTimes[index].date().month()) / 12.0f;
	this->dataTemp[numberOfInputRates + 2] = static_cast<float>(this->dateTimes[index].date().day()) / 31;
	this->dataTemp[numberOfInputRates + 3] = static_cast<float>(this->dateTimes[index].time().hour()) / 24;
	this->dataTemp[numberOfInputRates + 4] = static_cast<float>(this->dateTimes[index].time().minute()) / 60;
	this->dataTemp[numberOfInputRates + 5] = static_cast<float>(this->dateTimes[index].time().second()) / 60;

	this->sets[training].data.push_back(this->dataTemp);
}

void CurrencyRatesEurToUsd::createTrainingOutputs(const int index)
{
	this->ouputTemp[0] = (rates[index + intervalBetweenTwoTrade] - rates[index]) * multiplicationFactor / 5.0f;

	this->sets[training].labels.push_back(this->ouputTemp);
}
