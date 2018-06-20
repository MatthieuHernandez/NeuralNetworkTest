#pragma once
#include <string>
#include <QDateTime>
#include "Data.h"
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

	const int numberOfInputRates = 15;
	const int dateTimeSize = 6;
	const int intervalBetweenTwoTrade = 5;
	const float multiplicationFactor = 1000;

	std::vector<std::vector<QDateTime>> dateTimes;
	std::vector<float> rates;
	std::vector<float>& getDateTimeFromLine(std::string& line);

	QDateTime dateTimeTemp;
	std::vector<float> dataTemp;
	std::vector<float> ouputTemp;

	void createData();
	bool isAGap(const int index);

public:

	std::string path[1] = {"../Data/EURUSD/DAT_ASCII_EURUSD_M1_2016.csv"};

	 CurrencyRatesEurToUsd();
	 ~CurrencyRatesEurToUsd();

	void loadData() override;
	void loadCSV(int year);

	std::vector<float>& createTrainingData(const int index);
	std::vector<float>& createTrainingOutputs(const int index);
};
