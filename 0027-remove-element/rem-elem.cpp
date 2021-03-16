/**
 * REM-ELEM.CPP
 * 
 * https://leetcode.com/problems/remove-element/
 * 
 * Andre Zunino <neyzunino@gmail.com>
 * Created 15 March 2021
 */

#include <bits/c++config.h>
#include <string>
#include <vector>
#include <iostream>

int remove_element(std::vector<int>& nums, int val) {
    std::size_t len = nums.size();

    if (val > 50 || len == 0) {
        return len;
    }

    short p = 0;
    short q = len - 1;
    short removals = 0;

    while (true) {
        while (p <= q && nums[p] != val) {
            ++p;
        }

        while (q >= p && nums[q] == val) {
            --q;
            ++removals;
        }

        if (p >= q) {
            break;
        }

        nums[p++] = nums[q--];
        ++removals;
    }

    return len - removals;
}

struct TestCase {
    std::vector<int> nums;
    int val;
    int expected;
};

void print(const std::vector<int>& coll, std::ostream& os=std::cout) {
    os << '[';
    for (std::size_t i = 0; i < coll.size(); ++i) {
        if (i > 0) {
            os << ",";
        }
        os << coll[i];
    }
    os << ']';
}

std::ostream& operator<<(std::ostream& os, const TestCase& test_case) {
    print(test_case.nums, os);
    os << " | " << test_case.val << " | expected " << test_case.expected;
    return os;
}

void run_tests(std::vector<TestCase>& test_cases) {
    for (auto& test_case: test_cases) {
        std::cout << "Test " << test_case << ": ";
        auto got = remove_element(test_case.nums, test_case.val);
        print(test_case.nums);
        std::cout << "; got " << got;
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
        {{}, 1, 0},
        {{1}, 1, 0},
        {{2}, 1, 1},
        {{1,2,3,4}, 10, 4},
        {{1,2,3,4}, 51, 4},
        {{3,2,2,3}, 3, 2},
        {{0,1,2,2,3,0,4,2}, 2, 5},
        {{1,1,1,1,1}, 1, 0},
        {{0,0,1}, 1, 2},
    };
    run_tests(test_cases);
}

