#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <time.h>

#include "neuralNetwork.h"
#include "data.cpp"


using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_spinBoxLabel_editingFinished();

    void on_spinBoxLabel_valueChanged(int value);

    void on_pushButton_clicked();

private:



    Ui::MainWindow *ui;

    Data::MNIST_struct MNIST;
    NeuralNetwork neuralNetwork;

    vector<float> input;
    vector<float> desired;

    list<vector<float>> desired_outputs;

    void compute();
    void initialize();
    void initializeNeuralNetwork();

    vector<unsigned char> imagesTest;
    vector<unsigned char> labelsTest;

    vector<unsigned char> imagesLearn;
    vector<unsigned char> labelsLearn;

    unsigned char getImagesTest(int number, int x, int y);
};

#endif // MAINWINDOW_H
