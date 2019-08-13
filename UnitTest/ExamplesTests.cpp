#include <gtest/gtest.h>
#include "TestTools.h"
#include "neuralNetwork/StraightforwardNeuralNetwork.h"
#include "../example/RegressionExample.cpp"
#include "../example/ClassificationExample.cpp"
#include "../example/MultipleClassificationExemple.cpp"
using namespace std;
using namespace snn;

TEST(DISABLED_Example, regressionExample)
{
	EXPECT_EQ(regressionExample(), EXIT_SUCCESS);
}

TEST(DISABLED_Example, multipleClassificationExample)
{
	EXPECT_EQ(multipleClassificationExample(), EXIT_SUCCESS);
}

TEST(DISABLED_Example, classificationExample)
{
	EXPECT_EQ(classificationExample(), EXIT_SUCCESS);
}
