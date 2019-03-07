#pragma once

class DataSet
{
public:
	virtual ~DataSet() = default;
	virtual void loadData() = 0;
};
