#pragma once
#include "GTestTools.h"
#include "neuralNetwork.h"

using namespace std;

TEST(SaveNeuralNetwork, EqualTest)
{
	const vector<int> structureOfNetwork {5, 20, 10, 3};
	const vector<activationFunctionType> activationFunctionByLayer{sigmoid, sigmoid, sigmoid};
	NeuralNetwork A(structureOfNetwork, activationFunctionByLayer, 0.03f, 0.78f);
	NeuralNetwork C(structureOfNetwork, activationFunctionByLayer, 0.03f, 0.78f);
	NeuralNetwork B = A;

	EXPECT_TRUE(A == B) << "A == B";
	EXPECT_FALSE(A == C) << "A != C";

	const vector<float> inputs {1.5, 0.75, -0.25, 0};
	const vector<float> desired {1, 0, 0.5, 0};

	A.train(inputs, desired);

	EXPECT_FALSE(A == B) << "A != B";

	B.train(inputs, desired);
	
	EXPECT_TRUE(A == B) << "A == B";
}

TEST(SaveNeuralNetwork, Save)
{
	//EXPECT_TRUE(false);
}
