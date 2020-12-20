#pragma once

#include <clocale>

#include <string>
#include <type_traits>
#include <locale>
#include <concepts>
#include <bit>

#if defined(_WIN32) || defined(_WIN64)

#include <atlstr.h>

#if defined(DEBUG)
#define LOCALE "en_US.utf8"
#else
#define LOCALE "English_United States.1251"
#endif

#else

#error Unsupported platform detected

#endif

namespace WINAPIHash {

    template<typename T> concept _8BitsTy = std::is_convertible_v<T, uint32_t> && sizeof(T) == 1;
    template<typename T> concept _16BitsTy = std::is_convertible_v <T, uint32_t> && sizeof(T) == 2;

    inline std::wstring toUpperCase(std::wstring wstr) {
        for (auto it = wstr.begin(); it != wstr.cend(); it++)
            *it = std::toupper(*it, std::locale(LOCALE));
        return wstr;
    }

    template<_8BitsTy T>
    uint64_t hash(const T str[]) {
        uint32_t hash = 0;
        for (size_t i = 0; i < std::char_traits<T>::length(str); i++) {
            hash = static_cast<uint32_t>(str[i]) + std::rotr(hash, 0xD);
        }
        hash = std::rotr(hash, 0xD);
        return hash;
    }

    template<_16BitsTy T>
    uint64_t hash(const T str[]) {
        uint32_t hash = 0;
        for (size_t i = 0; i < std::char_traits<T>::length(str); i++) {
            char8_t* firstByte = (char8_t*)(&str[i]);
            char8_t* secondByte = firstByte + 1;
            hash = static_cast<uint32_t>(*firstByte) + std::rotr(hash, 0xD);
            hash = static_cast<uint32_t>(*secondByte) + std::rotr(hash, 0xD);
        }
        // For last two '\x00'
        hash = std::rotr(hash, 0xD);
        hash = std::rotr(hash, 0xD);

        return hash;
    }

    std::wstring toWString(std::string str) {
        return std::wstring(CStringW(str.c_str()));
    }

    uint64_t GetAPIHash(std::wstring library, std::string function) {
        return (hash(WINAPIHash::toUpperCase(library).c_str()) + hash(function.c_str())) & 0xFFFFFFFF;
    }

    uint64_t GetAPIHash(std::string library, std::string function) {
        return WINAPIHash::GetAPIHash(WINAPIHash::toWString(library), function);
    }

}
/* MIT License *********************************************************************
 *
 * Copyright (c) 2020 Jim00000
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 ***********************************************************************************/