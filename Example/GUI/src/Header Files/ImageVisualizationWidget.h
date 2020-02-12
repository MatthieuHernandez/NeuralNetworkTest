#pragma once
#include "DataVisualizationWidget.h"
#include "data/Data.hpp"

namespace Ui
{
	class ImageVisualizationWidget;
};

enum color
{
	red,
	green,
	blue
};

class ImageVisualizationWidget : public DataVisualizationWidget
{
Q_OBJECT

public:
	ImageVisualizationWidget(QWidget* parent, Controller* controller);
	~ImageVisualizationWidget() = default;

protected :
	Ui::ImageVisualizationWidget* ui;

	snn::set displayedSet = snn::testing;

	virtual unsigned char getPixel(int number, int x, int y, color color) const = 0;
	void displayImage(int value);

	void on_comboBoxSet_currentIndexChanged(int index);
	void on_spinBoxImageId_valueChanged(int value);
};
