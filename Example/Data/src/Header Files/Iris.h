#pragma once
#include "DataForClassification.h"

class Iris : public DataForClassification
{
public:
	Iris();
	~Iris();

	void loadData() override;
};

