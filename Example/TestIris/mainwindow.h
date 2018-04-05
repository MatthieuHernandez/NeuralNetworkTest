#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <vector>
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
        void sleep(int time = 0);


    private:

        Ui::MainWindow *ui;
        void intialisation();
        void loadData();
        int getLabel(int value);

        vector<vector<float>> inputs;
        vector<vector<float>> desires;
};

#endif // MAINWINDOW_H
