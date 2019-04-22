#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qtconcurrentrun.h>
#include "DataManager.h"
using namespace std;
using namespace snn;

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent),
	  ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	this->console = new Console();
	ui->comboBoxData->setCurrentIndex(0);
	ui->layout->addWidget(new QWidget);

	connect(&watcherLoadingData, SIGNAL(finished()), this, SLOT(endOfLoadingDataSet()));

	updateTimer = new QTimer(this);
	timerForTimeEdit = new QElapsedTimer();

	connect(&watcherCompute, SIGNAL(finished()), this, SLOT(stopCompute()));

	connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateInterface()));

	ui->tabWidgetData->setCurrentIndex(0);
	ui->tabWidgetNeuralNetwork->setCurrentIndex(0);

	this->mainChart = new MainChart();
	ui->chartView->setChart(this->mainChart->getChart());
	ui->chartView->setRenderHint(QPainter::Antialiasing);

	this->enableModification(true);
}

MainWindow::~MainWindow()
{
	this->computeIsStop = true;
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
	if (this->loadingLogo == nullptr)
	{
		this->loadingLogo = new QMovie("./Extra Files/loading.gif");
		this->loadingLogo->setScaledSize(QSize(50, 50));
	}

	if (!loadingLogo->isValid())
		write("[ERROR] Loading picture failed");
	ui->labelLoading->setMovie(loadingLogo);
	loadingLogo->start();
}

void MainWindow::stopCompute()
{
	this->currentController->getNeuralNetwork().trainingStop();
	this->computeIsStop = true;
	this->loadingLogo->stop();
	this->updateTimer->stop();
	this->updateInterface();
	ui->pushButtonResetGraph->setEnabled(true);
	this->enableModification(true);
	ui->pushButtonCompute->setText("Compute");
}

void MainWindow::endOfLoadingDataSet()
{
	if (firstLoading)
	{
		firstLoading = false;
	}

	this->initializeButtons();
	this->on_pushButtonResetGraph_clicked();
	ui->pushButtonCompute->setEnabled(true);

	const auto widget = this->manager.getWidget(indexController);
	ui->layout->itemAt(0)->widget()->hide();
	ui->layout->replaceWidget(ui->layout->itemAt(0)->widget(), widget);
	widget->show();

	ui->tabWidgetNeuralNetwork->setEnabled(true);
	this->enableModification(true);
	this->write("data loaded");
}

void MainWindow::initializeButtons()
{
	this->resetComboBoxLayer();
	this->initializeLayerButtons(0);
	ui->spinBoxTrainingRating->setMaximum(this->currentController->inputs.numberOfTrainingsBetweenTwoEvaluations);
	ui->spinBoxTrainingRating->setValue(this->currentController->inputs.numberOfTrainingsBetweenTwoEvaluations);
};

void MainWindow::resetComboBoxLayer() const
{
	ui->comboBoxLayer->blockSignals(true);
	ui->comboBoxLayer->clear();
	ui->comboBoxLayer->addItem("Input");
	const int numberOfLayer = static_cast<int>(this->currentController->inputs.structure.size()) - 1;
	for (int i = 0; i < numberOfLayer - 1; i++)
		ui->comboBoxLayer->addItem(QString::number(i));
	ui->comboBoxLayer->addItem("Output");
	ui->comboBoxLayer->blockSignals(false);
	ui->comboBoxLayer->setCurrentIndex(0);
};

void MainWindow::initializeLayerButtons(const int layer) const
{
	const int neuronsNumber = this->currentController->inputs.structure[layer];
	ui->spinBoxNeurons->setValue(neuronsNumber);


	if (layer > 0)
	{
		const auto function = static_cast<int>(this->currentController->inputs.activationFunction[layer - 1]);
		ui->comboBoxActivationFunction->blockSignals(true);
		ui->comboBoxActivationFunction->setCurrentIndex(function);
		ui->comboBoxActivationFunction->blockSignals(false);
		ui->comboBoxActivationFunction->show();
		if (this->currentController->inputs.structure.size() - 1 == layer || !computeIsStop)
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

void MainWindow::refreshClusteringRate() const
{
	ui->doubleSpinBoxCR->setValue(this->currentController->getNeuralNetwork().getGlobalClusteringRate() * 100.0f);
	/////ui->doubleSpinBoxCRM->setValue(this->currentController->getNeuralNetwork()->clusteringRateMax * 100.0f);
	ui->doubleSpinBoxWCR->setValue(this->currentController->getNeuralNetwork().getWeightedClusteringRate() * 100.0f);
	ui->doubleSpinBoxF1S->setValue(this->currentController->getNeuralNetwork().getF1Score() * 100.0f);
}

void MainWindow::enableModification(const bool isEnable) const
{
	ui->comboBoxData->setEnabled(isEnable);
	ui->pushButtonReset->setEnabled(isEnable);
	ui->pushButtonLoad->setEnabled(isEnable);
	ui->pushButtonSave->setEnabled(isEnable);
	ui->pushButtonEvaluate->setEnabled(isEnable);
	ui->pushButtonAddLayer->setEnabled(isEnable);
	ui->pushButtonRemoveLayer->setEnabled(isEnable);
	ui->spinBoxNeurons->setEnabled(isEnable);
	ui->comboBoxActivationFunction->setEnabled(isEnable);
	ui->spinBoxLearningRate->setEnabled(isEnable);
	ui->spinBoxMomentum->setEnabled(isEnable);
}

/**************************************************
 *				  	    SLOTS				  	  *
 **************************************************/

void MainWindow::on_pushButtonCompute_clicked()
{
	if (computeIsStop)
	{
		computeIsStop = false;
		this->mainChart->clear();
		if (&currentController->getNeuralNetwork() == nullptr)
		{
			this->on_pushButtonResetGraph_clicked();
			this->currentController->initializeNeuralNetwork();
			this->refreshClusteringRate();
			ui->spinBoxCount->setValue(this->currentController->getNeuralNetwork().getCurrentIndex());
			ui->spinBoxIteration->setValue(this->currentController->getNeuralNetwork().getNumberOfIteration());
		}
		this->startLoadingLogo();
		this->enableModification(false);
		QString data = ui->comboBoxData->currentText();

		currentController->getNeuralNetwork().trainingStart(*currentController->getData().data);

		updateTimer->start(40);
		timerForTimeEdit->start();
		ui->pushButtonResetGraph->setEnabled(false);
		ui->pushButtonCompute->setText("Stop");
		ui->timeEdit->setTime(QTime(0, 0));
	}
	else
	{
		stopCompute();
	}
}

void MainWindow::on_pushButtonEvaluate_clicked()
{
	if (computeIsStop)
	{
		computeIsStop = false;
		if (&currentController->getNeuralNetwork() == nullptr)
		{
			this->on_pushButtonResetGraph_clicked();
			this->currentController->initializeNeuralNetwork();
			this->refreshClusteringRate();
			ui->spinBoxCount->setValue(this->currentController->getNeuralNetwork().getCurrentIndex());
			ui->spinBoxIteration->setValue(this->currentController->getNeuralNetwork().getNumberOfIteration());
		}
		this->startLoadingLogo();

		currentController->getNeuralNetwork().evaluate(*currentController->getData().data);

		updateTimer->start(40);
		timerForTimeEdit->start();
		ui->pushButtonCompute->setText("Stop");
		ui->timeEdit->setTime(QTime(0, 0));
	}
}

void MainWindow::on_pushButtonConsole_clicked()
{
	console->show();
	console->activateWindow();
}

void MainWindow::on_pushButtonResetGraph_clicked()
{
	this->mainChart->clear();
	ui->pushButtonResetGraph->setEnabled(false);
}

void MainWindow::on_pushButtonAddLayer_clicked()
{
	const int index = ui->comboBoxLayer->currentIndex();
	const auto it1 = this->currentController->inputs.structure.begin();
	const auto it2 = this->currentController->inputs.activationFunction.begin();
	const auto value = this->currentController->inputs.structure[index];
	this->currentController->inputs.structure.insert(it1 + index, value);
	const auto function = this->currentController->inputs.activationFunction[index];
	this->currentController->inputs.activationFunction.insert(it2 + index, function);
	this->resetComboBoxLayer();
	this->initializeLayerButtons(index + 1);
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
		this->initializeLayerButtons(index);
		this->resetComboBoxLayer();
		this->initializeLayerButtons(index);
	}
}

void MainWindow::on_comboBoxLayer_currentIndexChanged(int index)
{
	this->initializeLayerButtons(index);
}

void MainWindow::on_comboBoxActivationFunction_currentIndexChanged(int index)
{
	auto layer = ui->comboBoxLayer->currentIndex();
	auto function = static_cast<activationFunctionType>(index);
	this->currentController->inputs.activationFunction[layer - 1] = function;
}

void MainWindow::on_checkBoxAutoSave_stateChanged(int state)
{
	if (state == 2)
	{
		this->autoSave = true;
		console->write("auto save enable");
		return;
	}
	this->autoSave = false;
	console->write("auto save disable");
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
	currentController->getNeuralNetwork().setNumberOfTrainingsBetweenTwoEvaluations(value);

	if (ui->spinBoxTrainingRating->value() == currentController->getData().data->data->sets[training].size)
		ui->labelMax->show();
	else
		ui->labelMax->hide();
}

void MainWindow::on_comboBoxData_currentIndexChanged(int index)
{
	this->write("loading ...");
	indexController = index;
	this->enableModification(false);
	ui->spinBoxTrainingRating->setEnabled(true);
	ui->tabWidgetNeuralNetwork->setEnabled(false);
	const QFuture<void> futureLoadingData = QtConcurrent::run([=]()
	{
		currentController = this->manager.getController(indexController);
	});
	watcherLoadingData.setFuture(futureLoadingData);
}

void MainWindow::on_pushButtonReset_clicked()
{
	this->currentController->DeleteNeuralNetwork();
	this->enableModification(true);
	ui->spinBoxCount->setValue(this->currentController->getNeuralNetwork().getCurrentIndex());
	ui->spinBoxIteration->setValue(this->currentController->getNeuralNetwork().getNumberOfIteration());
	this->refreshClusteringRate();
	this->on_pushButtonResetGraph_clicked();
}

void MainWindow::on_pushButtonSave_clicked()
{
	if (this->currentController->getNeuralNetwork().getGlobalClusteringRate() <= 0)
	{
		QMessageBox::warning(this, tr("Save Neural Network"), tr("Cannot save a neural network having never learned"),
		                     QMessageBox::Ok);
		return;
	}

	QString data = ui->comboBoxData->currentText();
	QString clustering_rate = QString::number(this->currentController->getNeuralNetwork().getGlobalClusteringRate());
	QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd");
	QString fileName = "./Save/" + data + "_" + clustering_rate + "_" + date;
	fileName = QFileDialog::getSaveFileName(this,
	                                        tr("Save Neural Network"), fileName,
	                                        tr("Binary (*.bin);;All Files (*)"));
	this->currentController->save(fileName);
}

void MainWindow::on_pushButtonLoad_clicked()
{
	QString fileName = "./Save/";
	fileName = QFileDialog::getOpenFileName(this,
	                                        tr("Save Neural Network"), fileName,
	                                        tr("Binary (*.bin);;All Files (*)"));
	if (fileName != nullptr)
	{
		this->currentController->load(fileName);
		this->on_pushButtonResetGraph_clicked();
		this->refreshClusteringRate();
	}
}

void MainWindow::updateInterface()
{
	this->refreshClusteringRate();

	ui->spinBoxIteration->setValue(this->currentController->getNeuralNetwork().getNumberOfIteration());	
	ui->timeEdit->setTime(QTime::fromMSecsSinceStartOfDay(static_cast<int>(timerForTimeEdit->elapsed())));
	ui->spinBoxCount->setValue(this->currentController->getNeuralNetwork().getCurrentIndex());

	this->mainChart->updateLineSeries(
		this->currentController->getNeuralNetwork().getNumberOfIteration(),
		this->currentController->getNeuralNetwork().getGlobalClusteringRate(),
		this->currentController->getNeuralNetwork().getWeightedClusteringRate(),
		this->currentController->getNeuralNetwork().getF1Score()
	);
}
