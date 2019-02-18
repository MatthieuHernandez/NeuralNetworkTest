#pragma once
#include "DataForClassification.h"

class Wine final : public DataForClassification
{
public:
	Wine();
	~Wine() = default;

	void loadData() override;
};
