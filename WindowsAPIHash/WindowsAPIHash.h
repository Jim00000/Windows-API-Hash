#pragma once

#include <clocale>

#include <string>
#include <type_traits>
#include <locale>
#include <concepts>

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
            hash = static_cast<uint32_t>(str[i]) + _rotr(hash, 0xD);
        }
        hash = _rotr(hash, 0xD);
        return hash;
    }

    template<_16BitsTy T>
    uint64_t hash(const T str[]) {
        uint32_t hash = 0;
        for (size_t i = 0; i < std::char_traits<T>::length(str); i++) {
            char8_t* firstByte = (char8_t*)(&str[i]);
            char8_t* secondByte = firstByte + 1;
            hash = static_cast<uint32_t>(*firstByte) + _rotr(hash, 0xD);
            hash = static_cast<uint32_t>(*secondByte) + _rotr(hash, 0xD);
        }
        // For last two '\x00'
        hash = _rotr(hash, 0xD);
        hash = _rotr(hash, 0xD);

        return hash;
    }

    template <typename WSTR, typename STR> requires requires(WSTR wstr, STR sstr) {
        std::is_base_of_v<std::wstring, WSTR> || std::is_convertible_v<WSTR, std::wstring>;
        std::is_base_of_v<std::string, STR> || std::is_convertible_v<STR, std::string>;
    }
    uint64_t GetAPIHash(WSTR&& library, STR&& function) {
        return (hash(WINAPIHash::toUpperCase(std::wstring{ library }).c_str()) + hash(std::string{ function }.c_str())) & 0xFFFFFFFF;
    }

    template < _8BitsTy T>
    uint64_t GetAPIHash(std::string&& library, T function[]) {
        std::string function_str(function);
        return GetAPIHash(library, function_str);
    }

    template <>
    uint64_t GetAPIHash<std::string>(std::string&& library, std::string&& function) {
        CStringW cstringw(library.c_str());
        return GetAPIHash(std::wstring{ cstringw }, function);
    }

    template<_8BitsTy T1, _8BitsTy T2>
    uint64_t GetAPIHash(T1 library[], T2 function[]) {
        CStringW cstringw(library);
        return GetAPIHash(std::wstring{ cstringw }, std::string{ function });
    }

    template<_16BitsTy T1, _8BitsTy T2>
    uint64_t GetAPIHash(T1 library[], T2 function[]) {
        std::wstring library_wstr{ library };
        std::string function_str{ function };
        return GetAPIHash(library_wstr, function_str);
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