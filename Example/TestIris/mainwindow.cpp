#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>


// 95.333% neuralNetwork(4, 1, 15, 3)                        YEAH !!!
// 95.333% neuralNetwork(4, 2, 20, 3)  4818  epoch           YEAH !!!
// 96.666% neuralNetwork(4, 2, 20, 3)  1334  epoch 0.01 lr   YEAH !!!
// 97.333% neuralNetwork(4, 2, 20, 3)  7126  epoch 0.01 lr   YEAH !!!
// 98.000% neuralNetwork(4, 3, 100, 3) 5834 epoch 0.01 lr    YEAH !!!

// 94.000% neuralNetwork(4, 1, 3, 3) 2021757 epoch 0.01 lr   YEAH !!! not really good

// 99.333% neuralNetwork(4, 3, 1000, 3) 11197 epoch 0.01 lr  YEAH !!!

/*static int randomBetween(int a, int b) // WARNING TO : b excluded
{
	return rand() % (b - a) + a;
}*/

template <typename T>
string to_string_with_precision(const T value, const int n = 3)
{
	ostringstream out;
	out << fixed << std::setprecision(n) << value;
	return out.str();
}

void MainWindow::sleep(int time)
{
	QEventLoop loop;
	QTimer::singleShot(time, &loop, SLOT(quit()));
	loop.exec();
}

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	this->intialisation();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::loadData()
{
	string line;
	ifstream file("../TestIris/iris.txt");
	int count = 0;
	vector<vector<string>> individuals;
	vector<string> temp;
	if (!file.is_open())
	{
		cout << "Cannot open file" << endl;
	}
	else
	{
		cout << "file open" << endl;
		getline(file, line); // labels
		while (getline(file, line))
		{
			//cout << line << endl;
			individuals.push_back(temp);
			for (int i = 0; line != line.substr(line.find('\t') + 1); i++)
			{
				individuals[count].push_back(line.substr(0, line.find('\t')));
				line = line.substr(line.find('\t') + 1);
			}
			individuals[count].push_back(line.substr(0, line.find('\t')));
			count++;
		}
		file.close();
	}
	inputs.resize(150);
	desires.resize(150);
	for (int i = 0; i < 150; i++) // c <= 500
	{
		inputs[i].resize(4);
		desires[i].resize(3);
	}


	for (int i = 0; i < 150; i++) // c <= 500
	{
		inputs[i][0] = stof(individuals[i][0]);
		inputs[i][1] = stof(individuals[i][1]);
		inputs[i][2] = stof(individuals[i][2]);
		inputs[i][3] = stof(individuals[i][3]);

		if (individuals[i][4] == "setosa")
		{
			desires[i][0] = 1;
			desires[i][1] = 0;
			desires[i][2] = 0;
		}
		else if (individuals[i][4] == "versicolor")
		{
			desires[i][0] = 0;
			desires[i][1] = 1;
			desires[i][2] = 0;
		}
		else if (individuals[i][4] == "virginica")
		{
			desires[i][0] = 0;
			desires[i][1] = 0;
			desires[i][2] = 1;
		}
		else
		{
			cout << "wrong label" << endl;
			break;
		}
	}
	cout << "data load : " << individuals.size() << " individuals" << endl;
}

int MainWindow::getLabel(const int value)
{
	if (desires[value][0] == 1) return 0;
	if (desires[value][1] == 1) return 1;
	if (desires[value][2] == 1) return 2;
	return -1;
}

void MainWindow::intialisation() // less than 100 times train to obtain 90%
{
	cout << "Start" << endl;
	srand(time(nullptr));
	loadData();

	vector<unsigned int> a{4, 200, 3};
	vector<activationFunction> b{sigmoid, sigmoid, sigmoid, sigmoid};

	NeuralNetwork neuralNetwork(a, b, 0.001f, 0.0f);

	const int numberOfEpochs = 50;

	if (neuralNetwork.isValid() != 0)
	{
		cout << "ERROR : " << neuralNetwork.getLastError() << endl;
		exit(0);
	}
	cout << "network initialaze. " << endl;

	float clusteringRateMax = -1;
	int epochMax = 0;

	//auto numberOfClockCycle = clock();
	for (int c = 1; -c <= numberOfEpochs; c++)
	{
		const auto r = rand();
		srand(r);
		std::random_shuffle(inputs.begin(), inputs.end());
		srand(r);
		std::random_shuffle(desires.begin(), desires.end());

		for (unsigned int i = 0; i < 150; i++)
		{
			neuralNetwork.train(inputs[i], desires[i]);
		}

		for (unsigned int i = 0; i < inputs.size(); i++)
		{
			neuralNetwork.calculateClusteringRateForClassificationProblem(inputs[i], getLabel(i));
		}
		const auto clusteringRate = neuralNetwork.getClusteringRate();
		if (clusteringRate > clusteringRateMax)
		{
			clusteringRateMax = clusteringRate;
			epochMax = c;
		}
		if (c % 2 == 0)
		{
			cout << "clustering rate : " << to_string_with_precision(clusteringRate) << "\t epoch : " << c << endl;
			cout << "clustering rate max : " << to_string_with_precision(clusteringRateMax) << "\t epoch : " << epochMax << endl;
		}
	}
	//    cluseringRateMax = neuralNetwork.getClusteringRate();
	//    cout << "clustering rate max on CPU : " << cluseringRateMax << endl;
	//    numberOfClockCycle = clock() - numberOfClockCycle;
	//    cout << "Time for " << numberOfEpochs << " epochs : " << numberOfClockCycle << " clock cycles" << " (" << (float)numberOfClockCycle/CLOCKS_PER_SEC << " secondes)\n" << endl;
}
