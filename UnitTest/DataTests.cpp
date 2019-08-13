#include <gtest/gtest.h>
#include "neuralNetwork/StraightforwardNeuralNetwork.h"
#include "TestTools.h"
#include "data/DataForRegression.h"

using namespace std;
using namespace snn;

// ReSharper disable CppInconsistentNaming CppLocalVariableMayBeConst CppUseAuto

TEST(DISABLED_NormalizeData, BasicTest)
{
	// Arrange
	vector<vector<float>> inputsTraining = {
		{10.0f, 0.8f, 102.0f},
		{20.0f, 1.0f, 100.0f},
		{15.0f, -1.0f, 100.5f}
	};
	vector<vector<float>> inputsTesting = {
		{21.0f, 0.7f, 104.0f},
		{12.0f, 0.4f, 101.0f}
	};
	vector<vector<float>> labels = {{0}, {1}};

	vector<vector<float>> expectedInputsTraining = {
		{-1.0f, 0.8f, 1.0f},
		{1.0f, 1.0f, -1.0f},
		{0.0f, -1.0f, -0.5f}
	};
	vector<vector<float>> expectedInputsTesting = {
		{1.2f, 0.7f, 3.0f},
		{-0.6f, 0.4f, 0.0f}
	};

	// Act
	DataForRegression data(inputsTraining, labels, inputsTesting, labels);

	// Assert
	TestTools::EXPECT_EQ_VECTOR_VECTOR(data.sets[training].inputs, expectedInputsTraining);
	TestTools::EXPECT_EQ_VECTOR_VECTOR(data.sets[snn::testing].inputs, expectedInputsTesting);
}
