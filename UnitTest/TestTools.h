#pragma once
#include <string>
#include <vector>
#include "gtest/gtest.h"

class TestTools
{
public :
	template <typename T>
	static void EXPECT_ABOUT_EQ(T min, T value, T max, std::string valueName = "value");

	static void EXPECT_EQ_VECTOR(std::vector<float> actual, std::vector<float> expected);

	static void EXPECT_EQ_VECTOR_VECTOR(std::vector<std::vector<float>> actual,
	                                    std::vector<std::vector<float>> expected);
};

template <typename T>
void TestTools::EXPECT_ABOUT_EQ(T min, T value, T max, std::string valueName)
{
	
	ASSERT_TRUE(value >= min) << valueName << " = " << to_string(value) + "\t\t >= " << to_string(min);
	ASSERT_TRUE(value <= max) << valueName << " = " << to_string(value) + "\t\t <= " << to_string(max);
}