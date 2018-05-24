#include "CurrencyRatesEurToUsd.h"
#include <string>
#include <fstream>

using namespace std;


CurrencyRatesEurToUsd::CurrencyRatesEurToUsd()
{
	this->sizeOfData = numberOfInputRates + dateTimeSize;
	this->numberOfLabel = 1;
	//this->sets[training].size = ?;
	//this->sets[testing].size = ?;
}


CurrencyRatesEurToUsd::~CurrencyRatesEurToUsd()
{
}

void CurrencyRatesEurToUsd::loadData()
{
	int year = 2016;
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
		getline(file, line, ';');

		if (line != "0")
			throw exception(("Parsing error : " + path).c_str());

		count++;
	}
	file.close();
	sets[training].data.resize(1);
	sets[training].data[0].resize(66);
	//sets[testing] = sets[training];
}

inline vector<float>& CurrencyRatesEurToUsd::getDateTimeFromLine(string& line)
{
	vector<float> dateTime;
	dateTime.resize(6);

	dateTime[year] = stof(line.substr(0, 4));
	dateTime[month] = stof(line.substr(4, 2));
	dateTime[day] = stof(line.substr(6, 2));
	dateTime[hour] = stof(line.substr(9, 2));
	dateTime[minute] = stof(line.substr(11, 2));
	dateTime[second] = stof(line.substr(13, 2));

	return dateTime;
}


std::vector<float>& CurrencyRatesEurToUsd::getTrainingData(int index)
{
	index += numberOfInputRates;
	for (int i = 0; i < dateTimeSize; i++)
		sets[training].data[index][i] = dateTimes[index][i];

	for (int i = 0; i < numberOfInputRates; i++)
		sets[training].data[index][i] = (rates[index - i] - rates[index - i - 1]) / rates[index - i - 1];

	return sets[training].data[index];
}

std::vector<float>& CurrencyRatesEurToUsd::getTestingData(int index)
{
	return this->getTrainingData(index);
}
