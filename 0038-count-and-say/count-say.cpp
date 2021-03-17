/**
 * COUNT-SAY.CPP
 * 
 * https://leetcode.com/problems/count-and-say/
 * 
 * Andre Zunino <neyzunino@gmail.com>
 * 17 March 2021
 */

#include <bits/c++config.h>
#include <string_view>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std::string_literals;

std::string count_and_say(unsigned short n) {
    if (n == 1) {
        return "1";
    }
    std::string s = count_and_say(n-1);
    std::stringstream result;
    for (unsigned short i = 0; i < s.size();) {
        unsigned char c = s[i];
        unsigned short c_count = 0;
        while (i < s.size() && s[i] == c) {
            ++c_count;
            ++i;
        }
        result << c_count << c;
    }
    return result.str();
}

struct TestCase {
    unsigned short input;
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
        auto got = count_and_say(test_case.input);
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
        {1, "1"},
        {2, "11"},
        {3, "21"},
        {4, "1211"},
        {5, "111221"},
        {6, "312211"},
        {10, "13211311123113112211"},
    };
    run_tests(test_cases);
}

