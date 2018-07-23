#include "DataVisualizationWidget.h"
#include "ui_DataVisualizationWidget.h"

using namespace std;

DataVisualizationWidget::DataVisualizationWidget(QWidget *parent, Controller *controller)
	: QWidget(parent), ui(new Ui::DataVisualizationWidget)
{
	ui->setupUi(this);
	this->controller = controller;

	ui->labelName->setText("");
	ui->labelDataSize->setText(QString::number(controller->getData().sizeOfData));
	ui->labelNumberOfLabel->setText(QString::number(controller->getData().numberOfLabel));
	ui->labelTrainingSetSize->setText(QString::number(controller->getData().sets[training].size));
	ui->labelTestingSetSize->setText(QString::number(controller->getData().sets[testing].size));
	
}