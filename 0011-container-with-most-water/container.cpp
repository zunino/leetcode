/**
 * CONTAINER.CPP
 * 
 * https://leetcode.com/problems/container-with-most-water/
 * 
 * Andre Zunino <neyzunino@gmail.com>
 * 27 March 2021
 */

#include <bits/c++config.h>
#include <string_view>
#include <string>
#include <vector>
#include <iostream>

using namespace std::string_literals;

int max_area(const std::vector<int>& height) {
    unsigned i = 0;
    unsigned j = height.size() - 1;
    unsigned max_area = 0;
    while (i < j) {
        unsigned area = (j-i) * std::min(height[i], height[j]);
        max_area = std::max(max_area, area);
        if (height[i] < height[j]) {
            ++i;
        } else {
            --j;
        }
    }
    return max_area;
}

struct TestCase {
    std::vector<int> input;
    int expected;
};

std::ostream& operator<<(std::ostream& os, const std::vector<int>& v) {
    os << '[';
    for (std::size_t i = 0; i < v.size(); ++i) {
        os << v[i] << ' ';
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
        auto got = max_area(test_case.input);
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
        {{1,8,6,2,5,4,8,3,7}, 49},
        {{1,1}, 1},
        {{4,3,2,1,4}, 16},
        {{1,2,1}, 2},
        {{1,8,6,5,4,8,3,7}, 42},
        {{1,2,4,3}, 4},
        {{1,8,6,2,5,4,8,25,7}, 49},
        {{2,3,4,5,18,17,6}, 17},
    };
    run_tests(test_cases);
}

