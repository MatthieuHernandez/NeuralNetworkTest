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

	std::vector<std::vector<float>> dateTimes;
	std::vector<float> rates;
	std::vector<float>& getDateTimeFromLine(std::string& line);


public:

	CurrencyRatesEurToUsd();
	~CurrencyRatesEurToUsd();

	void loadData() override;

	std::vector<float>& getTrainingData(int index);
	std::vector<float>& getTestingData(int index);

};
