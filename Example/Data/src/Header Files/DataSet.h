#pragma once
#include "data/Data.hpp"

class DataSet
{
public:

	snn::Data *data{};

	int sizeOfData{};
	int numberOfLabel{};
	int sizeOfTrainingSet{};
	int sizeOfTestingSet{};

	DataSet() = default;
	virtual ~DataSet() = default;
	virtual void loadData() = 0;
};
