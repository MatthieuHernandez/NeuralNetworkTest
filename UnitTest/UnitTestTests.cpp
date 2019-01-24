#pragma once
#include "GTestTools.h"

TEST(DISABLED_TestCaseName, TestName) 
{
  EXPECT_EQ(1, 1);
}

TEST(DISABLED_TestCaseName, TestName2)
{
	EXPECT_TRUE(true) << "message test";
}