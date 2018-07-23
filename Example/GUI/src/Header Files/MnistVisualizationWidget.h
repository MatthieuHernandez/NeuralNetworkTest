#pragma once
#include "Controller.h"
#include "ImageVisualizationWidget.h"

namespace Ui
{
	class MnistVisualization;
};

class MnistVisualizationWidget : public ImageVisualizationWidget
{
Q_OBJECT

public:

	MnistVisualizationWidget(QWidget* parent, Controller* controller);
	~MnistVisualizationWidget() = default;


private:

	Ui::MnistVisualization* ui;

	unsigned char getImages(int number, int x, int y) override;


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
