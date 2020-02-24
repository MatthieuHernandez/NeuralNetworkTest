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
	unsigned char getPixel(int number, int x, int y, color color) const override;
};
