#include "MnistVisualization.h"
#include "ui_MnistVisualization.h"
#include "DataManager.h"
#include <ui_ImageVisualisationWidget.h>

using namespace std;

MnistVisualization::MnistVisualization(QWidget *parent, Controller *controller)
	: ImageVisualisationWidget(parent), ui(new Ui::MnistVisualization)
{ 
	
	ui->setupUi(this);
	this->controller = controller;
	ImageVisualisationWidget::ui->Image->resize(280, 280);
}

unsigned char MnistVisualization::getImages(int number, int x, int y)
{
	return static_cast<unsigned char>((this->controller->getData().getData(displayedSet, number)[y * 28 + x] + 1.0) * 127.4);
}