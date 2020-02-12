#include "MainChart.h"


MainChart::MainChart()
{
	QPen a(Qt::blue, 1.5, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
	QPen b(Qt::red, 1.5, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
	QPen c(Qt::green, 1.5, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);

	this->chart = new QChart();
	this->chart->legend()->hide();
	this->chart->createDefaultAxes();

	this->clusteringRateSeries = new QLineSeries(this->chart);
	this->clusteringRateSeries->setName("clustering rates");
	this->clusteringRateSeries->setPen(a);
	this->chart->addSeries(this->clusteringRateSeries);

	this->weightedClusteringRateSeries = new QLineSeries(this->chart);
	this->weightedClusteringRateSeries->setName("weighted clustering rates");
	this->weightedClusteringRateSeries->setPen(b);
	this->chart->addSeries(this->weightedClusteringRateSeries);

	this->f1ScoreSeries = new QLineSeries(this->chart);
	this->f1ScoreSeries->setName("F1 scores");
	this->f1ScoreSeries->setPen(c);
	this->chart->addSeries(this->f1ScoreSeries);

	this->axisX = new QValueAxis();
	this->axisY = new QValueAxis();
	this->axisX->setRange(0, 2);
	this->axisY->setRange(0, 100);
	this->axisX->setLabelFormat("%i");
	this->axisY->setLabelFormat("%i");
	this->chart->setAxisX(this->axisX, this->clusteringRateSeries);
	this->chart->setAxisY(this->axisY, this->clusteringRateSeries);
	this->chart->setAxisX(this->axisX, this->weightedClusteringRateSeries);
	this->chart->setAxisY(this->axisY, this->weightedClusteringRateSeries);
	this->chart->setAxisX(this->axisX, this->f1ScoreSeries);
	this->chart->setAxisY(this->axisY, this->f1ScoreSeries);

	this->clusteringRateSeries->setUseOpenGL(true);
	this->weightedClusteringRateSeries->setUseOpenGL(true);
	this->f1ScoreSeries->setUseOpenGL(true);
}

void MainChart::clear()
{
	this->previousAxisXValue = 0;
	this->clusteringRatePoints.clear();
	this->clusteringRatePoints.push_back(QPointF(0, 0));
	this->weightedClusteringRatePoints.clear();
	this->weightedClusteringRatePoints.push_back(QPointF(0, 0));
	this->f1ScorePoints.clear();
	this->f1ScorePoints.push_back(QPointF(0, 0));

	this->clusteringRateSeries->replace(clusteringRatePoints);
	this->weightedClusteringRateSeries->replace(weightedClusteringRatePoints);
	this->f1ScoreSeries->replace(f1ScorePoints);
}

void MainChart::updateLineSeries(float x, float clusteringRate, float weightedClusteringRate, float f1Score)
{
	if (this->previousAxisXValue != x
		|| (this->previousAxisXValue == 0 || clusteringRate != 0))
	{
		this->previousAxisXValue = x;

		this->clusteringRatePoints.push_back(QPointF(x, clusteringRate * 100.0f));
		this->weightedClusteringRatePoints.push_back(QPointF(x, weightedClusteringRate * 100.0f));
		this->f1ScorePoints.push_back(QPointF(x, f1Score * 100.0f));

		this->clusteringRateSeries->replace(clusteringRatePoints);
		this->weightedClusteringRateSeries->replace(weightedClusteringRatePoints);
		this->f1ScoreSeries->replace(f1ScorePoints);

		this->axisX->setRange(0, x);
	}
}
