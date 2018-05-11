#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qtconcurrentrun.h>
#include <qpen.h>
#include "MNIST.h"
#include "ControllersManager.h"

using namespace std;

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	this->console = new Console();

	ui->spinBoxNeurons->setValue(0);
	this->on_comboBoxData_currentIndexChanged(0);

	connect(&watcherCompute, SIGNAL(finished()), this, SLOT(stopCompute()));
	connect(&watcherLoadingData, SIGNAL(finished()), this, SLOT(endOfLoadingData()));

	timerForCount = new QTimer(this);
	connect(timerForCount, SIGNAL(timeout()), this, SLOT(updateCount()));
}

MainWindow::~MainWindow()
{
	delete ui;
}

unsigned char MainWindow::getImages(int number, int x, int y)
{
	if (displayedSet == testing)
		return (unsigned char)((this->manager.getController(indexMNIST)->getData().sets[testing].data[number][y * 28 + x] +
				1.0
			) *
			127.4);
	else
		return (unsigned char)((this->manager.getController(indexMNIST)->getData().sets[training].data[number][y * 28 + x] +
				1.0)
			* 127.4);
}

void MainWindow::write(const string text, bool onlyConsole)
{
	if (onlyConsole)
		ui->lineEditInformation->setText(QString::fromStdString(text));
	console->write(text);
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

void MainWindow::startLoadingLogo()
{
	if (loadingLogo == nullptr)
	{
		loadingLogo = new QMovie("./Extra Files/loading.gif");
		loadingLogo->setScaledSize(QSize(50, 50));
	}

	if (!loadingLogo->isValid())
		write("[ERROR] Loading picture failed");
	ui->labelLoading->setMovie(loadingLogo);
	loadingLogo->start();
}

void MainWindow::stopCompute()
{
	computeIsStop = true;
	loadingLogo->stop();
	timerForCount->stop();
	ui->pushButtonCompute->setText("Compute");
}

void MainWindow::endOfLoadingData()
{
	const int neuronsNumber = this->currentController->inputs.structure[0];
	ui->spinBoxNeurons->setValue(neuronsNumber);

	const int function = this->currentController->inputs.structure[0];
	ui->comboBoxActivationfunction->setCurrentIndex(function);

	const int numberOfLayer = this->currentController->inputs.structure.size() - 1;
	ui->comboBoxLayer->clear();
	ui->comboBoxLayer->addItem("Input");
	for (int i = 0; i < numberOfLayer; i++)
	{
		ui->comboBoxLayer->addItem(QString::number(i));
	}
	ui->comboBoxLayer->addItem("Ouput");

	if(firstLoading)
	{
		connect(currentController, SIGNAL(updateNumberOfIteration()), this, SLOT(updateNumberOfIteration()));
		connect(currentController, SIGNAL(updateNumberOfIteration()), this, SLOT(updateGraphOfClusteringRate()));
		firstLoading = false;
	}

	this->ui->pushButtonCompute->setEnabled(true);
	this->write("data loaded");

}

int MainWindow::getLabel(int value, set displayedSet)
{
	for (int i = 0; i > 10; i++)
	{
		if (this->manager.getController(indexMNIST)->getData().sets[displayedSet].labels[value][i] == 1) return i;
	}
	return -1;
}

void MainWindow::initialiseInputs()
{
	float learningRate = 0.5f;
	float momentum = 0.0f;
	int numberOfTrainbyRating = this->currentController->getData().sets[training].size;

	vector<uint> structure;
	for (int i = 0; i < ui->comboBoxLayer->count(); i++)
	{
		uint value = (uint)ui->comboBoxLayer->itemText(i).toInt();
		structure.push_back(value);
	}

	vector<activationFunction> activationFunctions;
	for (int i = 0; i < ui->comboBoxActivationfunction->count(); i++)
	{
		const string text = ui->comboBoxActivationfunction->itemText(i).toStdString();

		if (text == "Sigmoid")
			activationFunctions.push_back(sigmoid);
		else if (text == "TanH")
			activationFunctions.push_back(tanH);
		else if (text == "ReLU")
			activationFunctions.push_back(reLU);
		else if (text == "Gaussian")
			activationFunctions.push_back(gaussian);
		else
			throw exception();
	}
	this->currentController->inputs.structure = structure;
	this->currentController->inputs.activationFunction = activationFunctions;
	this->currentController->inputs.learningRate = learningRate;
	this->currentController->inputs.momentum = momentum;
	this->currentController->inputs.numberOfTrainbyRating = numberOfTrainbyRating;
}

void MainWindow::resetGraphOfClusteringRate()
{
	x.clear();
	y.clear();

	ui->customPlot->addGraph();
	ui->customPlot->addGraph();
	ui->customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
	ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
	// first graph will be filled with translucent blue
	ui->customPlot->graph(1)->setPen(QPen(Qt::red));
	connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
	connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));
	ui->customPlot->yAxis->setRange(0, 100); // (0, 100)
	ui->customPlot->replot();
}

/**************************************************
 *				  	    SLOTS				  	  *
 **************************************************/

void MainWindow::on_pushButtonCompute_clicked()
{
	if (computeIsStop)
	{
		this->initialiseInputs();
		this->currentController->initializeNeuralNetwork();
		this->resetGraphOfClusteringRate();
		computeIsStop = false;
		this->startLoadingLogo();
		auto future = QtConcurrent::run([=]()
		{
			currentController->compute(&computeIsStop);
		});
		watcherCompute.setFuture(future);
		timerForCount->start(250);
		ui->pushButtonCompute->setText("Stop");
	}
	else
	{
		stopCompute();
	}
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

void MainWindow::on_spinBoxImageId_valueChanged(int value)
{
	displayImage(value);
}

void MainWindow::on_pushButtonConsole_clicked()
{
	console->show();
}

void MainWindow::on_comboBoxData_currentIndexChanged(int index)
{
	this->write("loading ...");
	this->ui->pushButtonCompute->setEnabled(false);

	auto future = QtConcurrent::run([=]()
	{
		currentController = this->manager.getController(index);
	});
	watcherLoadingData.setFuture(future);

	ui->comboBoxLayer->setCurrentIndex(0);
}

void MainWindow::updateGraphOfClusteringRate()
{
	x.push_back(currentController->outputs.numberOfIteration);
	y.push_back(currentController->outputs.clusteringRate);

	ui->customPlot->graph(0)->setData(x, y);
	ui->customPlot->xAxis->setRange(0, y.size() - 1);
	ui->customPlot->replot();
}

void MainWindow::updateNumberOfIteration()
{
	ui->lineEditIteration->setText(QString::number(currentController->outputs.numberOfIteration));
}

void MainWindow::updateCount()
{
	ui->lineEditCount->setText(QString::number(currentController->outputs.currentIndex));
}

