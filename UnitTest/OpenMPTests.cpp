#include <gtest/gtest.h>
#include "neuralNetwork/StraightforwardNeuralNetwork.h"
#include "TestTools.h"
#include "data/DataForRegression.h"

using namespace std;
using namespace snn;

// ReSharper disable CppInconsistentNaming CppLocalVariableMayBeConst CppUseAuto
StraightforwardNeuralNetwork& buildNeuralNetwork(bool useMultithreading);
Data& buildData();

TEST(SpeedTest, BasicTest)
{
	// Arrange
	Data &data1 = buildData();
	Data &data2 = buildData();
	auto neuralNetwork = buildNeuralNetwork(false);
	auto multithreadingNeuralNetwork = buildNeuralNetwork(true);

	// Act
	neuralNetwork.trainingStart(data1);
	this_thread::sleep_for(5s);
	neuralNetwork.trainingStop();
	this_thread::sleep_for(5s);
	multithreadingNeuralNetwork.trainingStart(data2);
	this_thread::sleep_for(5s);
	multithreadingNeuralNetwork.trainingStop();
	
	
	// Assert
	auto valueWithMT = multithreadingNeuralNetwork.getNumberOfIteration();
	auto valueWithoutMT = neuralNetwork.getNumberOfIteration();
	ASSERT_TRUE(valueWithMT > 2 * valueWithoutMT) << std::setprecision(3) << "With multithreading, it's "  << static_cast<float>(valueWithMT) / valueWithoutMT << " times faster." << endl;
}

StraightforwardNeuralNetwork& buildNeuralNetwork(bool useMultithreading)
{
	StraightforwardOption option;
	option.useMultithreading = useMultithreading;
	auto *neuralNetwork = new StraightforwardNeuralNetwork({2, 400, 400, 1}, {sigmoid, sigmoid, sigmoid}, option);
	return *neuralNetwork;
}

Data& buildData()
{
	vector<vector<float>> inputData {{0.3, 0.75}};
	vector<vector<float>> expectedOutput {{0.3, 0.75}};
	auto *data = new DataForRegression(inputData, expectedOutput, 0.1f);
	return *data;
}