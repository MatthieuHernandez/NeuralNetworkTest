#include "mainChart.h"


MainChart::MainChart()
{
	this->chart = new QChart();
	this->axisY = new QValueAxis();
	this->chart->addAxis(axisY, Qt::AlignLeft);
	this->axisY->setRange(0, 100);

	this->clusteringRates = new QLineSeries();
	this->clusteringRates->setName("clustering rates");
	this->clusteringRates->setColor(Qt::blue);
	this->chart->addSeries(this->clusteringRates);
	this->clusteringRates->attachAxis(this->axisY);

	this->weightedClusteringRates = new QLineSeries();
	this->weightedClusteringRates->setName("weighted clustering rates");
	this->weightedClusteringRates->setColor(Qt::red);
	this->chart->addSeries(this->weightedClusteringRates);
	this->weightedClusteringRates->attachAxis(this->axisY);

	this->f1Scores = new QLineSeries();
	this->f1Scores->setName("F1 scores");
	this->f1Scores->setColor(Qt::green);
	this->chart->addSeries(this->f1Scores);
	this->f1Scores->attachAxis(this->axisY);
}

void MainChart::clear()
{
	this->clusteringRates->clear();
	this->weightedClusteringRates->clear();
	this->f1Scores->clear();
}

void MainChart::updateLineSeries(float x, float clusteringRate, float weightedClusteringRate, float f1Score)
{
	if (this->previousAxisXValue < x)
	{
		this->previousAxisXValue = x;
		this->clusteringRates->append(QPointF(x, clusteringRate));
		this->weightedClusteringRates->append(QPointF(x, weightedClusteringRate));
		this->f1Scores->append(QPointF(x, f1Score));
	}
}
