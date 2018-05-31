#pragma once
#include <QMainWindow>
#include <QMovie>
#include <vector>
#include <qfuturewatcher.h>
#include "Controller.h"
#include "Console.h"
#include "ControllersManager.h"
#include <qelapsedtimer.h>

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:

	explicit MainWindow(QWidget* parent = nullptr);
	void write(std::string text, bool onlyConsole = true);
	~MainWindow();


private:

	Ui::MainWindow* ui;
	Console* console;
	Controller* currentController;
	ControllersManager manager;

	int indexController = 0;

	std::vector<float> input;
	std::vector<float> desired;

	set displayedSet = testing;

	QMovie* loadingLogo = nullptr;
	QTimer* timerForCount; // TO RENAME
	QElapsedTimer* timerForTimeEdit; // TO RENAME

	QFutureWatcher<void> watcherCompute;

	QFutureWatcher<void> watcherLoadingData;
	bool firstLoading = true;

	void displayImage(int value);

	void startLoadingLogo();
	void InitializeButtons();
	void ResetComboBoxlayer();
	void InitializeLayerButtons(int layer);
	void initialiseInputs();
	void resetGraphOfClusteringRate();

	unsigned char getImages(int number, int x, int y);

	bool isOnGraphTab = true;
	bool computeIsStop = true;

	QVector<double> x;
	QVector<double> y;

private slots:

	/* Controller slots*/
	void updateGraphOfClusteringRate();
	void updateNumberOfIteration();
	void updateCount();

	void on_spinBoxNeurons_valueChanged(int value);
	void on_spinBoxImageId_valueChanged(int value);
	void on_spinBoxLearningRate_valueChanged(double value);
	void on_spinBoxMomentum_valueChanged(double value);
	void on_spinBoxTrainingRating_valueChanged(int value);

	void on_pushButtonRemoveLayer_clicked();

	void on_comboBoxSet_currentIndexChanged(int index);
	void on_comboBoxLayer_currentIndexChanged(int index);

	void on_pushButtonCompute_clicked();
	void on_pushButtonConsole_clicked();

	void on_pushButtonAddLayer_clicked();

	void stopCompute();
	void endOfLoadingData();

	/* Data */
	void on_comboBoxData_currentIndexChanged(int index);
};


/*cout << "clustering rate : " << clusteringRate << " epoch : " << count << " time : " << (float)(clock() - numberOfClockCycles) /
CLOCKS_PER_SEC << " secondes" << endl;
numberOfClockCycles = clock();

cout << "clustering rate max : " << clusteringRateMax << " epoch : " << epochMax << endl;
clusteringRateVector.push_back(clusteringRate * 100);
updateGraphOfClusteringRate();
ui->labelClusteringRateMax->setText(
QString::fromStdString(
(string)"Clustering max : " + data::to_string_with_precision(clusteringRateMax * 100, 2) + "%"));
QApplication::processEvents();
if (index % 1000 == 0)
{
ui->labelCount->setText(QString::fromStdString((string)"Count : " + to_string(index)));
}
ui->labelCount->setText(QString::fromStdString((string)"Count : " + to_string(index_max)));

const int index_max = data->sets[training].size;
epochMax = count;*/
