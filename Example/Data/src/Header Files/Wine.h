#pragma once
#include "DataForClassification.h"

class Wine : public DataForClassification
{
public:
	Wine();
	~Wine() = default;

	void loadData() override;
};
