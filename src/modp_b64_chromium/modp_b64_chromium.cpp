#include "chromium/modp_b64/modp_b64.h"
#include <iostream>
#include <gtest/gtest.h>
#include "../test_base.hpp"
#include <string>

using namespace std;

struct B64_Adapt
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

	static std::string encode(size_t(*func)(char*,const char*,size_t), const std::string &bytes)
	{
		size_t encLen = GetEncodedLengthWithPadding(bytes.length());
		std::string encoded(encLen, '=');
		func((char*)&encoded[0], (const char*)&bytes[0], bytes.length());
		return encoded;
	}

	static std::string decode(size_t(*func)(char* dest, const char* src, size_t len), const std::string &encoded)
	{
		size_t decLen = GetDecodedLength(encoded);
		std::string decoded(decLen, '\0');
		func((char*)&decoded[0], (const char*)&encoded[0], encoded.length());
		return decoded;
	}
};

struct modp_b64_chromium
{
	std::string encode(std::string &bytes)
	{
		return B64_Adapt::encode(modp_b64_encode, bytes);
	}

	std::string decode(std::string &bytes)
	{
		return B64_Adapt::decode(modp_b64_decode, bytes);
	}
};

IMPLEMENT_ENCODE_TESTS(modp_b64_chromium);
IMPLEMENT_DECODE_TESTS(modp_b64_chromium);
