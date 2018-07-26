#pragma once
#include "Controller.h"
#include "ImageVisualizationWidget.h"

namespace Ui
{
	class Cifar10Visualization;
};

class Cifar10Visualization : public ImageVisualizationWidget
{
Q_OBJECT

public:

	Cifar10Visualization(QWidget* parent, Controller* controller);
	~Cifar10Visualization() = default;

private:

	Ui::Cifar10Visualization* ui;

	unsigned char getImages(int number, int x, int y);
};