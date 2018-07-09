#pragma once
#include "gtest/gtest.h"

template<typename T>
void EXPECT_ABOUT_EQ(T min, T value, T max, std::string valueName = "value")
{
	ASSERT_TRUE(value >= min) << valueName + " = " + std::to_string(value) + "\t\t >= " + std::to_string(min);
	ASSERT_TRUE(value <= max) << valueName + " = " + std::to_string(value) + "\t\t <= " + std::to_string(max);
}

