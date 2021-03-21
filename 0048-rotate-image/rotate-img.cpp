/**
 * ROTATE-IMG.CPP
 * 
 * https://leetcode.com/problems/rotate-image/
 *
 * Initial implementation using a strategy that consists on rotating numbers on
 * the outer perimeter and gradually moving towards the center. The algorithm
 * produces the correct behavior but there's certainly room for improvement.
 * 
 * Andre Zunino <neyzunino@gmail.com>
 * Created 20 March 2021
 * Modified 21 March 2021
 */

#include <cstdint>
#include <bits/c++config.h>
#include <string_view>
#include <string>
#include <vector>
#include <iostream>

using namespace std::string_literals;

struct Position {
    std::uint8_t row;
    std::uint8_t col;
};

inline Position rotated_pos(std::uint8_t cur_row, std::uint8_t cur_col,
        std::uint8_t dim) {
    return {cur_col, static_cast<std::uint8_t>(dim - 1 - cur_row)};
}

void rotate(std::vector<std::vector<int>>& matrix) {
    std::uint8_t n = matrix.size();
    std::uint8_t half_rows = n / 2;
    for (std::uint8_t i = 0; i < half_rows; ++i) {
        const std::uint8_t col_limit = (n - i - 1);
        for (std::uint8_t j = i; j < col_limit; ++j) {
            std::uint8_t row = i;
            std::uint8_t col = j;
            int value = matrix[row][col];
            for (std::uint8_t c = 0; c < 4; ++c) {
                auto [new_row, new_col] = rotated_pos(row, col, n);
                int tmp = matrix[new_row][new_col];
                matrix[new_row][new_col] = value;
                value = tmp;
                row = new_row;
                col = new_col;
            }
        }
    }
}

struct TestCase {
    std::vector<std::vector<int>> input;
    std::vector<std::vector<int>> expected;
};

std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<int>>& m) {
    os << '[';
    for (std::size_t i = 0; i < m.size(); ++i) {
        const auto& row = m[i];
        os << '[';
        for (std::size_t j = 0; j < row.size(); ++j) {
            os << row[j];
            if (j != row.size()-1) {
                os << ' ';
            }
        }
        os << ']';
        if (i != m.size()-1) {
            os << ' ';
        }
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
        std::cout << "Test " << test_case.input << "; expected " <<
            test_case.expected << "; got ";
        rotate(test_case.input);
        auto got = test_case.input;
        std::cout << got;
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
        {
            {{1}},
            {{1}}
        },
        {
            {{1,2,3},{4,5,6},{7,8,9}},
            {{7,4,1},{8,5,2},{9,6,3}}
        },
        {
            {{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16}},
            {{15,13,2,5},{14,3,4,1},{12,6,8,9},{16,7,10,11}}
        },
    };
    run_tests(test_cases);
}

