#include <gtest/gtest.h>
#include "../Base64SurveyRegistry.hpp"
#include "base64rvv/lib/include/libb64rvv.h"

struct BASE64RVV_Adapt
{
	static size_t GetDecodeExpectedLen(size_t inLen) noexcept
	{
		return ((inLen + 3) / 4) * 3;
	}

	static constexpr size_t GetEncodeLen(size_t inLen) noexcept
	{
		return ((inLen + 2) / 3) * 4;
	}
	static int64_t timespecDiff(struct timespec *timeA_p, struct timespec *timeB_p)
	{
		return ((timeA_p->tv_sec * 1000000000) + timeA_p->tv_nsec) -
			   ((timeB_p->tv_sec * 1000000000) + timeB_p->tv_nsec);
	}

	static std::string encode(void (*func)(uint8_t *in, uint8_t *out, size_t inlen), const std::string &bytes)
	{
		size_t encLen = GetEncodeLen(bytes.length());
		std::string encoded;
		encoded.resize(encLen);

		struct timespec start, end;

		// clock_gettime(CLOCK_MONOTONIC_RAW, &start);
		func((uint8_t *)&bytes[0], (uint8_t *)&encoded[0], bytes.length());
		// clock_gettime(CLOCK_MONOTONIC_RAW, &end);
		// uint64_t timeElapsed_rvv = timespecDiff(&end, &start);
		// printf("input length:%ld time (qs): %f\n", bytes.length(), ((double)timeElapsed_rvv / 1000));

		return encoded;
	}

	static std::string decode(size_t (*func)(const char *in, int8_t *out, size_t inlen), const std::string &encoded)
	{
		std::string decoded;
		decoded.resize(GetDecodeExpectedLen(encoded.length()));
		size_t dLen = func((const char *)&encoded[0], (int8_t *)&decoded[0], (size_t)encoded.length());
		decoded.resize(dLen);
		return decoded;
	}
};
// size_t b64_decode_rvv(const char *src, char *dst, size_t length);

struct base64rvv_m4
{
	std::string encode(const std::string &bytes)
	{
		return BASE64RVV_Adapt::encode(base64_encode_rvv_m4, bytes);
	}

	std::string decode(const std::string &base64)
	{
		return BASE64RVV_Adapt::decode(base64_decode_rvv_m4, base64);
	}
};

BASE64_REGISTER_ENCODER(base64rvv_m4);
BASE64_REGISTER_DECODER(base64rvv_m4);
