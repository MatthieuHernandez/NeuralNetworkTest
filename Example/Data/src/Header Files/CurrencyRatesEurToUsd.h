#pragma once
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

	const int numberOfInputRates = 60;
	const int dateTimeSize = 6;
	const int intervalBetweenTwoTrade = 5;

	std::vector<std::vector<float>> dateTimes;
	std::vector<float> rates;
	std::vector<float>& getDateTimeFromLine(std::string& line);

	std::vector<float> dataTemp;
	std::vector<float> dateTimeTemp;
	std::vector<float> ouputTemp;


public:

	CurrencyRatesEurToUsd();
	~CurrencyRatesEurToUsd();

	void loadData() override;
	void loadCSV(int year);

	std::vector<float>& getTrainingData(int index) override;
	std::vector<float>& getTestingData(int index) override;

	std::vector<float>& getTestingOutputs(const int index) override;
	std::vector<float>& getTrainingOutputs(const int index) override;
};
