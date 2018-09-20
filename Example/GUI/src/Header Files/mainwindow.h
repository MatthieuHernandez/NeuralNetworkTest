#pragma once
#include <QMainWindow>
#include <QMovie>
#include <vector>
#include <qfuturewatcher.h>
#include "Controller.h"
#include "Console.h"
#include "DataManager.h"
#include <qelapsedtimer.h>
#include "MnistVisualizationWidget.h"

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:

	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();

	void write(std::string text, bool onlyConsole = true);


private:

	Ui::MainWindow* ui;

	Console* console;

	Controller* currentController;
	DataVisualizationWidget* currentWidget;
	DataManager manager;

	MnistVisualizationWidget* visu = nullptr;

	int indexController = 0;

	std::vector<float> input;
	std::vector<float> desired;

	QMovie* loadingLogo = nullptr;
	QTimer* timerForCount; // TO RENAME
	QElapsedTimer* timerForTimeEdit; // TO RENAME

	QFutureWatcher<void> watcherCompute;

	QFutureWatcher<void> watcherLoadingData;
	bool firstLoading = true;

	void startLoadingLogo();
	void initializeButtons();
	void resetComboBoxlayer();
	void initializeLayerButtons(int layer);
	void initializeGraphOfClusteringRate();
	void refreshGraphOfClusteringRate();
	void refreshClusteringRate();

	void enableModification(bool isEnable);

	bool isOnGraphTab = true;
	bool computeIsStop = true;

	QVector<double> x;
	QVector<double> y;


private slots:

	/* Controller slots */
	void updateGraphOfClusteringRate();
	void updateNumberOfIteration();
	void updateCount();

	/* Inferface slots */
	void on_spinBoxNeurons_valueChanged(int value);
	void on_spinBoxLearningRate_valueChanged(double value);
	void on_spinBoxMomentum_valueChanged(double value);
	void on_spinBoxTrainingRating_valueChanged(int value);

	void on_comboBoxLayer_currentIndexChanged(int index);
	void on_comboBoxActivationFunction_currentIndexChanged(int index);

	void on_pushButtonCompute_clicked();
	void on_pushButtonEvaluate_clicked();

	void on_pushButtonConsole_clicked();
	void on_pushButtonResetGraph_clicked();

	void on_pushButtonAddLayer_clicked();
	void on_pushButtonRemoveLayer_clicked();

	void on_pushButtonReset_clicked();
	void on_pushButtonSave_clicked();
	void on_pushButtonLoad_clicked();

	void stopCompute();
	void endOfLoadingDataSet();

	/* Data */
	void on_comboBoxData_currentIndexChanged(int index);
};
