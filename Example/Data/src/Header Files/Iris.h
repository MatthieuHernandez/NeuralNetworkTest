#pragma once
#include "DataSet.h"

class Iris final : public DataSet
{
public:
	Iris();
	~Iris() = default;

	void loadData() override;
};

