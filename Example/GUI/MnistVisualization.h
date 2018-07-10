#pragma once
#include <DataVisualisationWidget.h>

namespace Ui
{
	class MnistVisualization;
};

class MnistVisualization : public DataVisualisationWidget
{

public:
	MnistVisualization(QWidget *parent = Q_NULLPTR);
	~MnistVisualization();

private:
	Ui::MnistVisualization *ui;
};
