/**
 * PARENS.CPP
 * 
 * https://leetcode.com/problems/valid-parentheses/
 * 
 * Andre Zunino <neyzunino@gmail.com>
 * 14 March 2021
 */

#include <bits/c++config.h>
#include <ios>
#include <string>
#include <vector>
#include <stack>
#include <iostream>

namespace {
    unsigned char openers[]{'(', '[', '{'};
    unsigned char closers[]{')', ']', '}'};
    constexpr int SYMBOLS_LEN = 3;
}

inline std::size_t index_of(unsigned char c, unsigned char* symbols) {
    for (std::size_t i = 0; i < SYMBOLS_LEN; ++i) {
        if (symbols[i] == c) {
            return i;
        }
    }
    return -1;
}

bool is_valid(std::string s) {
    std::stack<std::size_t> opener_indices;
    std::size_t len = s.size();
    for (std::size_t i = 0; i < len; ++i) {
        char c = s[i];
        if (auto idx = index_of(c, openers); idx != -1) {
            opener_indices.push(idx);
        } else {
            if (opener_indices.empty()) {
                return false;
            }
            auto closer_idx = index_of(c, closers);
            auto opener_idx = opener_indices.top();
            opener_indices.pop();
            if (closer_idx != opener_idx) {
                return false;
            }
        }
    }
    return opener_indices.empty();
}

struct TestCase {
    std::string input;
    bool expected;
};

void run_tests(const std::vector<TestCase>& test_cases) {
    for (auto& test_case: test_cases) {
        auto got = is_valid(test_case.input);
        std::cout << "Test \"" << test_case.input << '"' <<
            " | expected " << test_case.expected <<
            "; got " << got;
        const auto& exp = test_case.expected;
        if (got != exp) {
            std::cerr << " [FAIL]\n";
            continue;
        }
        std::cout << " [OK]\n";
    }
}

int main() {
    std::vector<TestCase> test_cases{
        {"()", true},
        {"()[]{}", true},
        {"(]", false},
        {"([)]", false},
        {"{[]}", true},
        {"[", false},
    };
    std::cout << std::boolalpha;
    run_tests(test_cases);
}

