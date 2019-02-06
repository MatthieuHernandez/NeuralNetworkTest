#pragma once
#include <vector>
class StatisticAnalysis
{
private:
	//float previousClusteringRate{};

	struct binaryClassification
	{
		float truePositive{};
		float trueNegative{};
		float falsePositive{};
		float falseNegative{};
	};

	 std::vector<binaryClassification> clusters;

	 float numberOfDataWellClassified{};
	 float numberOfDataMisclassified{};

public:
	StatisticAnalysis(int numberOfCluster);
	virtual ~StatisticAnalysis() = default;

	void startTesting();
	void insertTestWithPrecision(const std::vector<float>& outputs, const std::vector<float>& desiredOutputs, float precision);
	void insertTestSeparateByValue(const std::vector<float>& outputs, const std::vector<float>& desiredOutputs, float separator);
	void insertTestWithClassNumber(const std::vector<float>& outputs, int classNumber);

	float getGlobalClusteringRate() const;
	float getWeightedClusteringRate() const;
	float getF1Score() const;
};