/**
 * SUBSTR.CPP
 * 
 * https://leetcode.com/problems/longest-substring-without-repeating-characters/
 * 
 * Andre Zunino <neyzunino@gmail.com>
 * Created 13 March 2021
 * Modified 14 March 2021
 */

#include <algorithm>
#include <bits/c++config.h>
#include <string>
#include <cstring>
#include <array>
#include <vector>
#include <iostream>

namespace {
    constexpr std::size_t BUF_SIZE = 128;
}

int length_of_longest_substring(std::string s) {
    std::array<int, BUF_SIZE> buffer;
    buffer.fill(-1);

    std::size_t max_substr_len = 0;
    std::size_t substr_len = 0;
    int substr_start = 0;
    std::size_t len = s.size();
    for (int i = 0; i < len; ++i) {
        unsigned char c = s[i];
        int last_pos = buffer[c];
        if (last_pos != -1) {
            int j = std::max(last_pos, substr_start-1);
            while (++j < i && s[j] == c);
            substr_start = j;
            substr_len = i - substr_start;
        }
        ++substr_len;
        buffer[c] = i;
        if (substr_len > max_substr_len) {
            max_substr_len = substr_len;
        }
    }

    return max_substr_len;
}

struct TestCase {
    std::string input;
    int expected;
};

void run_tests(const std::vector<TestCase>& test_cases) {
    for (auto& test_case: test_cases) {
        auto got = length_of_longest_substring(test_case.input);
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
        TestCase{"abcabcbb", 3},
        TestCase{"babacad", 3},
        TestCase{"bbbbb", 1},
        TestCase{"pwwkew", 3},
        TestCase{"", 0},
        TestCase{"dvdf", 3},
        TestCase{" a bc dd ", 4},
        TestCase{"ddvdvvvdf ", 4},
        TestCase{" aa  aaba ", 3},
        TestCase{"cdd", 2},
    };
    run_tests(test_cases);
}

