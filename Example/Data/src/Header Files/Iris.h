#pragma once
#include "DataSet.h"

class Iris final : public DataSet
{
public:
	Iris();
	void loadData() override;
};
