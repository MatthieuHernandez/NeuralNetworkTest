#include "StatisticAnalysis.h"


StatisticAnalysis::StatisticAnalysis(int numberOfCluster)
{
	clusters.resize(numberOfCluster);
	this->startTesting();
}

void StatisticAnalysis::startTesting()
{
	for (auto& c : clusters)
	{
		c.truePositive = 0;
		c.trueNegative = 0;
		c.falsePositive = 0;
		c.falseNegative = 0;
	}
}

void StatisticAnalysis::insertTestWithPrecision(std::vector<float>& outputs, std::vector<float>& desiredOutputs,
                                                float precision)
{
	for (int i = 0; i < clusters.size(); i++)
	{
		if (outputs[i] > separator && desiredOutputs[i] > separator)
		{
			clusters[i].truePositive ++;
		}
		else if (outputs[i] <= separator && desiredOutputs[i] <= separator)
		{
			clusters[i].trueNegative ++;
		}
		else if (outputs[i] > separator && desiredOutputs[i] <= separator)
		{
			clusters[i].falsePositive ++;
		}
		else if (outputs[i] <= separator && desiredOutputs[i] > separator)
		{
			clusters[i].falseNegative ++;
		}
	}
}

void StatisticAnalysis::insertTestWithSeparateByValue(std::vector<float>& outputs, std::vector<float>& desiredOutputs,
                                                      float separator)
{
	for (int i = 0; i < clusters.size(); i++)
	{
		if (outputs[i] > separator && desiredOutputs[i] > separator)
		{
			clusters[i].truePositive ++;
		}
		else if (outputs[i] <= separator && desiredOutputs[i] <= separator)
		{
			clusters[i].trueNegative ++;
		}
		else if (outputs[i] > separator && desiredOutputs[i] <= separator)
		{
			clusters[i].falsePositive ++;
		}
		else if (outputs[i] <= separator && desiredOutputs[i] > separator)
		{
			clusters[i].falseNegative ++;
		}
	}
}

float StatisticAnalysis::getClusteringRate() const
{
	float wellClassified = 0;
	float total = 0;

	for (const auto c : clusters)
	{
		wellClassified += c.truePositive;
		wellClassified += c.trueNegative;
		total += c.falsePositive;
		total += c.falseNegative;
	}
	total += wellClassified;

	return wellClassified / total;
}

float StatisticAnalysis::getWeightedClusteringRate() const
{
	float weightedClusteringRate = 0;
	for (const auto c : clusters)
	{
		weightedClusteringRate += (c.truePositive + c.trueNegative)
			/ (c.truePositive + c.trueNegative + c.falsePositive + c.falseNegative);
	}
	return weightedClusteringRate / clusters.size();
}

float StatisticAnalysis::getF1Score() const
{
	float f1Score = 0;

	for (const auto c : clusters)
	{
		const float precision = c.truePositive / (c.truePositive + c.falsePositive);
		const float recall = c.truePositive / (c.truePositive + c.falsePositive);
		f1Score += (precision * recall) / (precision + recall);
	}
	return 2.0f * f1Score / clusters.size();
}
