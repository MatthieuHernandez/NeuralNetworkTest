#include "MnistVisualizationWidget.h"
#include "ui_MnistVisualization.h"
#include "DataManager.h"
#include <ui_ImageVisualizationWidget.h>

using namespace std;

MnistVisualizationWidget::MnistVisualizationWidget(QWidget *parent, Controller *controller)
	: ImageVisualizationWidget(parent, controller), ui(new Ui::MnistVisualization)
{ 
	
	ui->setupUi(this);
	this->controller = controller;
	ImageVisualizationWidget::ui->Image->resize(280, 280);
}

unsigned char MnistVisualizationWidget::getImages(int number, int x, int y)
{
	return static_cast<unsigned char>((this->controller->getData().getData(displayedSet, number)[y * 28 + x] + 1.0) * 127.4);
}