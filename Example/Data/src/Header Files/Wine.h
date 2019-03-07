#pragma once
#include "DataSet.h"

class Wine final : public DataSet
{
public:
	Wine();
	~Wine() = default;

	void loadData() override;
};
