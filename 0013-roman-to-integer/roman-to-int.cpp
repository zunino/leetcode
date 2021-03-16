/**
 * ROMAN-TO-INT.CPP
 * 
 * https://leetcode.com/problems/roman-to-integer/
 * 
 * Andre Zunino <neyzunino@gmail.com>
 * Created 15 March 2021
 * Modified 16 March 2021
 */

#include <bits/c++config.h>
#include <string_view>
#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std::string_literals;

int roman_to_int(std::string_view s) {
    unsigned short len = s.size();
    unsigned short value = 0;

    unsigned short remaining = len;
    for (unsigned short i = 0; i < len;) {
        unsigned char c = s[i];
        --remaining;

        if (remaining > 0) {
            if (c == 'I' && s[i+1] == 'V') {
                value += 4;
                --remaining;
                i += 2;
                continue;
            }
            if (c == 'I' && s[i+1] == 'X') {
                value += 9;
                --remaining;
                i += 2;
                continue;
            }
            if (c == 'X' && s[i+1] == 'L') {
                value += 40;
                --remaining;
                i += 2;
                continue;
            }
            if (c == 'X' && s[i+1] == 'C') {
                value += 90;
                --remaining;
                i += 2;
                continue;
            }
            if (c == 'C' && s[i+1] == 'D') {
                value += 400;
                --remaining;
                i += 2;
                continue;
            }
            if (c == 'C' && s[i+1] == 'M') {
                value += 900;
                --remaining;
                i += 2;
                continue;
            }
        }

        switch (c) {
        case 'I':
            value += 1;
            ++i;
            break;
        case 'V':
            value += 5;
            ++i;
            break;
        case 'X':
            value += 10;
            ++i;
            break;
        case 'L':
            value += 50;
            ++i;
            break;
        case 'C':
            value += 100;
            ++i;
            break;
        case 'D':
            value += 500;
            ++i;
            break;
        case 'M':
            value += 1000;
            ++i;
            break;
        }
    }

    return value;
}

struct TestCase {
    std::string input;
    int expected;
};

inline std::string red(std::string_view s, std::ostream& os=std::cout) {
    return "\x1b[31m"s + s.data() + "\x1b[0m";
}

inline std::string green(std::string_view s, std::ostream& os=std::cout) {
    return "\x1b[32m"s + s.data() + "\x1b[0m";
}

void run_tests(std::vector<TestCase>& test_cases) {
    for (auto& test_case: test_cases) {
        auto got = roman_to_int(test_case.input);
        std::cout << "Test " << test_case.input << "; expected " <<
            test_case.expected << "; got " << got;
        const auto& exp = test_case.expected;
        if (got != exp) {
            std::cerr << red(" [FAIL]\n");
            continue;
        }
        std::cout << green(" [OK]\n");
    }
}

int main() {
    std::vector<TestCase> test_cases{
        {"I", 1},
        {"II", 2},
        {"III", 3},
        {"IV", 4},
        {"V", 5},
        {"VI", 6},
        {"VII", 7},
        {"VIII", 8},
        {"IX", 9},
        {"X", 10},
        {"XI", 11},
        {"XII", 12},
        {"XIII", 13},
        {"XIV", 14},
        {"XV", 15},
        {"XX", 20},
        {"XXIX", 29},
        {"XLIX", 49},
        {"XCIX", 99},
        {"CII", 102},
        {"CCCLXV", 365},
        {"CDLXXXVI", 486},
        {"DXII", 512},
        {"DCCCXCII", 892},
        {"MMMCMXCIX", 3999},
    };
    run_tests(test_cases);
}

