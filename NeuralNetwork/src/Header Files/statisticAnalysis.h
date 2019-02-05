#pragma once
#include <vector>
class StatisticAnalysis
{
private:
	float previousClusteringRate{};

protected:

	struct binaryClassification
	{
		float truePositive{};
		float trueNegative{};
		float falsePositive{};
		float falseNegative{};
	};

	 std::vector<binaryClassification> clusterClassifications;

public:
	StatisticAnalysis(int numberOfCluster);
	virtual ~StatisticAnalysis() = default;

	void startTesting();

	float getClusteringRate() const;
	float getWeightedClusteringRate() const;
	float getF1Score() const;
};
