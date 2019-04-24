#pragma once
#pragma warning(push, 0)
#include "gtest/gtest.h"
#pragma warning(pop)

using namespace std;

template <typename T>
void EXPECT_ABOUT_EQ(T min, T value, T max, std::string valueName = "value")
{
	ASSERT_TRUE(value >= min) << valueName << " = " << std::to_string(value) + "\t\t >= " << std::to_string(min);
	ASSERT_TRUE(value <= max) << valueName << " = " << std::to_string(value) + "\t\t <= " << std::to_string(max);
}

template <typename T>
void EXPECT_EQ_VECTOR(vector<T> actual, vector<T> expected)
{
	ASSERT_EQ(actual.size(), expected.size()) << "Vectors are of unequal length";

	for (int i = 0; i < actual.size(); ++i)
	{
		EXPECT_EQ(actual[i], expected[i]) << "Vectors different at index " << i;
	}
}
