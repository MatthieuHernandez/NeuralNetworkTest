#pragma once
#include "Controller.h"
#include "ImageVisualizationWidget.h"

namespace Ui
{
	class Cifar10Visualization;
};

class Cifar10VisualizationWidget : public ImageVisualizationWidget
{
Q_OBJECT

public:
	Cifar10VisualizationWidget(QWidget* parent, Controller* controller);
	~Cifar10VisualizationWidget() = default;

private:
	Ui::Cifar10Visualization* ui;

	unsigned char getPixel(int number, int x, int y, color color) const override;

private slots:
	void on_comboBoxSet_currentIndexChanged(int index)
	{
		ImageVisualizationWidget::on_comboBoxSet_currentIndexChanged(index);
	}

	void on_spinBoxImageId_valueChanged(int value)
	{
		ImageVisualizationWidget::on_spinBoxImageId_valueChanged(value);
	}
};
