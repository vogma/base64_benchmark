#include <gtest/gtest.h>
#include "../Base64SurveyRegistry.hpp"
#include "base64sve/lib/include/base64sve.h"
#include <iostream>

struct BASE64SVE_Adapt_bdep
{

    static constexpr inline size_t GetDecodeExpectedLen(size_t inLen) noexcept
    {
        return ((inLen + 3) / 4) * 3;
    }

    static constexpr inline size_t GetEncodeLen(size_t inLen) noexcept
    {
        return ((inLen + 2) / 3) * 4;
    }

    static std::string encode(void (*func)(void *in, char *out, size_t inlen), const std::string &bytes)
    {
        size_t encLen = GetEncodeLen(bytes.length());
        std::string encoded;
        encoded.resize(encLen);
        func((void *)&bytes[0], &encoded[0], bytes.length());
        return encoded;
    }

    static std::string decode(void (*func)(char *in, void *out, size_t inlen, size_t *decoded_length), const std::string &encoded)
    {
        std::string decoded;
        decoded.resize(GetDecodeExpectedLen(encoded.length()));
        size_t dLen = 0;
        func((char *)&encoded[0], (int8_t *)&decoded[0], (size_t)encoded.length(), &dLen);
        // void base64_decode(char *base64_data, void *output, size_t encoded_length, size_t *decoded_length);
        decoded.resize(dLen);
        return decoded;
    }
};

struct base64sve_bdep
{
    std::string encode(const std::string &bytes)
    {
        return BASE64SVE_Adapt_bdep::encode(base64sve_encode_bdep, bytes);
    }

    std::string decode(const std::string &base64)
    {
        return BASE64SVE_Adapt_bdep::decode(base64sve_decode, base64);
    }
};

BASE64_REGISTER_ENCODER(base64sve_bdep);
BASE64_REGISTER_DECODER(base64sve_bdep);