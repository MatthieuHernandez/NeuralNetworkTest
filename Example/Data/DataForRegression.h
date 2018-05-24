#pragma once
#include "Data.h"

class DataForRegression : public Data
{
public:

	DataForRegression();
	std::vector<float>& getTestingOutputs(const int index) override;
	void loadData() override = 0;
};

