/**
 * VALID-NUM.CPP
 * 
 * https://leetcode.com/problems/valid-number/
 * 
 * Andre Zunino <neyzunino@gmail.com>
 * 29 March 2021
 */

#include <bits/c++config.h>
#include <ios>
#include <string>
#include <vector>
#include <cctype>
#include <sstream>
#include <iostream>

using namespace std::string_literals;

inline bool parse_integer(std::istream& input, bool terminating=false) {
    unsigned char c;
    input >> c;
    if (c == '+' || c == '-') {
        input >> c;
    }
    if (!std::isdigit(c)) {
        return false;
    }
    while (input >> c && std::isdigit(c));
    if (!input) {
        return true;
    }
    if (terminating) {
        return false;
    }
    if (c == 'e' || c == 'E') {
        return parse_integer(input, true);
    }
    if (!input) {
        return true;
    }
    return false;
}

inline bool parse_decimal(std::istream& input) {
    unsigned char c;
    input >> c;
    if (c == '+' || c == '-') {
        input >> c;
    }
    bool some_digit = false;
    if (std::isdigit(c)) {
        some_digit = true;
        while (input >> c && std::isdigit(c));
    }
    if (c != '.') {
        return false;
    }
    input >> c;
    if (some_digit && !input) {
        return true;
    }
    if (std::isdigit(c)) {
        some_digit = true;
        while (input >> c && std::isdigit(c));
        if (!input) {
            return true;
        }
    }
    if (some_digit && (c == 'e' || c == 'E')) {
        return parse_integer(input, true);
    }
    return false;
}

bool is_number(std::string s) {
    std::istringstream input{s};

    if (parse_decimal(input)) {
        return true;
    }

    input.clear();
    input.seekg(0);

    if (parse_integer(input)) {
        return true;
    }

    return false;
}

struct TestCase {
    std::string input;
    bool expected;
};

inline std::string red(std::string_view s, std::ostream& os=std::cout) {
    return "\x1b[31m"s + s.data() + "\x1b[0m";
}

inline std::string green(std::string_view s, std::ostream& os=std::cout) {
    return "\x1b[32m"s + s.data() + "\x1b[0m";
}

void run_tests(const std::vector<TestCase>& test_cases) {
    for (auto& test_case: test_cases) {
        auto got = is_number(test_case.input);
        std::cout << "Test \"" << test_case.input << '"' <<
            " | expected " << test_case.expected <<
            "; got " << got;
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
        {"0", true},
        {".", false},
        {".1", true},
        {"+10", true},
        {"-110", true},
        {"++110", false},
        {"0089", true},
        {"-0.1", true},
        {"+3.14", true},
        {"4.", true},
        {"-.9", true},
        {"2e10", true},
        {"-90E3", true},
        {"3e+7", true},
        {"+6e-1", true},
        {"+.6e-1", true},
        {"abc", false},
        {"1a", false},
        {"e3", false},
        {"99e2.5", false},
        {"95a54e53", false},
        {"46.e3", true},
        {".e1", false},
        {"92e1740e91", false},
    };
    std::cout << std::boolalpha;
    run_tests(test_cases);
}

