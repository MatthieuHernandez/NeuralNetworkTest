#pragma once
#include "data/StraightforwardData.h"

class DataSet
{
public:

	snn::StraightforwardData *data;

	int sizeOfData;
	int numberOfLabel;
	int sizeOfTrainingSet;
	int sizeOfTestingSet;

	DataSet() = default;
	virtual ~DataSet() = default;
	virtual void loadData() = 0;
};