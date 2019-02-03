#include "StatisticAnalysis.h"



StatisticAnalysis::StatisticAnalysis()
{
	this->startTesting();
}

void StatisticAnalysis::startTesting()
{
}

float StatisticAnalysis::getClusteringRate() const
{
	return (this->truePositive + this->trueNegative)/(this->truePositive + this->trueNegative + this->falsePositive + this->falseNegative);
}

float StatisticAnalysis::getF1Score()
{
	const float precision = truePositive / (truePositive + falsePositive);
	const float recall = truePositive /  (truePositive + falsePositive);

	const float f1Score = 2 * (precision * recall) / ( precision + recall);

	return f1Score;
}

