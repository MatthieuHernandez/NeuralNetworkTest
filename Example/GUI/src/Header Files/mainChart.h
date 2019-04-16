#pragma once
#include <QtCharts>

QT_CHARTS_USE_NAMESPACE

class MainChart
{
public:
	MainChart();
	~MainChart() = default;

	void clear();
	void updateLineSeries(float x, float clusteringRate, float weightedClusteringRate, float f1Score);

	QChart* getChart() const { return this->chart; }

private:

	float previousAxisXValue = 0.0f;

	QChart* chart{};

	QValueAxis* axisX{};
	QValueAxis* axisY{};

	QLineSeries* clusteringRates{};
	QLineSeries* weightedClusteringRates{};
	QLineSeries* f1Scores{};
};
