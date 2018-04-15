#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	cout << "STEP 00 finished : Start" << endl;
	this->initialize();
	cout << "STEP 01 finished : Initialize" << endl;

	displayImage(0);
	ui->comboBoxSet->addItem("Testing set");
	ui->comboBoxSet->addItem("Training set");
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::initialize()
{
	this->MNIST = data::create_MNIST();
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

void MainWindow::compute()
{
	this->initializeNeuralNetwork();


	auto clusteringRateMax = -1.0f;
	auto epochMax = 0;

	auto numberOfClockCycles = clock();
	for (int count = 1; ; count++)
	{

		for (int index = 0; index < MNIST.testing.size; index ++)
		{
			neuralNetwork->
				calculateClusteringRateForClassificationProblem(MNIST.testing.images[index], getLabel(index, testing));
		}
		const auto clusteringRate = neuralNetwork->getClusteringRate();
		if (clusteringRate > clusteringRateMax)
		{
			clusteringRateMax = clusteringRate;
			epochMax = count;
		}
		cout << "clustering rate : " << clusteringRate << " epoch : " << count << " time : " << (float)(clock() - numberOfClockCycles) /
			CLOCKS_PER_SEC << " secondes" << endl;
		numberOfClockCycles = clock();

		cout << "clustering rate max : " << clusteringRateMax << " epoch : " << epochMax << endl;
		clusteringRateVector.push_back(clusteringRate * 100);
		graphClusteringRate();
		ui->labelClusteringRateMax->setText(
			QString::fromStdString(
				(string)"Clustering max : " + data::to_string_with_precision(clusteringRateMax * 100, 2) + "%"));
		QApplication::processEvents();

		const int index_max = MNIST.trainig.size;

		for (int index = 0; index < index_max; index ++)
		{
			neuralNetwork->train(MNIST.trainig.images[index], MNIST.trainig.labels[index]);
			if (index % 1000 == 0)
			{
				ui->labelCount->setText(QString::fromStdString((string)"Count : " + to_string(index)));
				QApplication::processEvents();
			}
		}
		ui->labelCount->setText(QString::fromStdString((string)"Count : " + to_string(index_max)));
		QApplication::processEvents();
	}
}

void MainWindow::initializeNeuralNetwork()
{
	this->neuralNetwork = std::make_unique<NeuralNetwork>(
		vector<unsigned int>{static_cast<unsigned int>(MNIST.sizeOfImages), 150, 80, static_cast<unsigned int>(MNIST.numberOfLabel)},
		vector<activationFunction>{sigmoid, sigmoid, sigmoid}, 0.05f, 0.0f);

	if (neuralNetwork->isValid() != 0)
	{
		cout << "ERROR : " << neuralNetwork->getLastError() << endl;
		exit(0);
	}
	this->input.resize(MNIST.sizeOfImages);
	this->desired.resize(10);
}

void MainWindow::on_pushButton_clicked()
{
	compute();
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
