#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "Controller.h"
#include "Console.h"

namespace Ui
{
	class MainWindow;
}

enum DisplayedSet
{
	testing = 0,
	training
};

enum indexData
{
	indexMNIST = 0,
	indexIris,
	indexParisTrees,
	End
};

class MainWindow : public QMainWindow
{
Q_OBJECT
public:

	explicit MainWindow(QWidget* parent = 0);
	~MainWindow();


private:

	Ui::MainWindow* ui;
	Console* console;

	int indexController = 0;
	Controller* currentController;
	std::vector<Controller*> controllers;

	//data::MNIST_struct MNIST;

	std::vector<float> input;
	std::vector<float> desired;

	//list<std::vector<float>> desired_outputs;

	DisplayedSet displayedSet = testing;

	void compute();
	void initialize();
	void initializeNeuralNetwork();
	void displayImage(int value);
	int getLabel(int value, DisplayedSet displayedSet);
	void graphClusteringRate();

	unsigned char getImages(int number, int x, int y);
	bool flag_graph = true;

	QVector<double> clusteringRates;
	QVector<double> x;

private slots:

	void on_spinBoxImageId_valueChanged(int value);
	void on_pushButton_clicked();
	void on_comboBoxSet_currentIndexChanged(int index);
	void on_pushButtonConsole_clicked();
};

#endif // MAINWINDOW_H
