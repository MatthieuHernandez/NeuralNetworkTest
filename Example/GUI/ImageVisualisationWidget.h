#pragma once
#include <QWidget>
#include "Controller.h"

namespace Ui
{
	class ImageVisualisationWidget;
};

class ImageVisualisationWidget : public QWidget
{
Q_OBJECT

public:
	ImageVisualisationWidget(QWidget* parent);
	~ImageVisualisationWidget() = default;

protected :

	Ui::ImageVisualisationWidget* ui;

	Controller* controller;
	set displayedSet = testing;

	virtual unsigned char getImages(int number, int x, int y) = 0;
	void displayImage(int value);

	void on_comboBoxSet_currentIndexChanged(int index);
	void on_spinBoxImageId_valueChanged(int value);
};
