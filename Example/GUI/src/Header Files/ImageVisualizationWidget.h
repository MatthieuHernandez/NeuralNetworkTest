#pragma once
#include "DataVisualizationWidget.h"

namespace Ui
{
	class ImageVisualizationWidget;
};

class ImageVisualizationWidget : public DataVisualizationWidget
{
Q_OBJECT

public:
	ImageVisualizationWidget(QWidget* parent, Controller *controller);
	~ImageVisualizationWidget() = default;

protected :

	Ui::ImageVisualizationWidget* ui;

	set displayedSet = testing;

	virtual unsigned char getImages(int number, int x, int y) = 0;
	void displayImage(int value);

	void on_comboBoxSet_currentIndexChanged(int index);
	void on_spinBoxImageId_valueChanged(int value);
};
