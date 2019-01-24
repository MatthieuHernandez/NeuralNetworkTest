#include "GTestTools.h"

int main(int ac, char* av[])
{
	testing::InitGoogleTest(&ac, av);
	const auto tests = RUN_ALL_TESTS();
	system("PAUSE");
	return tests;
}
