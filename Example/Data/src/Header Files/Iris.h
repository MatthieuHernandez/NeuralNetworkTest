#pragma once
#include "DataForClassification.h"

class Iris final : public DataForClassification
{
public:
	Iris();
	~Iris() = default;

	void loadData() override;
};

