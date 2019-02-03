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
	StatisticAnalysis();
	virtual ~StatisticAnalysis() = default;

	void startTesting();

	float getClusteringRate() const;
	float getF1Score();

	int getTruePositive() const { return this->truePositive; }
	int getTrueNegative() const { return this->trueNegative; }
	int getFalsePositive() const { return this->falsePositive; }
	int getFalseNegative() const { return this->falseNegative; }
};
