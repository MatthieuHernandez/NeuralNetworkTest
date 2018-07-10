#include "MnistVisualization.h"
#include "ui_MnistVisualization.h"

MnistVisualization::MnistVisualization(QWidget *parent)
{
	ui = new Ui::MnistVisualization();
	ui->setupUi(this);
}

MnistVisualization::~MnistVisualization()
{
	delete ui;
}
