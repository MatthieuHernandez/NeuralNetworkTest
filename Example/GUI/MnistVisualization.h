#pragma once
#include "Controller.h"
#include "ImageVisualisationWidget.h"
#include <qaccessiblebridge.h>

namespace Ui
{
	class MnistVisualization;
};

class MnistVisualization : public ImageVisualisationWidget
{
Q_OBJECT

public:

	MnistVisualization(QWidget* parent, Controller* controller);
	~MnistVisualization() = default;


private:

	Ui::MnistVisualization* ui;

	unsigned char getImages(int number, int x, int y) override;


private slots:

	void on_comboBoxSet_currentIndexChanged(int index)
	{
		ImageVisualisationWidget::on_comboBoxSet_currentIndexChanged(index);
	}

	void on_spinBoxImageId_valueChanged(int value)
	{
	 	ImageVisualisationWidget::on_spinBoxImageId_valueChanged(value);
	}
};
