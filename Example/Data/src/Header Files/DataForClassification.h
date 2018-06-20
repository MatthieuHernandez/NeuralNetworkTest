#pragma once
#include "Data.h"

class DataForClassification : public Data
{
public:

	DataForClassification();
	int getLabel(const int index, set set);
	int getTrainingLabel(const int index);
	int getTestingLabel(const int index);
	void loadData() override = 0;
};

