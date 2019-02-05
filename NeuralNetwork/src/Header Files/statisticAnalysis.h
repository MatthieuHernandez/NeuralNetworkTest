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

	 std::vector<binaryClassification> clusters;

public:
	StatisticAnalysis(int numberOfCluster);
	virtual ~StatisticAnalysis() = default;

	void startTesting();
	void insertTestWithPrecision(std::vector<float>& outputs, std::vector<float>& desiredOutputs, float precision);
	void insertTestWithSeparateByValue(std::vector<float>& outputs, std::vector<float>& desiredOutputs, float separator);

	float getClusteringRate() const;
	float getWeightedClusteringRate() const;
	float getF1Score() const;
};
