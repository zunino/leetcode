/**
 * PREFIX.CPP
 * 
 * https://leetcode.com/problems/longest-common-prefix/
 * 
 * Andre Zunino <neyzunino@gmail.com>
 * 21 March 2021
 */

#include <bits/c++config.h>
#include <iterator>
#include <string_view>
#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std::string_literals;

std::string longest_common_prefix(const std::vector<std::string>& strs) {
    std::string prefix;
    std::uint8_t str_count = strs.size();
    if (str_count > 0) {
        prefix = strs[0];
        for (std::uint8_t i = 1; i < str_count; ++i) {
            std::uint8_t prefix_len = prefix.size();
            if (prefix_len == 0) {
                break;
            }
            const std::string& str = strs[i];
            std::uint8_t str_len = str.size();
            std::uint8_t j;
            for (j = 0; j < prefix_len && j < str_len; ++j) {
                if (str[j] != prefix[j]) {
                    break;
                }
            }
            if (j < prefix_len) {
                prefix.resize(j);
            }
        }
    }
    return prefix;
}

struct TestCase {
    std::vector<std::string> input;
    std::string expected;
};

std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& v) {
    os << '[';
    for (const auto& s : v) {
        os << s << ' ';
    }
    if (!v.empty()) {
        os << '\b';
    }
    os << ']';
    return os;
}

inline std::string red(std::string_view s, std::ostream& os=std::cout) {
    return "\x1b[31m"s + s.data() + "\x1b[0m";
}

inline std::string green(std::string_view s, std::ostream& os=std::cout) {
    return "\x1b[32m"s + s.data() + "\x1b[0m";
}

void run_tests(std::vector<TestCase>& test_cases) {
    for (auto& test_case: test_cases) {
        std::cout << "Test " << test_case.input << "; expected \"" <<
            test_case.expected << "\"; got \"";
        auto got = longest_common_prefix(test_case.input);
        std::cout << got << '\"';
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
        {{}, ""},
        {{""}, ""},
        {{"", "b"}, ""},
        {{"ab", "a"}, "a"},
        {{"flower", "flow", "flight"}, "fl"},
        {{"dog", "racecar", "car"}, ""},
    };
    run_tests(test_cases);
}

