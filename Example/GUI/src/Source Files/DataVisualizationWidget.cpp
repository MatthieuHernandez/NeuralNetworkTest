#include "DataVisualizationWidget.h"
#include "ui_DataVisualizationWidget.h"

using namespace snn;

DataVisualizationWidget::DataVisualizationWidget(QWidget *parent, Controller *controller)
	: QWidget(parent), ui(new Ui::DataVisualizationWidget)
{
	ui->setupUi(this);
	this->controller = controller;

	ui->labelName->setText("");
	ui->labelDataSize->setText(QString::number(controller->getDataset().data->sizeOfData));
	ui->labelNumberOfLabel->setText(QString::number(controller->getDataset().data->numberOfLabel));
	ui->labelTrainingSetSize->setText(QString::number(controller->getDataset().data->sets[training].size));
	ui->labelTestingSetSize->setText(QString::number(controller->getDataset().data->sets[testing].size));
	
}