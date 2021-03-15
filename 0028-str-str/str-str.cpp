/**
 * STRSTR.CPP
 * 
 * https://leetcode.com/problems/implement-strstr/
 * 
 * Andre Zunino <neyzunino@gmail.com>
 * 14 March 2021
 */

#include <bits/c++config.h>
#include <string>
#include <vector>
#include <iostream>

int str_str(const std::string& haystack, const std::string& needle) {
    if (needle.empty()) {
        return 0;
    }
   
    std::size_t haystack_len = haystack.size();
    std::size_t needle_len = needle.size();
    if (needle_len > haystack_len) {
        return -1;
    }
   
    std::size_t index = 0;
    std::size_t i = 0;

    while (true) {

        /* find start */
        while (i < haystack_len && haystack[i] != needle[0]) {
            ++i;
        }
        if (haystack_len - i < needle_len) {
            return -1;
        }

        index = i;

        /* check needle's remaining characters */
        std::size_t j = 1;
        for (; j < needle_len; ++j) {
            if (haystack[++i] != needle[j]) {
                break;
            }
        }
        if (j == needle_len) {
            return index;
        }

        i = index + 1;
    }

    if (i == haystack_len) {
        return -1;
    }

    return index;
}

struct TestCase {
    std::string haystack;
    std::string needle;
    int expected;
};

void run_tests(const std::vector<TestCase>& test_cases) {
    for (auto& test_case: test_cases) {
        auto got = str_str(test_case.haystack, test_case.needle);
        std::cout << "Test \"" << test_case.haystack << "\" | \"" <<
            test_case.needle << "\" | expected " << test_case.expected <<
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
        {"hello", "", 0},
        {"hello", "ll", 2},
        {"hello", "ola", -1},
        {"hello goo goodbye", "good", 10},
        {"hello", "hello goo", -1},
        {"mississippi", "issip", 4},
        {" taking the kingdom", "kingd", 12},
    };
    run_tests(test_cases);
}

