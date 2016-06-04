// Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
// This software is subject to the Apache v2.0 License.
#pragma once
#ifndef __FORMAT_H__
#define __FORMAT_H__

#ifdef _WIN32
#include "sse_emulate.h"
#else
#include "SSE2NEON.h"
#endif


inline __m128i vU64(uint64_t v1, uint64_t v0)
{
	sse_m128 t;
	t.u64[0] = v0;
	t.u64[1] = v1;
	return t.m128i;
}

inline __m128i vS64(int64_t v1, int64_t v0)
{
	sse_m128 t;
	t.s64[0] = v0;
	t.s64[1] = v1;
	return t.m128i;
}


inline __m128i vU8(uint8_t v15, uint8_t v14, uint8_t v13, uint8_t v12,
	uint8_t v11, uint8_t v10, uint8_t v9, uint8_t v8,
	uint8_t v7, uint8_t v6, uint8_t v5, uint8_t v4,
	uint8_t v3, uint8_t v2, uint8_t v1, uint8_t v0)
{
	return _mm_set_epi8(v15, v14, v13, v12, v11, v10, v9, v8, v7, v6, v5, v4, v3, v2, v1, v0);
}

inline __m128i vS8(int8_t v15, int8_t v14, int8_t v13, int8_t v12,
	int8_t v11, int8_t v10, int8_t v9, int8_t v8,
	int8_t v7, int8_t v6, int8_t v5, int8_t v4,
	int8_t v3, int8_t v2, int8_t v1, int8_t v0)
{
	return _mm_set_epi8(v15, v14, v13, v12, v11, v10, v9, v8, v7, v6, v5, v4, v3, v2, v1, v0);
}

inline __m128i vS16(int16_t v7, int16_t v6, int16_t v5, int16_t v4,
	int16_t v3, int16_t v2, int16_t v1, int16_t v0)
{
	return _mm_set_epi16(v7, v6, v5, v4, v3, v2, v1, v0);
}

inline __m128i vU16(uint16_t v7, uint16_t v6, uint16_t v5, uint16_t v4,
	uint16_t v3, uint16_t v2, uint16_t v1, uint16_t v0)
{
	return _mm_set_epi16(v7, v6, v5, v4, v3, v2, v1, v0);
}

#ifndef __ANDROID__
inline bool operator==(const __m128i& a, const __m128i& b) { return memcmp(&a, &b, sizeof(__m128i)) == 0; }
#endif
inline bool equals(const __m128i& a, const __m128i& b) { return memcmp(&a, &b, sizeof(__m128i)) == 0; }

#endif
