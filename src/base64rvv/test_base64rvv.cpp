#include <gtest/gtest.h>
#include "../Base64SurveyRegistry.hpp"
#include "base64rvv/lib/include/libb64rvv.h"

struct BASE64RVV_Adapt
{
	static constexpr size_t GetEncodedLengthWithoutPadding(size_t decodedLength)
	{
		return (decodedLength * 8 + 5) / 6;
	}

	static constexpr size_t GetEncodedLengthWithPadding(size_t decodedLength)
	{
		return ((GetEncodedLengthWithoutPadding(decodedLength) + 3) / 4) * 4;
	}

	static size_t CountPadding(const std::string &encoded)
	{
		size_t padding = 0;
		size_t len = encoded.length();
		if (len == 0)
			return 0;

		if (encoded[len - 1] == '=')
			++padding;

		if (len == 1)
			return padding;

		if (encoded[len - 2] == '=')
			++padding;

		return padding;
	}

	static size_t GetDecodedLength(const std::string &encoded)
	{
		size_t padding = CountPadding(encoded);
		return (encoded.length() - padding) * 3 / 4;
	}

	static std::string encode(void (*func)(uint8_t *in, uint8_t *out, size_t inlen), const std::string &bytes)
	{
		size_t encLen = GetEncodedLengthWithPadding(bytes.length());
		std::string encoded(encLen, '=');
		func((uint8_t *)&bytes[0], (uint8_t *)&encoded[0], bytes.length());
		return encoded;
	}

	// void base64_encode_rvv(uint8_t *restrict input, uint8_t *output, size_t length);
	// void base64_decode_rvv(const char *data, int8_t *output, size_t input_length, size_t *output_length);

	static std::string decode(void (*func)(const char *in, int8_t *out, size_t inlen, size_t *out_len), const std::string &encoded)
	{
		size_t decLen = GetDecodedLength(encoded);
		std::string decoded(decLen, '\0');
		size_t outlen;
		func((const char *)&encoded[0], (int8_t *)&decoded[0], (size_t) encoded.length(), &outlen);
		return decoded;
	}
};

struct Base64rvv
{
	std::string encode(const std::string &bytes)
	{
		return BASE64RVV_Adapt::encode(base64_encode_rvv, bytes);
	}

	std::string decode(const std::string &base64)
	{
		return BASE64RVV_Adapt::decode(base64_decode_rvv, base64);
	}
};

BASE64_REGISTER_ENCODER(Base64rvv);
BASE64_REGISTER_DECODER(Base64rvv);
