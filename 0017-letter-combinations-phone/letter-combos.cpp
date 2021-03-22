/**
 * LETTER-COMBOS.CPP
 * 
 * https://leetcode.com/problems/letter-combinations-of-a-phone-number/
 * 
 * Andre Zunino <neyzunino@gmail.com>
 * 21 March 2021
 */

#include <bits/c++config.h>
#include <cstdint>
#include <map>
#include <string_view>
#include <string>
#include <vector>
#include <iostream>

using namespace std::string_literals;

std::map<unsigned char, std::vector<std::string>> letters{
    {'2', {"a", "b", "c"}},
    {'3', {"d", "e", "f"}},
    {'4', {"g", "h", "i"}},
    {'5', {"j", "k", "l"}},
    {'6', {"m", "n", "o"}},
    {'7', {"p", "q", "r", "s"}},
    {'8', {"t", "u", "v"}},
    {'9', {"w", "x", "y", "z"}},
};

std::vector<std::string> combine(
        const std::vector<std::string>& v1,
        const std::vector<std::string>& v2) {
    std::vector<std::string> combos;
    combos.reserve(v1.size() * v2.size());
    for (const auto& e1 : v1) {
        for (const auto& e2 : v2) {
            combos.push_back(e1 + e2);
        }
    }
    return combos;
}

std::vector<std::string> letter_combinations(const std::string& digits) {
    unsigned short digits_len = digits.length();
    if (digits_len < 1) {
        return {};
    }
    std::vector<std::string> combos = letters[digits[0]];
    if (digits_len == 1) {
        return combos;
    }
    for (unsigned short i = 1; i < digits_len; ++i) {
        combos = combine(combos, letters[digits[i]]);
    }
    return combos;
}

struct TestCase {
    std::string input;
    std::vector<std::string> expected;
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
        std::cout << "Test \"" << test_case.input << "\"; expected \"" <<
            test_case.expected << "\"; got \"";
        auto got = letter_combinations(test_case.input);
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
        {"23", {"ad","ae","af","bd","be","bf","cd","ce","cf"}},
        {"", {}},
        {"2", {"a","b","c"}},
        {"243", {"agd","age","agf","ahd","ahe","ahf","aid","aie","aif",
                 "bgd","bge","bgf","bhd","bhe","bhf","bid","bie","bif",
                 "cgd","cge","cgf","chd","che","chf","cid","cie","cif"}},
    };
    run_tests(test_cases);
}

