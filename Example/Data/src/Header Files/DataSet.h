#pragma once
#include "StraightforwardData.h"

class DataSet
{
public:

	snn::StraightforwardData *data;

	int sizeOfData;
	int numberOfLabel;
	int sizeOfTrainingSet;
	int sizeOfTestingSet;

	DataSet();
	virtual ~DataSet() = default;
	virtual void loadData() = 0;
};
