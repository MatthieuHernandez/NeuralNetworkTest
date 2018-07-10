#pragma once
#include <QWidget>

class DataVisualisationWidget : public QWidget
{
Q_OBJECT

public:
	DataVisualisationWidget(QWidget *parent = Q_NULLPTR);
	~DataVisualisationWidget();

private:
	DataVisualisationWidget* ui;
};
