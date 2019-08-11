#include <gtest/gtest.h>
#include "TestTools.h"
#include "neuralNetwork/StraightforwardNeuralNetwork.h"
#include "../example/SimpleExamplesRegression.cpp"
#include "../example/SimpleExamplesClassification.cpp"
using namespace std;
using namespace snn;

TEST(DISABLED_Example, simpleExampleRegression1)
{
	EXPECT_EQ(simpleExampleRegression1(), EXIT_SUCCESS);
}

TEST(DISABLED_Example, simpleExampleRegression2)
{
	EXPECT_EQ(simpleExampleRegression2(), EXIT_SUCCESS);
}


TEST(DISABLED_Example, simpleExampleClassification1)
{
	EXPECT_EQ(simpleExampleClassification1(), EXIT_SUCCESS);
}

TEST(Example, simpleExampleClassification2)
{
	EXPECT_EQ(simpleExampleClassification2(), EXIT_SUCCESS);
}