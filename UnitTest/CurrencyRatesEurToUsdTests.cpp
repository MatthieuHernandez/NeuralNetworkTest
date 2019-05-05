#pragma once
#include "CurrencyRatesEurToUsd.h"
#include "TestTools.h"
#include <gtest/gtest.h>
using namespace std;
using namespace snn;

class CurrencyTest : public testing::Test
{
protected:

	CurrencyTest()
	{
		data = new CurrencyRatesEurToUsd();
		data->path[0] = "../Example/Data/EURUSD/DAT_ASCII_EURUSD_M1_2016.csv";
		data->loadData();
	}

public:

	CurrencyRatesEurToUsd* data;
};

TEST_F(CurrencyTest, DISABLED_OutputTest)
{
	// Arrange
	int positiveRates = 0;
	int negativeRates = 0;
	const int errorSize = 3;
	int error[errorSize] = {0};

	// Act
	for (int i = 0; i < data->data->data->sets[training].size; i++)
	{
		auto output = data->data->data->getTrainingOutputs(i)[0];

		if (output != data->data->data->getTestingOutputs(i)[0])
			error[0]++;

		if (output > 0 && output < 3)
			positiveRates++;
		else if (output <= 0 && output > -3)
		{
			negativeRates++;
			if (output == 0)
				error[2]++;
		}

		else
			error[1]++;
	}
	const int totalRates = positiveRates + negativeRates;
	const float positiveRatesRatio = static_cast<float>(positiveRates) / totalRates;
	const float negativeRatesRatio = static_cast<float>(negativeRates) / totalRates;

	const int DateToRemove = data->getNumberOfGaps() * data->numberOfInputRates;

	const int minRates = 372000 - DateToRemove;
	const int maxRates = 373000 - DateToRemove;

	// Assert
	TestTools::EXPECT_ABOUT_EQ(300, data->getNumberOfGaps(), 400, "Number of gaps");
	TestTools::EXPECT_ABOUT_EQ(minRates, totalRates, maxRates, "Total rates without gap");
	TestTools::EXPECT_ABOUT_EQ(0.48f, positiveRatesRatio, 0.52f, "Positif Ratio");
	TestTools::EXPECT_ABOUT_EQ(0.48f, negativeRatesRatio, 0.52f, "Negatif Ratio");
	EXPECT_EQ(error[0], 0);
	EXPECT_EQ(error[1], 0);
	TestTools::EXPECT_ABOUT_EQ(100, error[2], 10000, "Number of rates to 0");
}

TEST_F(CurrencyTest, DISABLED_InputTest)
{
	// Arrange
	const int errorSize = 3;
	int error[errorSize] = {0};

	// Act
	auto sizeOfInput = data->data->data->getTrainingData(0).size();

	for (int i = 0; i < data->data->data->sets[training].size; i++)
	{
		auto inputs = data->data->data->getTrainingData(i);

		if (inputs != data->data->data->getTestingData(i))
			error[0]++;

		for (int j = 0; j < inputs.size(); j++)
		{
			if (inputs[j] > 10 || inputs[j] < -10)
				error[1]++;
		}
		const int k = 25;
		if (i + 1 < data->data->data->sets[training].size)
			if (data->data->data->getTrainingData(i)[k] != data->data->data->getTrainingData(i + 1)[k + 1])
				error[2]++;
	}

	const auto actualDataSize = data->data->data->sets[training].size;
	const auto expectedDataSize = data->getNumberOfLines() - data->getNumberOfGaps()*(data->numberOfInputRates) - sizeOfInput + 1;

	// Assert
	EXPECT_EQ(sizeOfInput, 66);
	EXPECT_EQ(actualDataSize, expectedDataSize);
	EXPECT_EQ(error[0], 0);
	EXPECT_EQ(error[1], 0);
	EXPECT_TRUE(error[2] < data->getNumberOfGaps()); // ??? Why ? But ok !
}
