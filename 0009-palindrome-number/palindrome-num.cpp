/**
 * PALINDROME-NUM.CPP
 * 
 * https://leetcode.com/problems/palindrome-number/
 * 
 * Andre Zunino <neyzunino@gmail.com>
 * 18 March 2021
 */

#include <algorithm>
#include <ios>
#include <iterator>
#include <limits>
#include <string_view>
#include <string>
#include <vector>
#include <iostream>

using namespace std::string_literals;

constexpr int MAX_INT_TENTH = std::numeric_limits<int>::max() / 10;

bool is_palindrome(int x) {
    if (x < 0) {
        return false;
    }
    int normal = x;
    int reversed = 0;
    for (; x != 0; x /= 10) {
        unsigned char digit = x % 10;
        if (reversed > MAX_INT_TENTH) {
            return false;
        }
        reversed = reversed * 10 + digit;
    }
    return reversed == normal; 
}

struct TestCase {
    int input;
    bool expected;
};

inline std::string red(std::string_view s, std::ostream& os=std::cout) {
    return "\x1b[31m"s + s.data() + "\x1b[0m";
}

inline std::string green(std::string_view s, std::ostream& os=std::cout) {
    return "\x1b[32m"s + s.data() + "\x1b[0m";
}

void run_tests(std::vector<TestCase>& test_cases) {
    for (auto& test_case: test_cases) {
        auto got = is_palindrome(test_case.input);
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
    std::cout << std::boolalpha;
    std::vector<TestCase> test_cases{
        {121, true},
        {-121, false},
        {10, false},
        {-101, false},
        {1'234'567'899, false},
    };
    run_tests(test_cases);
}

