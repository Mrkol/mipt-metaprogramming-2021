#pragma once

#include <string>

template<size_t max_length>
class String;

template<size_t max_length>
struct String {

    constexpr String(const char* str, size_t length):
            len(std::min(length, max_length)) {
        std::copy_n(str, len, data);
    }

    constexpr operator std::string_view() const {
        return {data, len};
    }

    uint32_t len;
    char data[max_length];
};

constexpr String<256u> operator "" _cstr(const char* str, size_t length) {
    return {str, length};
}
