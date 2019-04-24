#pragma once
#include <gtest/gtest.h>
#include "neuralNetwork/StraightforwardNeuralNetwork.h"
#include "GTestTools.h"

using namespace std;
using namespace snn;

// ReSharper disable CppInconsistentNaming CppLocalVariableMayBeConst CppUseAuto

TEST(NormalizeData, BasicTest)
{
	// Arrange
	vector<vector<float>> inputsTraining = {{10, 0.83, 102}, {15, 1, 100}, {20, 0, 100.5}};
	vector<vector<float>> inputsTesting = {{21, 0.75, 104}, {12, 0.125, 101}};
	vector<vector<float>> labels = {{0}, {1}};

	vector<vector<float>> expectedInputsTraining = {{0, 0.83, 1}, {0.5, 1, 0}, {1.0, 0, 0.25}};
	vector<vector<float>> expectedInputsTesting = {{1.1, 0.75, 2}, {0.2, 0.125, 0.5}};

	// Act
	StraightforwardData data(snn::regression, inputsTraining, labels, inputsTesting, labels);

	// Assert
	EXPECT_EQ_VECTOR(data.data->sets[training].inputs, expectedInputsTraining);
	EXPECT_EQ_VECTOR(data.data->sets[snn::testing].inputs, expectedInputsTesting);
}
