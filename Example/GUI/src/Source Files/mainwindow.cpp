#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qtconcurrentrun.h>
#include "DataManager.h"

using namespace std;

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent),
	  ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	this->console = new Console();
	ui->comboBoxData->setCurrentIndex(0);
	ui->layout->addWidget(new QWidget);

	connect(&watcherLoadingData, SIGNAL(finished()), this, SLOT(endOfLoadingDataSet()));

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

void MainWindow::write(const string text, bool onlyConsole)
{
	if (onlyConsole)
		ui->lineEditInformation->setText(QString::fromStdString(text));
	console->write(text);
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

void MainWindow::endOfLoadingDataSet()
{
	if (firstLoading)
	{
		initializeGraphOfClusteringRate();
		firstLoading = false;
	}
	connect(currentController, SIGNAL(updateNumberOfIteration()), this, SLOT(updateNumberOfIteration()));
	connect(currentController, SIGNAL(updateNumberOfIteration()), this, SLOT(updateGraphOfClusteringRate()));

	this->InitializeButtons();
	ui->pushButtonCompute->setEnabled(true);

	const auto widget = this->manager.getWidget(indexController);
	ui->layout->itemAt(0)->widget()->hide();
	ui->layout->replaceWidget(ui->layout->itemAt(0)->widget(), widget);
	widget->show();

	ui->tabWidgetNeuralNetwork->setEnabled(true);
	ui->comboBoxData->setEnabled(true);
	this->write("data loaded");
}

void MainWindow::InitializeButtons()
{
	this->ResetComboBoxlayer();
	this->InitializeLayerButtons(0);
	ui->spinBoxTrainingRating->setMaximum(this->currentController->inputs.numberOfTrainbyRating);
	ui->spinBoxTrainingRating->setValue(this->currentController->inputs.numberOfTrainbyRating);
};

void MainWindow::ResetComboBoxlayer()
{
	ui->comboBoxLayer->blockSignals(true);
	ui->comboBoxLayer->clear();
	ui->comboBoxLayer->addItem("Input");
	const int numberOfLayer = static_cast<int>(this->currentController->inputs.structure.size()) - 1;
	for (int i = 0; i < numberOfLayer - 1; i++)
		ui->comboBoxLayer->addItem(QString::number(i));
	ui->comboBoxLayer->addItem("Ouput");
	ui->comboBoxLayer->blockSignals(false);
	ui->comboBoxLayer->setCurrentIndex(0);
};

void MainWindow::InitializeLayerButtons(const int layer)
{
	const int neuronsNumber = this->currentController->inputs.structure[layer];
	ui->spinBoxNeurons->setValue(neuronsNumber);


	if (layer > 0)
	{
		auto function = static_cast<int>(this->currentController->inputs.activationFunction[layer - 1]);
		ui->comboBoxActivationFunction->blockSignals(true);
		ui->comboBoxActivationFunction->setCurrentIndex(function);
		ui->comboBoxActivationFunction->blockSignals(false);
		ui->comboBoxActivationFunction->show();
		if (this->currentController->inputs.structure.size() - 1 == layer)
			ui->spinBoxNeurons->setEnabled(false);
		else
			ui->spinBoxNeurons->setEnabled(true);
		ui->labelNeurons->setText("Neurons :");
	}
	else
	{
		ui->comboBoxActivationFunction->hide();
		ui->spinBoxNeurons->setEnabled(false);
		ui->labelNeurons->setText("Inputs :");
	}

	ui->spinBoxLearningRate->setValue(this->currentController->inputs.learningRate);
	ui->spinBoxMomentum->setValue(this->currentController->inputs.momentum);
}

void MainWindow::initializeInputs()
{
	const float learningRate = ui->spinBoxLearningRate->value();
	const float momentum = ui->spinBoxMomentum->value();
	const int numberOfTrainbyRating = ui->spinBoxTrainingRating->value();

	this->currentController->inputs.learningRate = learningRate;
	this->currentController->inputs.momentum = momentum;
	this->currentController->inputs.numberOfTrainbyRating = numberOfTrainbyRating;
}

void MainWindow::initializeGraphOfClusteringRate()
{
	x.clear();
	y.clear();

	ui->customPlot->addGraph();
	ui->customPlot->graph(0)->setPen(QPen(Qt::blue));
	ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
	ui->customPlot->yAxis->setRange(0, 100);
	ui->customPlot->replot();
	updateGraphOfClusteringRate();
}

void MainWindow::resetGraphOfClusteringRate()
{
	x.clear();
	y.clear();
	this->refreshGraphOfClusteringRate();
}

void MainWindow::refreshGraphOfClusteringRate()
{
	ui->customPlot->graph(0)->setData(x, y);
	ui->customPlot->xAxis->setRange(0, currentController->outputs.numberOfIteration);
	ui->customPlot->replot();
}

/**************************************************
 *				  	    SLOTS				  	  *
 **************************************************/

void MainWindow::on_pushButtonCompute_clicked()
{
	if (computeIsStop)
	{
		this->initializeInputs();
		this->currentController->initializeNeuralNetwork();
		this->resetGraphOfClusteringRate();
		computeIsStop = false;
		this->startLoadingLogo();
		const auto future = QtConcurrent::run([=]()
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
	console->activateWindow();
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

void MainWindow::on_comboBoxLayer_currentIndexChanged(int index)
{
	this->InitializeLayerButtons(index);
}

void MainWindow::on_comboBoxActivationFunction_currentIndexChanged(int index)
{
	auto layer = ui->comboBoxLayer->currentIndex();
	auto function = static_cast<activationFunctionType>(index);
	this->currentController->inputs.activationFunction[layer - 1] = function;
}

void MainWindow::on_spinBoxNeurons_valueChanged(int value)
{
	int index = ui->comboBoxLayer->currentIndex();
	this->currentController->inputs.structure[index] = value;
}

void MainWindow::on_spinBoxLearningRate_valueChanged(double value)
{
	currentController->inputs.learningRate = value;
}

void MainWindow::on_spinBoxMomentum_valueChanged(double value)
{
	currentController->inputs.momentum = value;
}

void MainWindow::on_spinBoxTrainingRating_valueChanged(int value)
{
	currentController->inputs.numberOfTrainbyRating = value;

	if (ui->spinBoxTrainingRating->value() == currentController->getData().sets[training].size)
		ui->labelMax->show();
	else
		ui->labelMax->hide();
}

void MainWindow::on_comboBoxData_currentIndexChanged(int index)
{
	this->write("loading ...");
	indexController = index;
	ui->pushButtonCompute->setEnabled(false);
	ui->comboBoxData->setEnabled(false);
	ui->tabWidgetNeuralNetwork->setEnabled(false);

	const QFuture<void> futureLoadingData = QtConcurrent::run([=]()
	{
		currentController = this->manager.getController(indexController);
	});

	watcherLoadingData.setFuture(futureLoadingData);
	ui->spinBoxTrainingRating->setEnabled(true);
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
	this->refreshGraphOfClusteringRate();
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
