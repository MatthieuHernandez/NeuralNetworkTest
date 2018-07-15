#pragma once
#include <DataVisualisationWidget.h>
#include "Data.h"
#include "Controller.h"

namespace Ui
{
	class MnistVisualization;
};

class MnistVisualization : public DataVisualisationWidget
{
Q_OBJECT

public:

	MnistVisualization(QWidget* parent, Controller* controller);
	~MnistVisualization() = default;


private:

	Ui::MnistVisualization *ui;

	Controller* controller;
	
	set displayedSet = testing;

	
	unsigned char getImages(int number, int x, int y);
	void displayImage(int value);


private slots:

	void on_comboBoxSet_currentIndexChanged(int index);
	void on_spinBoxImageId_valueChanged(int value);
};
