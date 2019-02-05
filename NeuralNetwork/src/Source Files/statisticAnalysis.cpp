#include "StatisticAnalysis.h"


StatisticAnalysis::StatisticAnalysis(int numberOfCluster)
{
	clusterClassifications.resize(numberOfCluster);
	this->startTesting();
}

void StatisticAnalysis::startTesting()
{
	for (auto cluster : clusterClassifications)
	{
		cluster.truePositive = 0;
		cluster.trueNegative = 0;
		cluster.falsePositive = 0;
		cluster.falseNegative = 0;
	}
}

float StatisticAnalysis::getClusteringRate() const
{
	float wellClassified = 0;
	float Total = 0;

	for (const auto cluster : clusterClassifications)
	{
		wellClassified += cluster.truePositive;
		wellClassified += cluster.trueNegative;
		Total += cluster.falsePositive;
		Total += cluster.falseNegative;
	}
	Total += wellClassified;

	return wellClassified / Total;
}

float StatisticAnalysis::getWeightedClusteringRate() const
{
	float weightedClusteringRate = 0;
	for (const auto cluster : clusterClassifications)
	{
		weightedClusteringRate += (cluster.truePositive + cluster.trueNegative) / (cluster.truePositive + cluster.
			trueNegative + cluster.falsePositive + cluster.falseNegative);
	}
	return weightedClusteringRate / clusterClassifications.size();
}

float StatisticAnalysis::getF1Score() const
{
	float f1Score = 0;

	for (const auto cluster : clusterClassifications)
	{
		const float precision = cluster.truePositive / (cluster.truePositive + cluster.falsePositive);
		const float recall = cluster.truePositive / (cluster.truePositive + cluster.falsePositive);
		f1Score += (precision * recall) / (precision + recall);
	}
	return 2.0f * f1Score / clusterClassifications.size();
}
