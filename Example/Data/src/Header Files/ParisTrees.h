#pragma once
#include "DataForClassification.h"

class ParisTrees : public DataForClassification
{
public:
	ParisTrees();
	~ParisTrees();

	void loadData();
};
