#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cout << "STEP 00 finished : Start" << endl;
    this->initialize();
    cout << "STEP 01 finished : Initialize" << endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::initialize()
{
    this->MNIST = Data::create_MNIST();
}

unsigned char MainWindow::getImagesTest(int number, int x, int y)
{
    return imagesTest[number * 784 + y * 28 + x];
}

void MainWindow::on_spinBoxLabel_editingFinished()
{

}

void MainWindow::on_spinBoxLabel_valueChanged(int value)
{
    int size = 28;
    int multiple = 10;
    QImage picture(size, size, QImage::Format_RGB32);
    for(int x = 0; x < size; x++)
    {
        for(int y = 0; y < size; y++)
        {
            picture.setPixel(x, y, qRgb((int)getImagesTest(value, x, y),
                                        (int)getImagesTest(value, x, y),
                                        (int)getImagesTest(value, x, y)));
        }
    }
    QImage scalePicture = picture.scaled(size*multiple, size*multiple, Qt::KeepAspectRatio);
    ui->labelPicture->setPixmap(QPixmap::fromImage(scalePicture));
}

void MainWindow::compute()
{
    this->initializeNeuralNetwork();

    clock_t numberOfClockCycle = clock();
    float cluseringRateMax = -1;
    int epochMax = 0;

    for(int count = 1; ; count++)
    {
        for(int index = 0; index < trainnig_set_size; index ++)
        {
           input.assign(&imagesTest[index*784], &imagesTest[(index+1)*784]);
           for(int j = 0; j < 10; j++)
           {
               if(labelsTest[index] == j)
                   desired[j] = 1;
               else
                   desired[j] = 0;
           }
           //neuralNetwork.train(input, desired);
           cout << index << endl;
        }
        neuralNetwork.resetCalculationOfClusteringRate();
        for(int index = 0; index < testing_set_size; index ++)
        {
            for(unsigned int i = 0; i < labelsTest.size(); i++)
            {
                input.assign(&imagesTest[index*784], &imagesTest[(index+1)*784]);

                for(int j = 0; j < 10; j++)
                {
                    if(labelsTest[i] == j)
                        desired[j] = 1;
                    else
                        desired[j] = 0;
                }
                neuralNetwork.calculateClusteringRate(input, desired);
            }
        }
        if(neuralNetwork.getClusteringRate() > cluseringRateMax)
        {
            cluseringRateMax = neuralNetwork.getClusteringRate();
            epochMax = count;
        }
        cout << "clustering rate : " << neuralNetwork.getClusteringRate() << " epoch : " << count << " time : " << (float)numberOfClockCycle/CLOCKS_PER_SEC << " secondes" << endl;
        cout << "clustering rate max : " << cluseringRateMax << " epoch : " << epochMax << endl;
    }
}

void MainWindow::initializeNeuralNetwork()
{
    this->neuralNetwork = NeuralNetwork(784, 1, 100, 10);

    neuralNetwork.resetCalculationOfClusteringRate();
    neuralNetwork.setLearningRate(0.01f);

    if(neuralNetwork.isValid() != 0)
    {
        cout << "ERROR : " << neuralNetwork.getLastError() << endl;
        exit(0);
    }

    this->input.resize(784);
    this->desired.resize(10);
}

void MainWindow::on_pushButton_clicked()
{
    compute();
}
