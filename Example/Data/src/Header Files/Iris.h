#pragma once
#include "DataForClassification.h"

class Iris : public DataForClassification
{
public:
	Iris();
	~Iris() = default;

	void loadData() override;
};

