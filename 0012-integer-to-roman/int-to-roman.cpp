/**
 * INT-TO-ROMAN.CPP
 * 
 * https://leetcode.com/problems/integer-to-roman/
 * 
 * Andre Zunino <neyzunino@gmail.com>
 * 19 March 2021
 */

#include <bits/c++config.h>
#include <iterator>
#include <string_view>
#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std::string_literals;

const std::map<unsigned short, std::vector<std::string>> roman_values{
    {1, {"I",  "X",  "C", "M"}},
    {4, {"IV", "XL", "CD"}},
    {5, {"V",  "L",  "D"}},
    {9, {"IX", "XC", "CM"}},
};

inline bool is_exception(unsigned char digit) {
    return digit == 4 || digit == 5 || digit == 9;
}

std::string int_to_roman(int num) {
    std::vector<std::string> parts;
    for (unsigned short pos = 0; num != 0; num /= 10, ++pos) {
        unsigned char digit = num % 10;
        if (is_exception(digit)) {
            parts.push_back(roman_values.at(digit)[pos]);
            continue;
        }
        unsigned char repeating_char = roman_values.at(1)[pos][0];
        if (digit < 4) {
            parts.push_back(std::string(digit, repeating_char));
        } else if (digit > 5 && digit < 9) {
            parts.push_back(std::string(digit-5, repeating_char));
            parts.push_back(roman_values.at(5)[pos]);
        }
    }
    std::string result;
    for (auto iter = std::crbegin(parts); iter != std::crend(parts); iter++) {
        result.append(*iter);
    }
    return result;
}

struct TestCase {
    int input;
    std::string expected;
};

inline std::string red(std::string_view s, std::ostream& os=std::cout) {
    return "\x1b[31m"s + s.data() + "\x1b[0m";
}

inline std::string green(std::string_view s, std::ostream& os=std::cout) {
    return "\x1b[32m"s + s.data() + "\x1b[0m";
}

void run_tests(std::vector<TestCase>& test_cases) {
    for (auto& test_case: test_cases) {
        auto got = int_to_roman(test_case.input);
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
        {1, "I"},
        {2, "II"},
        {3, "III"},
        {4, "IV"},
        {5, "V"},
        {6, "VI"},
        {7, "VII"},
        {8, "VIII"},
        {9, "IX"},
        {10, "X"},
        {11, "XI"},
        {12, "XII"},
        {13, "XIII"},
        {14, "XIV"},
        {15, "XV"},
        {20, "XX"},
        {29, "XXIX"},
        {49, "XLIX"},
        {58, "LVIII"},
        {99, "XCIX"},
        {102, "CII"},
        {365, "CCCLXV"},
        {486, "CDLXXXVI"},
        {512, "DXII"},
        {892, "DCCCXCII"},
        {1994, "MCMXCIV"},
        {3999, "MMMCMXCIX"},
    };
    run_tests(test_cases);
}

