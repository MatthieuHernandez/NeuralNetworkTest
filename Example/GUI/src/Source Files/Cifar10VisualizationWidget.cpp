#include "Cifar10VisualizationWidget.h"
#include "ui_Cifar10Visualization.h"
#include <ui_ImageVisualizationWidget.h>

Cifar10VisualizationWidget::Cifar10VisualizationWidget(QWidget *parent, Controller *controller)
	: ImageVisualizationWidget(parent, controller), ui(new Ui::Cifar10Visualization)
{
	ui->setupUi(this);
	this->controller = controller;
	ImageVisualizationWidget::ui->Image->resize(320, 320);
	this->displayImage(0);
}

unsigned char Cifar10VisualizationWidget::getPixel(int number, int x, int y, color color) const
{
	return static_cast<unsigned char>((this->controller->getDataset().data->getData(displayedSet, number)[(y * 32 + x) +  color * 1024] + 1.0) * 127.4);
}