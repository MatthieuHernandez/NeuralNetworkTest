#include "ImageVisualizationWidget.h"
#include "ui_ImageVisualizationWidget.h"

ImageVisualizationWidget::ImageVisualizationWidget(QWidget* parent, Controller* controller)
	: DataVisualizationWidget(parent, controller), ui(new Ui::ImageVisualizationWidget)
{
	ui->setupUi(this);
}

void ImageVisualizationWidget::displayImage(int value)
{
	const int size = 28;
	const int multiple = 10;
	QImage picture(size, size, QImage::Format_RGB32);
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			picture.setPixel(x, y, qRgb(getPixel(value, x, y, red),
			                            getPixel(value, x, y, green),
			                            getPixel(value, x, y, blue)));
		}
	}
	const QImage scalePicture = picture.scaled(size * multiple, size * multiple, Qt::KeepAspectRatio);
	ui->Image->setPixmap(QPixmap::fromImage(scalePicture));

	const string label = static_cast<string>("Label : ") + to_string(
		this->controller->getDataset().data->getLabel(displayedSet, value));
	ui->labelImage->setText(QString::fromStdString(label));
}

void ImageVisualizationWidget::on_comboBoxSet_currentIndexChanged(int index)
{
	this->displayedSet = static_cast<snn::set>(index);
	ui->spinBoxImageId->setMaximum(this->controller->getDataset().data->sets[this->displayedSet].size - 1);
	ui->labelImage->setText("Label : " + QString::number(
		this->controller->getDataset().data->getTrainingLabel(ui->spinBoxImageId->value())));
	this->displayImage(ui->spinBoxImageId->value());
}

void ImageVisualizationWidget::on_spinBoxImageId_valueChanged(int value)
{
	this->displayImage(value);
}
