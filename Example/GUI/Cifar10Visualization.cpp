#include "Cifar10Visualization.h"
#include "ui_Cifar10Visualization.h"
#include <QWidget>
#include "Controller.h"

using namespace std;

Cifar10Visualization::Cifar10Visualization(QWidget *parent, Controller *controller)
	: ui(new Ui::Cifar10Visualization), ImageVisualisationWidget(parent)
{
	ui->setupUi(this);
	this->controller = controller;
}

unsigned char Cifar10Visualization::getImages(int number, int x, int y)
{
	return static_cast<unsigned char>((this->controller->getData().getData(displayedSet, number)[y * 28 + x] + 1.0) * 127.4);
}