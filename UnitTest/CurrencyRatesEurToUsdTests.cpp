#pragma once
#include "gtest/gtest.h"
#include "CurrencyRatesEurToUsd.h"
#include "GTestTools.h"

TEST(CurrencyTest, OutputHasGoodValue)
{
	// Arrange
	auto* data = new CurrencyRatesEurToUsd();
	data->path[0] = "../Example/Data/EURUSD/DAT_ASCII_EURUSD_M1_2016.csv";
	data->loadData();
	int positifRates = 0;
	int negatifRates = 0;
	const int errorSize = 2;
	int error[errorSize] = {0};

	// Act
	for (int i = 0; i < data->sets[training].size; i++)
	{
		auto rate = data->getTrainingOutputs(i)[0];

		if (rate != data->getTestingOutputs(i)[0])
			error[1]++;

		if (rate > 0 && rate < 3)
			positifRates++;
		else if (rate <= 0 && rate > -3)
			negatifRates++;
		else
			error[0]++;
	}
	const int totalRates = positifRates + negatifRates;

	// Assert
	EXPECT_ABOUT_EQ(372000, totalRates, 373000);
	EXPECT_ABOUT_EQ(0.45f, static_cast<float>(positifRates) / totalRates, 0.55f);
	EXPECT_ABOUT_EQ(0.45f, static_cast<float>(negatifRates) / totalRates, 0.55f);
	EXPECT_TRUE(error[0] == 0);
	EXPECT_TRUE(error[1] == 0);
}

TEST(CurrencyTest, InputHasGoodValue)
{
	throw std::exception();
}