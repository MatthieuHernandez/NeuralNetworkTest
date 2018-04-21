#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->lineEditInformation->setText("loading ...");
	this->controller = new Controller();
	this->controller->initialize();
	QTimer::singleShot(200, this, SLOT(this->controller->initialize()));
	ui->lineEditInformation->setText("data loaded");
}

MainWindow::~MainWindow()
{
	delete ui;
}

unsigned char MainWindow::getImages(int number, int x, int y)
{
	if (displayedSet == testing)
		return (unsigned char)((this->MNIST.testing.images[number][y * 28 + x] + 1.0) * 127.4);
	else
		return (unsigned char)((this->MNIST.trainig.images[number][y * 28 + x] + 1.0) * 127.4);
}

void MainWindow::on_spinBoxImageId_valueChanged(int value)
{
	displayImage(value);
}

void MainWindow::displayImage(int value)
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
	QImage scalePicture = picture.scaled(size * multiple, size * multiple, Qt::KeepAspectRatio);
	ui->Image->setPixmap(QPixmap::fromImage(scalePicture));

	if (displayedSet == training)
		ui->labelImage->setText(QString::fromStdString((string)"Label : " + to_string(getLabel(value, this->displayedSet))));
	else
		ui->labelImage->setText(QString::fromStdString((string)"Label : " + to_string(getLabel(value, this->displayedSet))));
}

int MainWindow::getLabel(int value, DisplayedSet displayedSet)
{
	if (displayedSet == training)
	{
		if (this->MNIST.trainig.labels[value][0] == 1) return 0;
		if (this->MNIST.trainig.labels[value][1] == 1) return 1;
		if (this->MNIST.trainig.labels[value][2] == 1) return 2;
		if (this->MNIST.trainig.labels[value][3] == 1) return 3;
		if (this->MNIST.trainig.labels[value][4] == 1) return 4;
		if (this->MNIST.trainig.labels[value][5] == 1) return 5;
		if (this->MNIST.trainig.labels[value][6] == 1) return 6;
		if (this->MNIST.trainig.labels[value][7] == 1) return 7;
		if (this->MNIST.trainig.labels[value][8] == 1) return 8;
		if (this->MNIST.trainig.labels[value][9] == 1) return 9;
		return -1;
	}

	if (this->MNIST.testing.labels[value][0] == 1) return 0;
	if (this->MNIST.testing.labels[value][1] == 1) return 1;
	if (this->MNIST.testing.labels[value][2] == 1) return 2;
	if (this->MNIST.testing.labels[value][3] == 1) return 3;
	if (this->MNIST.testing.labels[value][4] == 1) return 4;
	if (this->MNIST.testing.labels[value][5] == 1) return 5;
	if (this->MNIST.testing.labels[value][6] == 1) return 6;
	if (this->MNIST.testing.labels[value][7] == 1) return 7;
	if (this->MNIST.testing.labels[value][8] == 1) return 8;
	if (this->MNIST.testing.labels[value][9] == 1) return 9;
	return -1;
}

void MainWindow::on_pushButton_clicked()
{
	QTimer::singleShot(200, this, SLOT(this->controller->compute()));
}

void MainWindow::on_comboBoxSet_currentIndexChanged(int index)
{
	if (index == 0)
	{
		this->displayedSet = testing;
		ui->spinBoxImageId->setMaximum(9999);
		ui->labelImage->setText(
			QString::fromStdString(
				(string)"Label : " + to_string(getLabel(ui->spinBoxImageId->value(), this->displayedSet))));
	}
	if (index == 1)
	{
		this->displayedSet = training;
		ui->spinBoxImageId->setMaximum(59999);
		ui->labelImage->setText(
			QString::fromStdString(
				(string)"Label : " + to_string(getLabel(ui->spinBoxImageId->value(), this->displayedSet))));
	}

	displayImage(ui->spinBoxImageId->value());
}

void MainWindow::on_pushButtonConsole_clicked()
{
}

void MainWindow::graphClusteringRate()
{
	QApplication::processEvents();
	if (flag_graph)
	{
		ui->custom_plot->addGraph();
		ui->custom_plot->addGraph();
		ui->custom_plot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
		ui->custom_plot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
		// first graph will be filled with translucent blue
		ui->custom_plot->graph(1)->setPen(QPen(Qt::red));
		connect(ui->custom_plot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->custom_plot->xAxis2, SLOT(setRange(QCPRange)));
		connect(ui->custom_plot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->custom_plot->yAxis2, SLOT(setRange(QCPRange)));
		ui->custom_plot->yAxis->setRange(0, 100); // (0, 100)
		flag_graph = false;
	}
	// make left and bottom axes always transfer their ranges to right and top axes:
	x.clear();
	for (auto i = 0; i < clusteringRateVector.size(); i++)
	{
		x.push_back(i);
	}
	ui->custom_plot->graph(0)->setData(x, clusteringRateVector);
	ui->custom_plot->xAxis->setRange(0, clusteringRateVector.size() - 1);
	ui->custom_plot->replot();
}
