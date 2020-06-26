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
    this->currentController->getNeuralNetwork().stopTraining();
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
        firstLoading = false;

    this->initializeButtons();
    this->on_pushButtonResetGraph_clicked();

    const auto widget = this->manager.getWidget(indexController);
    ui->layout->itemAt(0)->widget()->hide();
    ui->layout->replaceWidget(ui->layout->itemAt(0)->widget(), widget);
    widget->show();

    ui->tabWidgetNeuralNetwork->setEnabled(true);
    this->enableModification(true);
    this->write("data loaded");
    ui->pushButtonCompute->setEnabled(true);
}

void MainWindow::initializeButtons()
{
    this->resetComboBoxLayer();
    this->initializeLayerButtons(0);
    // TODO: to rework
    //ui->spinBoxTrainingRating->setMaximum(this->currentController->inputs.numberOfTrainingsBetweenTwoEvaluations);
    //ui->spinBoxTrainingRating->setValue(this->currentController->inputs.numberOfTrainingsBetweenTwoEvaluations);
};

void MainWindow::resetComboBoxLayer() const
{
    ui->comboBoxLayer->blockSignals(true);
    ui->comboBoxLayer->clear();
    ui->comboBoxLayer->addItem("Input");
    const int numberOfLayer = this->currentController->inputs.structure.size();
    for (int i = 0; i < numberOfLayer - 2; i++)
        ui->comboBoxLayer->addItem(QString::number(i));
    ui->comboBoxLayer->addItem("Output");
    ui->comboBoxLayer->blockSignals(false);
    ui->comboBoxLayer->setCurrentIndex(0);
};

void MainWindow::initializeLayerButtons(const int layer) const
{
    if (layer == 0)
    {
        const int neuronsNumber = this->currentController->inputs.structure[layer].numberOfInputs;
        ui->comboBoxActivationFunction->hide();
        ui->spinBoxNeurons->setEnabled(false);
        ui->labelNeurons->setText("Inputs :");
        ui->spinBoxNeurons->setValue(neuronsNumber);
    }
    else
    {
        const int neuronsNumber = this->currentController->inputs.structure[layer].numberOfNeurons;
        const auto function = static_cast<int>(this->currentController->inputs.structure[layer].activation);
        ui->comboBoxActivationFunction->blockSignals(true);
        ui->comboBoxActivationFunction->setCurrentIndex(function);
        ui->comboBoxActivationFunction->blockSignals(false);
        ui->comboBoxActivationFunction->show();
        if (this->currentController->inputs.structure.size() == layer || !computeIsStop)
            ui->spinBoxNeurons->setEnabled(false);
        else
            ui->spinBoxNeurons->setEnabled(true);
        ui->labelNeurons->setText("Neurons :");
        ui->spinBoxNeurons->setValue(neuronsNumber);
    }

    ui->spinBoxLearningRate->setValue(this->currentController->inputs.learningRate);
    ui->spinBoxMomentum->setValue(this->currentController->inputs.learningRate);
}

void MainWindow::refreshClusteringRate() const
{
    ui->doubleSpinBoxCR->setValue(this->currentController->getNeuralNetwork().getGlobalClusteringRate() * 100.0f);
    if(ui->doubleSpinBoxCR->value() > ui->doubleSpinBoxCRM->value())
    ui->doubleSpinBoxCRM->setValue(ui->doubleSpinBoxCR->value());
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
    ui->comboBoxActivationFunction->setEnabled(isEnable);
    ui->spinBoxLearningRate->setEnabled(isEnable);
    ui->spinBoxMomentum->setEnabled(isEnable);
}

/**************************************************
 *                      SLOTS                     *
 **************************************************/

void MainWindow::on_pushButtonCompute_clicked()
{
    if (computeIsStop)
    {
        computeIsStop = false;
        this->mainChart->clear();
        if (&currentController->getNeuralNetwork() == nullptr)
        {
            const auto dataSetName = ui->comboBoxData->currentText();
            this->on_pushButtonResetGraph_clicked();
            this->currentController->initializeNeuralNetwork(dataSetName);
            this->refreshClusteringRate();
            ui->spinBoxCount->setValue(this->currentController->getNeuralNetwork().getCurrentIndex());
            ui->spinBoxIteration->setValue(this->currentController->getNeuralNetwork().getNumberOfIteration());
        }
        this->startLoadingLogo();
        this->enableModification(false);

        currentController->getNeuralNetwork().startTraining(*currentController->getDataset().data);

        updateTimer->start();
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
            QString dataSetName = ui->comboBoxData->currentText();
            this->on_pushButtonResetGraph_clicked();
            this->currentController->initializeNeuralNetwork(dataSetName);
            this->refreshClusteringRate();
            ui->spinBoxCount->setValue(this->currentController->getNeuralNetwork().getCurrentIndex());
            ui->spinBoxIteration->setValue(this->currentController->getNeuralNetwork().getNumberOfIteration());
        }
        this->startLoadingLogo();

        currentController->getNeuralNetwork().evaluate(*currentController->getDataset().data);

        updateTimer->start(60);
        timerForTimeEdit->start();
        ui->pushButtonCompute->setText("Stop");
        ui->timeEdit->setTime(QTime(0, 0));
    }
}

void MainWindow::on_pushButtonConsole_clicked() const
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
    this->currentController->addLayer(index);
    this->resetComboBoxLayer();
    this->initializeLayerButtons(index + 1);
}

void MainWindow::on_pushButtonRemoveLayer_clicked()
{
    int index = ui->comboBoxLayer->currentIndex();

    if (index > 0)
    {
        this->currentController->removeLayer(index);
        ui->comboBoxLayer->removeItem(index);
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
    auto function = static_cast<activationFunction>(index);
    this->currentController->inputs.structure[layer-1].activation = function;
}

void MainWindow::on_checkBoxAutoSave_stateChanged(int state)
{
    if (state == 2)
    {
        if (&currentController->getNeuralNetwork() != nullptr)
        {
            this->currentController->inputs.autoSaveWhenBetter = true;
            this->console->write("auto save enable");
        }
    }
    else
    {
        this->currentController->inputs.autoSaveWhenBetter = false;
        this->console->write("auto save disable");
    }
}

void MainWindow::on_checkBoxOpenMP_stateChanged(int state)
{
    if (state == 2)
    {
        if (&currentController->getNeuralNetwork() != nullptr)
        {
            this->currentController->inputs.useMultithreading = true;
            this->console->write("Multithreading enable");
            
        }
    }
    else
    {
        this->currentController->inputs.useMultithreading = false;
        this->console->write("Multithreading save disable");
    }
}

void MainWindow::on_spinBoxNeurons_valueChanged(int value)
{
    int index = ui->comboBoxLayer->currentIndex();
    //TODO: only for FullyConnected
    if(index > 0)
        this->currentController->inputs.structure[index-1].numberOfNeurons = value;
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

    if (ui->spinBoxTrainingRating->value() == currentController->getDataset().data->sets[training].size)
        ui->labelMax->show();
    else
        ui->labelMax->hide();
}

void MainWindow::on_comboBoxData_currentIndexChanged(int index)
{
    this->write("loading ...");
    ui->pushButtonCompute->setEnabled(false);
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
    this->enableModification(true);
    ui->pushButtonReset->setEnabled(false);
    ui->spinBoxCount->setValue(0);
    ui->spinBoxIteration->setValue(0);
    this->refreshClusteringRate();
    this->currentController->deleteNeuralNetwork();
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