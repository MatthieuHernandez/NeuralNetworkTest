#include <gtest/gtest.h>
#include "TestTools.h"
#include "neuralNetwork/StraightforwardNeuralNetwork.h"
#include "data/DataForRegression.h"
using namespace std;
using namespace snn;

// ReSharper disable CppInconsistentNaming CppLocalVariableMayBeConst CppUseAuto

TEST(DISABLED_SaveNeuralNetwork, EqualTest)
{
	const vector<int> structureOfNetwork {5, 20, 10, 3};
	const vector<activationFunctionType> activationFunctionByLayer{iSigmoid, tanH, sigmoid};

	StraightforwardOption optionA{};
	optionA.learningRate  = 0.03f;
	optionA.momentum = 0.78f;

	StraightforwardOption optionB{};
	optionB.learningRate  = 0.03f;
	optionB.momentum = 0.78f;

	StraightforwardNeuralNetwork A(structureOfNetwork, activationFunctionByLayer, optionA);
	StraightforwardNeuralNetwork C(structureOfNetwork, activationFunctionByLayer, optionB);
	StraightforwardNeuralNetwork B = A;

	EXPECT_TRUE(A == B) << "A == B";
	EXPECT_TRUE(&A != &B) << "A != B";

	EXPECT_TRUE(*A.getLayer(0) == *B.getLayer(0)) << "Value : A.layers[0] == B.layers[0]";
	EXPECT_TRUE(A.getLayer(0) != B.getLayer(0)) << "Address : A.layers[0] != B.layers[0]";

	EXPECT_TRUE(*A.getLayer(0)->getNeuron(0) == *B.getLayer(0)->getNeuron(0)) << "Value : A.Layers[0].neurons[0] == B.Layers[0].neurons[0]";
	EXPECT_TRUE(A.getLayer(0)->getNeuron(0) != B.getLayer(0)->getNeuron(0)) << "Address : A.Layers[0].neurons[0] != B.Layers[0].neurons[0]";
	
	EXPECT_TRUE(*A.getLayer(0)->getNeuron(0)->getActivationFunction() == *B.getLayer(0)->getNeuron(0)->getActivationFunction()) << "Value : A.Layers[0].neurons[0] == B.Layers[0].neurons[0]";
	EXPECT_TRUE(A.getLayer(0)->getNeuron(0)->getActivationFunction() != B.getLayer(0)->getNeuron(0)->getActivationFunction()) << "Address : A.Layers[0].neurons[0] != B.Layers[0].neurons[0]";

	EXPECT_TRUE(A != C) << "A != C";

	vector<vector<float>> inputs {{1.5, 0.75, -0.25, 0, 0}};
	vector<vector<float>> desired {{1, 0, 0.5, 0}};
	DataForRegression data(inputs, desired, 0.2f);

	A.trainOnce(inputs.back(), desired.back());

	EXPECT_TRUE(A != B) << "A != B";

	B.trainOnce(inputs.back(), desired.back());

	EXPECT_TRUE(A == B) << "A == B";

	A.evaluate(data);

	EXPECT_TRUE(A.getF1Score() == B.getF1Score()) << "A == B";
}

TEST(DISABLED_SaveNeuralNetwork, Save)
{
	const vector<int> structureOfNetwork {5, 20, 10, 3};
	const vector<activationFunctionType> activationFunctionByLayer{iSigmoid, tanH, sigmoid};

	StraightforwardOption option{};
	option.learningRate  = 0.03f;
	option.momentum = 0.78f;

	StraightforwardNeuralNetwork A(structureOfNetwork, activationFunctionByLayer, option);

	A.saveAs("./testSave.bin");

	StraightforwardNeuralNetwork B = StraightforwardNeuralNetwork::loadFrom("./testSave.bin");

	EXPECT_TRUE(A == B) << "A == B";
}
