#pragma once
class StatisticAnalysis
{
public:
	StatisticAnalysis();
	virtual ~StatisticAnalysis() = default;

	void startTesting();

	float getClusteringRate();
	float getF1Score();
};

