#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <time.h>
#include "neuralNetwork.h"

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

    const int trainnig_set_size = 60000;
    const int testing_set_size = 10000;

    Ui::MainWindow *ui;

    NeuralNetwork neuralNetwork;
    vector<float> input;
    vector<float> desired;

    list<vector<float>> desired_outputs;

    void readData();
    void compute();
    void initialize();

    vector<unsigned char> imagesTest;
    vector<unsigned char> labelsTest;

    unsigned char getImagesTest(int number, int x, int y);
};

#endif // MAINWINDOW_H
