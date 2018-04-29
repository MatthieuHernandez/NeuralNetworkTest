#pragma once
#include "Data.h"

class Iris : public Data
{
public:
	Iris();
	~Iris();

	void loadData() override;
};

