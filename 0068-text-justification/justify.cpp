/**
 * JUSTIFY.CPP
 * 
 * https://leetcode.com/problems/text-justification/
 * 
 * Andre Zunino <neyzunino@gmail.com>
 * 29 March 2021
 */

#include <bits/c++config.h>
#include <iterator>
#include <string_view>
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>

using namespace std::string_literals;

template <typename Iter>
std::string justify_line(Iter from, Iter to, int max_width, short line_len) {
    short word_count = std::distance(from, to);
    short location_count = word_count - 1;
    short needed_space = max_width - line_len;
    short base_spaces = needed_space / location_count;
    short extra_spaces = needed_space % location_count;
    std::string line;
    line.reserve(max_width);
    for (Iter it = from; it != to; ++it) {
        line += *it;
        if (it == to-1) {
            break;
        }
        line += std::string(base_spaces, ' ');
        if (extra_spaces-- > 0) {
            line += ' ';
        }
    }
    return line;
}

template <typename Iter>
std::string justify_line_left(Iter from, Iter to, int max_width, short line_len) {
    std::string line;
    line.reserve(max_width);
    for (Iter it = from; it != to; ++it) {
        line += *it;
        if (it == to-1) {
            break;
        }
        line += ' ';
    }
    line.resize(max_width, ' ');
    return line;
}

std::vector<std::string> full_justify(std::vector<std::string>& words, int max_width) {
    auto p1 = std::begin(words);
    auto p2 = p1;

    std::vector<std::string> justified;

    while (p2 != std::end(words)) {
        short line_len = p1->length();
        short eff_line_len = line_len;
        short next_len = 0;

        while (++p2 != std::end(words)) {
            next_len = 1 + p2->length();
            if (line_len + next_len > max_width) {
                break;
            }
            line_len += next_len;
            eff_line_len += next_len - 1;
        }

        if (std::distance(p1, p2) == 1 || p2 == std::end(words)) {
            justified.push_back(justify_line_left(p1, p2, max_width, eff_line_len));
        } else {
            justified.push_back(justify_line(p1, p2, max_width, eff_line_len));
        }
        p1 = p2;
    }

    return justified;
}

struct TestCase {
    std::vector<std::string> words;
    int max_width;
    std::vector<std::string> expected;
};

std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& v) {
    os << '[';
    for (auto& s : v) {
        os << s << ' ';
    }
    if (v.size() > 0) {
        os << '\b';
    }
    return os << ']';
}

void justified_(std::ostream& os, const std::vector<std::string>& v, short width) {
    for (auto& s : v) {
        os << '|' << std::setw(width) << s << "|\n";
    }
}

inline std::string red(std::string_view s, std::ostream& os=std::cout) {
    return "\x1b[31m"s + s.data() + "\x1b[0m";
}

inline std::string green(std::string_view s, std::ostream& os=std::cout) {
    return "\x1b[32m"s + s.data() + "\x1b[0m";
}

void run_tests(std::vector<TestCase>& test_cases) {
    for (auto& test_case: test_cases) {
        auto got = full_justify(test_case.words, test_case.max_width);
        std::cout << "Test " << test_case.words << " width " << test_case.max_width
            << "; got \n";
        justified_(std::cout, got, test_case.max_width);
        const auto& exp = test_case.expected;
        if (got != exp) {
            std::cerr << red("[FAIL]\n");
            continue;
        }
        std::cout << green("[OK]\n");
    }
}

int main() {
    std::vector<TestCase> test_cases{
        {
            {"This","is","an","example","of","text","justification."}, 16,
            {
                "This    is    an",
                "example  of text",
                "justification.  "
            }
        },
        {
            {"What","must","be","acknowledgement","shall","be"}, 16,
            {
                "What   must   be",
                "acknowledgement ",
                "shall be        "
            }
        },
        {
            {"Science","is","what","we","understand","well","enough","to",
             "explain","to","a","computer.","Art","is","everything","else",
             "we","do."}, 20,
            {
                "Science  is  what we",
                "understand      well",
                "enough to explain to",
                "a  computer.  Art is",
                "everything  else  we",
                "do.                 "
            }
        },
        {
            {"Single"}, 10,
            {"Single    "}
        },
    };
    run_tests(test_cases);
}

