#include <gtest/gtest.h>
#include "TestTools.h"
#include "../example/RegressionExample.cpp"
#include "../example/ClassificationExample.cpp"
#include "../example/MultipleClassificationExemple.cpp"
using namespace std;
using namespace snn;

TEST(Example, regressionExample)
{
	EXPECT_EQ(regressionExample(), EXIT_SUCCESS);
}

TEST(Example, multipleClassificationExample)
{
	EXPECT_EQ(multipleClassificationExample(), EXIT_SUCCESS);
}

TEST(Example, classificationExample)
{
	EXPECT_EQ(classificationExample(), EXIT_SUCCESS);
}
