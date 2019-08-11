#include "TestTools.h"
#include "gtest/gtest.h"

using namespace std;


void TestTools::EXPECT_EQ_VECTOR(vector<float> actual, vector<float> expected)
{
	ASSERT_EQ(actual.size(), expected.size()) << "Vectors are of unequal length";

	for (int i = 0; i < actual.size(); ++i)
	{
		EXPECT_NEAR(actual[i], expected[i], 0.0001) << "Vectors different at index " << i;
	}
}

void TestTools::EXPECT_EQ_VECTOR_VECTOR(vector<vector<float>> actual, vector<vector<float>> expected)
{
	ASSERT_EQ(actual.size(), expected.size()) << "Vectors are of unequal length";

	for (int i = 0; i < actual.size(); ++i)
	{
		EXPECT_EQ_VECTOR(actual[i], expected[i]);
	}
}