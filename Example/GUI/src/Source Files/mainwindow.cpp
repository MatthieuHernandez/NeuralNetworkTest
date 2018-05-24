#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qtconcurrentrun.h>
#include "ControllersManager.h"

using namespace std;

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	this->console = new Console();
	ui->comboBoxData->setCurrentIndex(0);

	connect(&watcherLoadingData, SIGNAL(finished()), this, SLOT(endOfLoadingData()));

	timerForCount = new QTimer(this);
	timerForTimeEdit = new QElapsedTimer();

	connect(&watcherCompute, SIGNAL(finished()), this, SLOT(stopCompute()));
	connect(timerForCount, SIGNAL(timeout()), this, SLOT(updateCount()));

	ui->tabWidgetData->setCurrentIndex(0);
	ui->tabWidgetNeuralNetwork->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
	computeIsStop = true;
	delete ui;
}

unsigned char MainWindow::getImages(int number, int x, int y)
{
	return (unsigned char)((this->manager.getController(indexMNIST)->getData().sets[displayedSet].data[number][y * 28 + x]
		+ 1.0) * 127.4);
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

	string label = (string)"Label : " + to_string(manager.getController(indexMNIST)->getData().getLabel(value, this->displayedSet));
	ui->labelImage->setText(QString::fromStdString(label));
		
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
	if (firstLoading)
	{
		connect(currentController, SIGNAL(updateNumberOfIteration()), this, SLOT(updateNumberOfIteration()));
		connect(currentController, SIGNAL(updateNumberOfIteration()), this, SLOT(updateGraphOfClusteringRate()));
		firstLoading = false;
	}
	this->InitializeButtons();
	this->ui->pushButtonCompute->setEnabled(true);
	this->write("data loaded");
	//if (ui->comboBoxData->currentIndex() == indexMNIST)
		//displayImage(ui->spinBoxImageId->value());
}

void MainWindow::InitializeButtons()
{
	this->ResetComboBoxlayer();
	this->InitializeLayerButtons(0);
	ui->spinBoxTrainingRating->setValue(this->currentController->inputs.numberOfTrainbyRating);
	ui->spinBoxTrainingRating->setMaximum(this->currentController->inputs.numberOfTrainbyRating);
};

void MainWindow::ResetComboBoxlayer()
{
	const int numberOfLayer = this->currentController->inputs.structure.size() - 1;
	ui->comboBoxLayer->clear();
	ui->comboBoxLayer->addItem("Input");
	for (int i = 0; i < numberOfLayer - 1; i++)
		ui->comboBoxLayer->addItem(QString::number(i));
	ui->comboBoxLayer->addItem("Ouput");
};

void MainWindow::InitializeLayerButtons(int layer)
{
	const int neuronsNumber = this->currentController->inputs.structure[layer];
	ui->spinBoxNeurons->setValue(neuronsNumber);

	int function = 0;
	if (layer > 0)
	{
		function = this->currentController->inputs.activationFunction[layer - 1];
		ui->comboBoxActivationfunction->show();
		if (this->currentController->inputs.structure.size() - 1 == layer)
			ui->spinBoxNeurons->setEnabled(false);
		else
			ui->spinBoxNeurons->setEnabled(true);
		ui->labelNeurons->setText("Neurons :");
	}
	else
	{
		ui->comboBoxActivationfunction->hide();
		ui->spinBoxNeurons->setEnabled(false);
		ui->labelNeurons->setText("Inputs :");
	}

	ui->comboBoxActivationfunction->setCurrentIndex(function + 1);
}

void MainWindow::initialiseInputs()
{
	float learningRate = 0.5f;
	float momentum = 0.0f;
	int numberOfTrainbyRating = ui->spinBoxTrainingRating->value();

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

	//this->currentController->inputs.structure = structure;
	//this->currentController->inputs.activationFunction = activationFunctions;
	//this->currentController->inputs.learningRate = learningRate;
	//this->currentController->inputs.momentum = momentum;
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
		timerForTimeEdit->start();
		ui->pushButtonCompute->setText("Stop");
		ui->timeEdit->setTime(QTime(0, 0));
	}
	else
	{
		stopCompute();
	}
}

void MainWindow::on_pushButtonConsole_clicked()
{
	console->show();
}

void MainWindow::on_pushButtonAddLayer_clicked()
{
	const int index = ui->comboBoxLayer->currentIndex();
	const auto it1 = this->currentController->inputs.structure.begin();
	const auto it2 = this->currentController->inputs.activationFunction.begin();
	const auto value = this->currentController->inputs.structure[index];
	this->currentController->inputs.structure.insert(it1 + index, value);
	const auto fuction = this->currentController->inputs.activationFunction[index];
	this->currentController->inputs.activationFunction.insert(it2 + index, fuction);
	this->ResetComboBoxlayer();
	this->InitializeLayerButtons(index + 1);
}

void MainWindow::on_pushButtonRemoveLayer_clicked()
{
	int index = ui->comboBoxLayer->currentIndex();
	if (index > 0 && index < this->currentController->inputs.structure.size() - 1)
	{
		ui->comboBoxLayer->removeItem(index);
		const auto it1 = this->currentController->inputs.structure.begin();
		const auto it2 = this->currentController->inputs.activationFunction.begin();
		this->currentController->inputs.structure.erase(it1 + index);
		this->currentController->inputs.activationFunction.erase(it2 + index);
		index = ui->comboBoxLayer->currentIndex();
		this->InitializeLayerButtons(index);
		this->ResetComboBoxlayer();
		this->InitializeLayerButtons(index);
	}
}

void MainWindow::on_comboBoxSet_currentIndexChanged(int index)
{
	if (index == training)
	{
		this->displayedSet = testing;
		ui->spinBoxImageId->setMaximum(9999);
		ui->labelImage->setText("Label : " + QString::number(
			manager.getController(indexMNIST)->getData().getTrainingLabel(ui->spinBoxImageId->value())));
	}
	if (index == testing)
	{
		this->displayedSet = training;
		ui->spinBoxImageId->setMaximum(59999);
		ui->labelImage->setText(
			QString::fromStdString(
				(string)"Label : " + to_string(
					manager.getController(indexMNIST)->getData().getTestingLabel(ui->spinBoxImageId->value()))));
	}
	displayImage(ui->spinBoxImageId->value());
}

void MainWindow::on_comboBoxLayer_currentIndexChanged(int index)
{
	if (index >= 0)
		this->InitializeLayerButtons(index);
}

void MainWindow::on_spinBoxNeurons_valueChanged(int value)
{
	int index = ui->comboBoxLayer->currentIndex();
	this->currentController->inputs.structure[index] = value;
}

void MainWindow::on_spinBoxImageId_valueChanged(int value)
{
	displayImage(value);
}

void MainWindow::on_spinBoxTrainingRating_valueChanged(int value)
{
	if (ui->spinBoxTrainingRating->value() == currentController->getData().sets[training].size)
		ui->labelMax->show();
	else
		ui->labelMax->hide();
}

void MainWindow::on_comboBoxData_currentIndexChanged(int index)
{
	this->write("loading ...");
	ui->pushButtonCompute->setEnabled(false);

	watcherLoadingData.setFuture(futureLoadingData);
	futureLoadingData = QtConcurrent::run([=]()
	{
		currentController = this->manager.getController(index);
	});

	ui->comboBoxLayer->setCurrentIndex(0);
	ui->spinBoxTrainingRating->setEnabled(false);
}

void MainWindow::updateGraphOfClusteringRate()
{
	this->currentController->blockSignals(true);
	auto CR = this->currentController->outputs.clusteringRate * 100.0f;
	auto CRM = this->currentController->outputs.clusteringRateMax * 100.0f;
	ui->doubleSpinBoxCR->setValue(CR);
	ui->doubleSpinBoxCRM->setValue(CRM);

	x.push_back(currentController->outputs.numberOfIteration);
	y.push_back(CR);

	ui->customPlot->graph(0)->setData(x, y);
	ui->customPlot->xAxis->setRange(0, y.size() - 1);
	ui->customPlot->replot();
	QApplication::processEvents();
	this->currentController->blockSignals(false);
}

void MainWindow::updateNumberOfIteration()
{
	this->currentController->blockSignals(true);
	ui->spinBoxIteration->setValue(currentController->outputs.numberOfIteration);
	QApplication::processEvents();
	this->currentController->blockSignals(false);
}

void MainWindow::updateCount()
{
	ui->timeEdit->setTime(QTime::fromMSecsSinceStartOfDay(static_cast<int>(timerForTimeEdit->elapsed())));
	ui->spinBoxCount->setValue(currentController->outputs.currentIndex);
}
