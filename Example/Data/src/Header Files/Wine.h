#pragma once
#include "DataSet.h"

class Wine final : public DataSet
{
public:
	Wine();
	void loadData() override;
};
