/**
 * ATOI.CPP
 * 
 * https://leetcode.com/problems/string-to-integer-atoi/
 * 
 * Andre Zunino <neyzunino@gmail.com>
 * Modified 14 March 2021
 */

#include <string>
#include <vector>
#include <limits>
#include <sstream>
#include <iostream>

constexpr int SIGNED_INT_MIN = -2'147'483'648;
constexpr int SIGNED_INT_MAX =  2'147'483'647;

inline bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

inline bool is_sign(char c) {
    return c == '+' || c == '-';
}

inline bool is_space(char c) {
    return c == ' ';
}

int clamp(long int value, bool neg) {
    int clamped = 0;
    if (neg) {
        if (value + SIGNED_INT_MIN > 0) {
            clamped = SIGNED_INT_MIN;
        } else {
            clamped = value * -1;
        }
    } else if (value > SIGNED_INT_MAX) {
        clamped = SIGNED_INT_MAX;
    } else {
        clamped = value;
    }
    return clamped;
}

int my_atoi(std::string str) {
    const int len = str.size();
    int ini = 0;

    /* ignore leading whitespace */
    for (; ini < len; ++ini) {
        if (!is_space(str[ini])) break;
    }
    if (ini == len) {
        return 0;
    }

    /* handle sign */
    char sign = '+';
    if (is_sign(str[ini])) {
        sign = str[ini];
        ++ini;
    }
    bool neg = sign == '-';

    /* ignore leading zeros */
    while (ini < len && str[ini] == '0') {
        ++ini;
    }

    /* check for remaining digits */
    int fin = ini;
    while (fin < len && is_digit(str[fin])) {
        ++fin;
    };

    int num_len = fin - ini;
    if (num_len < 1) {
        return 0;
    }

    if (num_len > 10) {
        return neg ? SIGNED_INT_MIN : SIGNED_INT_MAX;
    }

    long int mult = 1;
    for (int i = 1; i < num_len; ++i) {
        mult *= 10;
    }

    long int value = 0;
    for (int i = ini; i < fin; ++i) {
        long int v = (str[i] - 0x30) * mult;
        value += v;
        mult /= 10;
    }

    return clamp(value, neg);
}

struct TestCase {
    std::string input;
    long expected;
};

void run_tests(const std::vector<TestCase>& test_cases) {
    for (const auto& [k, v] : test_cases) {
        int got = my_atoi(k);
        std::cout << "Test \"" << k << "\"; expected " << v << "; got " << got;
        if (got != v) {
            std::cerr << " [FAIL]\n";
            continue;
        }
        std::cout << " [OK]\n";
    }
}

int main() {
    std::vector<TestCase> test_cases{
        {"", 0},
        {"0", 0},
        {"  000  ", 0},
        {"4", 4},
        {"42", 42},
        {"-4", -4},
        {"    42", 42},
        {"   -42", -42},
        {"    42  ", 42},
        {"   -42  ", -42},
        {"91283472332", SIGNED_INT_MAX},
        {"-91283472332", SIGNED_INT_MIN},
        {"  987 with words ", 987},
        {"words and 987", 0},
        {"  0000000000012345678", 12345678},
        {"00000-42a1234", 0},
        {"abc", 0},
        {"  abc  ", 0},
        {"2147483646", 2147483646},
        {"-6147483648", SIGNED_INT_MIN},
    };
    run_tests(test_cases);
}

