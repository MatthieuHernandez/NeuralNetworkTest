#pragma once
#include "gtest/gtest.h"
#include "CurrencyRatesEurToUsd.h"
#include "GTestTools.h"

using namespace std;

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

TEST_F(CurrencyTest, OutputTest)
{
	// Arrange
	int positifRates = 0;
	int negatifRates = 0;
	const int errorSize = 3;
	int error[errorSize] = {0};

	// Act
	for (int i = 0; i < data->sets[training].size; i++)
	{
		auto output = data->getTrainingOutputs(i)[0];

		if (output != data->getTestingOutputs(i)[0])
			error[0]++;

		if (output > 0 && output < 3)
			positifRates++;
		else if (output <= 0 && output > -3)
		{
			negatifRates++;
			if (output == 0)
				error[2]++;
		}

		else
			error[1]++;
	}
	const int totalRates = positifRates + negatifRates;
	const float positifRatesRatio = static_cast<float>(positifRates) / totalRates;
	const float negatifRatesRatio = static_cast<float>(negatifRates) / totalRates;

	const int DateToRemove = data->getNumberOfGaps() * data->numberOfInputRates;

	const int minRates = 371000 - DateToRemove;
	const int maxRates = 374000 - DateToRemove;

	// Assert
	EXPECT_ABOUT_EQ(400, data->getNumberOfGaps(), 500, "Number of gaps");
	EXPECT_ABOUT_EQ(minRates, totalRates, maxRates, "Total rates without gap");
	EXPECT_ABOUT_EQ(0.45f, positifRatesRatio, 0.55f, "Positif Ratio");
	EXPECT_ABOUT_EQ(0.45f, negatifRatesRatio, 0.55f, "Negatif Ratio");
	EXPECT_EQ(error[0], 0);
	EXPECT_EQ(error[1], 0);
	EXPECT_ABOUT_EQ(100, error[2], 10000, "Number of rates to 0");
}

TEST_F(CurrencyTest, InputTest)
{
	// Arrange
	const int errorSize = 3;
	int error[errorSize] = {0};

	// Act
	auto size = data->getTrainingData(0).size();

	for (int i = 0; i < data->sets[training].size; i++)
	{
		auto inputs = data->getTrainingData(i);

		if (inputs != data->getTestingData(i))
			error[0]++;

		for (int i = 0; i < inputs.size(); i++)
		{
			if (inputs[i] > 10 || inputs[i] < -10)
				error[1]++;
		}
		if (i + 1 < data->sets[training].size)
			if (inputs[12] == data->getTrainingData(i + 1)[11])
				error[2]++;
	}

	// Assert
	EXPECT_EQ(size, 21);
	EXPECT_EQ(error[0], 0);
	EXPECT_EQ(error[1], 0);
	EXPECT_EQ(error[2], 0);
}
