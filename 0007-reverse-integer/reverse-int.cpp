/**
 * REVERSE-INT.CPP
 * 
 * https://leetcode.com/problems/reverse-integer/
 * 
 * Andre Zunino <neyzunino@gmail.com>
 * Created 17 March 2021
 * Modified 18 March 2021
 */

#include <bits/c++config.h>
#include <string_view>
#include <string>
#include <vector>
#include <limits>
#include <locale>
#include <cmath>
#include <iostream>

using namespace std::string_literals;

constexpr int MIN_INT_TENTH = std::numeric_limits<int32_t>::min()/10;
constexpr int MAX_INT_TENTH = std::numeric_limits<int32_t>::max()/10;

int reverse(int x) {
    int result = 0;
    for (; x != 0; x /= 10) {
        char digit = x % 10;
        if (result > MAX_INT_TENTH) return 0;
        if (result < MIN_INT_TENTH) return 0;
        result = 10 * result + digit;
    }
    return result;
}

struct TestCase {
    int input;
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
        auto got = reverse(test_case.input);
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
    std::locale locale{""};
    std::cout.imbue(locale);
    std::vector<TestCase> test_cases{
        {0, 0},
        {1, 1},
        {10, 1},
        {120, 21},
        {123, 321},
        {-123, -321},
        {1'500, 51},
        {1'282'895, 5'982'821},
        {2'103'282'895, 0},
        {-2'103'282'895, 0},
        {-2'147'483'412, -2'143'847'412},
        {1'534'236'469, 0},
        {-1'534'236'469, 0},
    };
    run_tests(test_cases);
}

