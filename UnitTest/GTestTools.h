#pragma once
#include "gtest/gtest.h"

template<typename T>
void EXPECT_ABOUT_EQ(T min, T value, T max)
{
	ASSERT_TRUE(value >= min);
	ASSERT_TRUE(value <= max);
}

