#pragma once
#include <string>
#include <QDateTime>
#include "DataForRegression.h"

enum timeUnit
{
	year = 0,
	month,
	day,
	hour,
	minute,
	second
};

class CurrencyRatesEurToUsd : public DataForRegression
{
private:

	int numberOfGap = 0;

	const float multiplicationFactor = 1000;

	std::vector<QDateTime> dateTimes;
	QDateTime* dateTimeTemp;
	std::vector<float> rates;
	QDateTime& getDateTimeFromLine(std::string& line);

	std::vector<float> dataTemp;
	std::vector<float> outputTemp;

	void createData();
	bool isAGap(const int index);
	bool isWrongDate(const int index);


public:

	const int numberOfInputRates = 60;
	const int dateTimeSize = 6;
	const int intervalBetweenTwoTrade = 5;

	int getNumberOfGaps() const { return numberOfGap; }
	int getNumberOfLines() const { return static_cast<int>(dateTimes.size()); }

	std::string path[1] = {"../Data/EURUSD/DAT_ASCII_EURUSD_M1_2016.csv"};

	CurrencyRatesEurToUsd();
	~CurrencyRatesEurToUsd() {}

	void loadData() override;
	void loadCSV(int year);

	void createTrainingData(const int index);
	void createTrainingOutputs(const int index);
};
