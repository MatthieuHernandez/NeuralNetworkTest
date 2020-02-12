#include "MnistVisualizationWidget.h"
#include "ui_MnistVisualization.h"
#include <ui_ImageVisualizationWidget.h>

using namespace std;

MnistVisualizationWidget::MnistVisualizationWidget(QWidget *parent, Controller *controller)
	: ImageVisualizationWidget(parent, controller), ui(new Ui::MnistVisualization)
{ 
	
	ui->setupUi(this);
	this->controller = controller;
	ImageVisualizationWidget::ui->Image->resize(280, 280);
}

unsigned char MnistVisualizationWidget::getPixel(int number, int x, int y, color) const
{
	return static_cast<unsigned char>((this->controller->getDataset().data->getData(displayedSet, number)[y * 28 + x] + 1.0) * 127.4);
}