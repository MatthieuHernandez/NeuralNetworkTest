#pragma once
#include "gtest/gtest.h"

TEST(TestCaseName, TestName) 
{
  EXPECT_EQ(1, 1);
}

TEST(TestCaseName, TestName2)
{
	EXPECT_TRUE(true) << "message test";
}