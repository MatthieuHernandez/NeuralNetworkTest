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
	this->enableModification(true);
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
	this->refreshClusteringRate();
	ui->pushButtonResetGraph->setEnabled(true);
	this->enableModification(true);
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
	ui->spinBoxTrainingRating->setMaximum(this->currentController->inputs.numberOfTrainbyRating);
	ui->spinBoxTrainingRating->setValue(this->currentController->inputs.numberOfTrainbyRating);
};

void MainWindow::resetComboBoxLayer() const
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

void MainWindow::refreshGraphOfClusteringRate() const
{
	ui->customPlot->graph(0)->setData(x, y);
	ui->customPlot->xAxis->setRange(0, y.empty() ? 1 : y.size() - 1);
	ui->customPlot->replot();
}

void MainWindow::refreshClusteringRate() const
{
	auto CR = this->currentController->outputs.clusteringRate * 100.0f;
	auto CRM = this->currentController->outputs.clusteringRateMax * 100.0f;
	ui->doubleSpinBoxCR->setValue(CR);
	ui->doubleSpinBoxCRM->setValue(CRM);
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
		if (&currentController->getNeuralNetwork() == nullptr)
		{
			this->on_pushButtonResetGraph_clicked();
			this->currentController->initializeNeuralNetwork();
			this->refreshClusteringRate();
			ui->spinBoxCount->setValue(currentController->outputs.currentIndex);
			ui->spinBoxIteration->setValue(currentController->outputs.numberOfIteration);
		}
		this->startLoadingLogo();
		this->enableModification(false);
		QString data = ui->comboBoxData->currentText();
		const auto future = QtConcurrent::run([=]()
		{
			currentController->compute(&this->computeIsStop, &this->autoSave, data);
		});
		watcherCompute.setFuture(future);
		timerForCount->start(250);
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
			ui->spinBoxCount->setValue(currentController->outputs.currentIndex);
			ui->spinBoxIteration->setValue(currentController->outputs.numberOfIteration);
		}
		this->startLoadingLogo();
		const auto future = QtConcurrent::run([=]()
		{
			currentController->evaluate(&this->computeIsStop);
		});
		watcherCompute.setFuture(future);
		timerForCount->start(250);
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
	x.clear();
	y.clear();
	ui->pushButtonResetGraph->setEnabled(false);
	this->refreshGraphOfClusteringRate();
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
	if(state == 2)
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
	ui->spinBoxCount->setValue(currentController->outputs.currentIndex);
	ui->spinBoxIteration->setValue(currentController->outputs.numberOfIteration);
	this->refreshClusteringRate();
	this->on_pushButtonResetGraph_clicked();
}

void MainWindow::on_pushButtonSave_clicked()
{
	if (currentController->outputs.clusteringRate <= 0)
	{
		QMessageBox::warning(this, tr("Save Neural Network"), tr("Cannot save a neural network having never learned"),
		                     QMessageBox::Ok);
		return;
	}

	QString data = ui->comboBoxData->currentText();
	QString clustering_rate = QString::number(currentController->outputs.clusteringRate);
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

void MainWindow::updateGraphOfClusteringRate()
{
	this->currentController->blockSignals(true);
	this->refreshClusteringRate();
	x.push_back(y.size());
	y.push_back(ui->doubleSpinBoxCR->value());
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
