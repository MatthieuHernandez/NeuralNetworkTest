#pragma once
#include <QWidget>
#include "Controller.h"

namespace Ui
{
	class DataVisualizationWidget;
};

class DataVisualizationWidget : public QWidget
{
Q_OBJECT

public:
	DataVisualizationWidget(QWidget* parent, Controller* controller);
	~DataVisualizationWidget() = default;

protected:

	Ui::DataVisualizationWidget* ui;
	Controller* controller;
};
