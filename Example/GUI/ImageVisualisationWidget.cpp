#include "ImageVisualisationWidget.h"
#include "ui_ImageVisualisationWidget.h"

using namespace std;

ImageVisualisationWidget::ImageVisualisationWidget(QWidget *parent)
	: QWidget(parent), ui(new Ui::ImageVisualisationWidget)
{
	ui->setupUi(this);
}

void ImageVisualisationWidget::displayImage(int value)
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

void ImageVisualisationWidget::on_comboBoxSet_currentIndexChanged(int index)
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

void ImageVisualisationWidget::on_spinBoxImageId_valueChanged(int value)
{
	this->displayImage(value);
}
