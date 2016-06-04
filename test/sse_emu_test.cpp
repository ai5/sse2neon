// This software is subject to the Apache v2.0 License.

#include <gtest/gtest.h>
#include <cstring>
#ifdef USE_SSE42
#include <smmintrin.h>
#else
#include <emmintrin.h>
#endif
#include "sse_emulate.h"
#include "format.h"

TEST(SSE_EMU_TEST, test)
{
	ASSERT_EQ(0, 0);
}

TEST(SSE_EMU_TEST, _mm_extract_epi64_test)
{
	ASSERT_EQ(_mm_extract_epi64(vU64(0xFFEEDDCCBBAA9988ll, 0x7766554433221100ll), 0), 0x7766554433221100ll);
	ASSERT_EQ(_mm_extract_epi64(vU64(0xFFEEDDCCBBAA9988ll, 0x7766554433221100ll), 1), 0xFFEEDDCCBBAA9988ll);
}

TEST(SSE_EMU_TEST, _mm_insert_epi64_test)
{
	// x86ÇæÇ∆16ÇÃÇŸÇ∞Ç∆Ç¢Ç§ÉGÉâÅ[Ç™Ç≈ÇÈÇÃÇ≈î‰ärÇ‹Ç≈Ç±Ç±Ç≈Ç‚ÇÈ
	ASSERT_EQ(_mm_insert_epi64(vS64(123456789, -987654321), 987654321, 0) == vS64(123456789, 987654321), true);
	ASSERT_EQ(_mm_insert_epi64(vS64(123456789, -987654321), 987654321, 1) == vS64(987654321, -987654321), true);
}

TEST(SSE_EMU_TEST, _mm_testc_si128_test)
{
	ASSERT_EQ(_mm_testc_si128(vU64(0xFEDCBA9876543210ll, 0xAAAA55551111FFFFll), 
		                      vU64(0xFEDCBA9876543210ll, 0xAAAA55551111FFFFll)), 1);

	ASSERT_EQ(_mm_testc_si128(vU64(0xFEDCBA9876543210ll, 0xAAAA55551011FFFFll),
		                      vU64(0xFEDCBA9876543210ll, 0xAAAA55551111FFFFll)), 0);

	ASSERT_EQ(_mm_testc_si128(vU64(0xFEDCBA9876543210ll, 0xAAAA55551111FFFFll),
		vU64(0xFEDCBA9876543210ll, 0xAAAA55551011FFFFll)), 1);
}

TEST(SSE_EMU_TEST, _mm_testz_si128_test)
{
	ASSERT_EQ(_mm_testz_si128(vU64(0xF0FAF0F0F0F0F0F0ll, 0x1020354050607080ll),
 		                      vU64(0x0F0F0F0F0F0F0F0Fll, 0x090A0B0C0D0E0FB0ll)), 0);
	
	ASSERT_EQ(_mm_testz_si128(vU64(0xF0F0F0F0F0F0F0F0ll, 0x1020304050607080ll),
		                      vU64(0x0F0F0F0F0F0F0F0Fll, 0x090A0B0C0D0E0F00ll)), 1);

	ASSERT_EQ(_mm_testz_si128(vU64(0xF0F0F0F0F0F0F0F0ll, 0x1020304050607080ll),
		                      vU64(0x0F0F0F0F0F0F0F0Fll, 0x090A0B0C0D0E0FB0ll)), 0);

}

TEST(SSE_EMU_TEST, _mm_cvtepu8_epi16_test)
{
	ASSERT_EQ(_mm_cvtepu8_epi16(vU8(9, 9, 10, 11, 12, 13, 14, 15, 0, -1, 3, -3, 5, -5, 8, -7)) == vS16(0, 255, 3, 253, 5, 251, 8, 249), true);
}

TEST(SSE_EMU_TEST, _mm_min_epu16_test)
{
	ASSERT_EQ(_mm_min_epu16(vU16(65535, 65534, 32767, 65534, 4, 5, 6, 7), 
		                    vU16(65534, 65535, 65534, 32767, 5, 5, 8, 2))
		                 == vU16(65534, 65534, 32767, 32767, 4, 5, 6, 2), true);
}

TEST(SSE_EMU_TEST, _mm_shuffle_epi8_test)
{
	ASSERT_EQ(_mm_shuffle_epi8(
		   vS8(-1, -128, -64, -32, -16, -8, -4, -2, 127, 64, 32, 16, 8, 4, 2, 1),
		   vU8(0x00, 0x81, 0x02, 0x83, 0x04, 0x85, 0x06, 0x87, 0x08, 0x89, 0x0A, 0x8B, 0x0C, 0x8D, 0x0E, 0x8F))
		== vS8(1, 0, 4, 0, 16, 0, 64, 0, -2, 0, -8, 0, -32, 0, -128, 0), true);
}

TEST(SSE_EMU_TEST, _mm_comge_epi8_test)
{
#if !defined(USE_SSE3) && !defined(USE_SSE42)
	//_mm_comge_epi8ÇÕ_mm_shuffle_epi8()ÇÃíÜÇ≈ÇÃÇ›égÇ¡ÇƒÇÈ
	ASSERT_EQ(_mm_comge_epi8(
		vS8(  -1, 11,    0,  124,  125, -124, -125,  100,   11, -31,   10, -124, -125,  124,  125, -100), 
		vS8(  -1, 22,    0,    0,  123, -123, -100, -100,   11, -22,   10,    0, -123,  123,  100,  100))
	 == vU8(0xFF,  0, 0xFF, 0xFF, 0xFF,    0,    0, 0xFF, 0xFF,   0, 0xFF,    0,    0, 0xFF, 0xFF,    0), true);
#endif
}
