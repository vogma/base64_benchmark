#include <gtest/gtest.h>
#include "../Base64SurveyRegistry.hpp"
#include "base64rvv/lib/include/libb64rvv.h"

struct BASE64RVVM2_Adapt
{
	static size_t GetDecodeExpectedLen(size_t inLen) noexcept
	{
		return ((inLen + 3) / 4) * 3;
	}

	static constexpr size_t GetEncodeLen(size_t inLen) noexcept
	{
		return ((inLen + 2) / 3) * 4;
	}

	static std::string encode(void (*func)(uint8_t *in, uint8_t *out, size_t inlen), const std::string &bytes)
	{
		size_t encLen = GetEncodeLen(bytes.length());
		std::string encoded;
		encoded.resize(encLen);
		func((uint8_t *)&bytes[0], (uint8_t *)&encoded[0], bytes.length());
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

struct Base64rvv_m2
{
	std::string encode(const std::string &bytes)
	{
		return BASE64RVVM2_Adapt::encode(base64_encode_rvv_m2, bytes);
	}

	std::string decode(const std::string &base64)
	{
		return BASE64RVVM2_Adapt::decode(base64_decode_rvv_m2, base64);
	}
};

BASE64_REGISTER_ENCODER(Base64rvv_m2);
BASE64_REGISTER_DECODER(Base64rvv_m2);
