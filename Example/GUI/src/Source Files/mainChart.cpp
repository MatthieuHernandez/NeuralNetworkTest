#include "mainChart.h"


MainChart::MainChart()
{
	this->chart = new QChart();
	this->chart->legend()->hide();
	this->axisX = new QValueAxis();
	this->axisY = new QValueAxis();

	this->chart->addAxis(axisY, Qt::AlignLeft);
	this->chart->addAxis(axisX, Qt::AlignBottom);
	this->axisX->setRange(0, 1000);
	this->axisY->setRange(0, 100);

	this->clusteringRates = new QLineSeries(this->chart);
	this->clusteringRates->setName("clustering rates");
	this->clusteringRates->setColor(Qt::blue);
	this->chart->addSeries(this->clusteringRates);
	this->clusteringRates->attachAxis(this->axisY);

	this->weightedClusteringRates = new QLineSeries(this->chart);
	this->weightedClusteringRates->setName("weighted clustering rates");
	this->weightedClusteringRates->setColor(Qt::red);
	this->chart->addSeries(this->weightedClusteringRates);
	this->weightedClusteringRates->attachAxis(this->axisY);

	this->f1Scores = new QLineSeries(this->chart);
	this->f1Scores->setName("F1 scores");
	this->f1Scores->setColor(Qt::green);
	this->chart->addSeries(this->f1Scores);
	this->f1Scores->attachAxis(this->axisY);

	this->clusteringRates->setUseOpenGL(true);
	this->weightedClusteringRates->setUseOpenGL(true);
	this->f1Scores->setUseOpenGL(true);
}

void MainChart::clear()
{
	printf("not Weird\n");
	this->clusteringRates->clear();
	this->weightedClusteringRates->clear();
	this->f1Scores->clear();
}

void MainChart::updateLineSeries(float x, float clusteringRate, float weightedClusteringRate, float f1Score)
{
	if (this->previousAxisXValue < x)
	{
		printf("Weird\n");
		this->previousAxisXValue = x;
		this->clusteringRates->append(QPointF(x, static_cast<float>(clusteringRate) * 100.0f));
		this->weightedClusteringRates->append(QPointF(x, static_cast<float>(weightedClusteringRate) * 100.0f));
		this->f1Scores->append(QPointF(x, static_cast<float>(f1Score) * 100.0f));

		this->chart->removeAllSeries();
		this->chart->addSeries(this->clusteringRates);
		this->chart->addSeries(this->weightedClusteringRates);
		this->chart->addSeries(this->f1Scores);
	}
}
