#include "MnistVisualization.h"
#include "ui_MnistVisualization.h"
#include "DataManager.h"

using namespace std;

MnistVisualization::MnistVisualization(QWidget *parent, Controller *controller)
	: ui(new Ui::MnistVisualization)
{ 
	ui->setupUi(this);
	this->controller = controller;
}

unsigned char MnistVisualization::getImages(int number, int x, int y)
{
	return static_cast<unsigned char>((this->controller->getData().getData(displayedSet, number)[y * 28 + x] + 1.0) * 127.4);
}

void MnistVisualization::displayImage(int value)
{
	const int size = 28;
	const int multiple = 10;
	QImage picture(size, size, QImage::Format_RGB32);
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			picture.setPixel(x, y, qRgb(getImages(value, x, y),
			                            getImages(value, x, y),
			                            getImages(value, x, y)));
		}
	}
	const QImage scalePicture = picture.scaled(size * multiple, size * multiple, Qt::KeepAspectRatio);
	ui->Image->setPixmap(QPixmap::fromImage(scalePicture));

	const string label = static_cast<string>("Label : ") + to_string(this->controller->getData().getLabel(displayedSet, value));
	ui->labelImage->setText(QString::fromStdString(label));
}

/**************************************************
 *				  	    SLOTS				  	  *
 **************************************************/

void MnistVisualization::on_comboBoxSet_currentIndexChanged(int index)
{
	if (index == training)
	{
		this->displayedSet = training;
		ui->spinBoxImageId->setMaximum(9999);
		ui->labelImage->setText("Label : " + QString::number(
			this->controller->getData().getTrainingLabel(ui->spinBoxImageId->value())));
	}
	if (index == testing)
	{
		this->displayedSet = testing;
		ui->spinBoxImageId->setMaximum(59999);
		ui->labelImage->setText(
			QString::fromStdString(
				static_cast<string>("Label : ") + to_string(
					this->controller->getData().getTestingLabel(ui->spinBoxImageId->value()))));
	}
	this->displayImage(ui->spinBoxImageId->value());
}

void MnistVisualization::on_spinBoxImageId_valueChanged(int value)
{
	displayImage(value);
}