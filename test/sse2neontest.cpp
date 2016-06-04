#include <gtest/gtest.h>

#ifdef _WIN32
#include <smmintrin.h>
#else
#include "SSE2NEON.h"
#endif


TEST(SSE2NEONTest, test)
{
	ASSERT_EQ(0, 0);
}

