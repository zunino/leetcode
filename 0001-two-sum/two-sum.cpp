/**
 * TWO-SUM.CPP
 * 
 * https://leetcode.com/problems/two-sum/
 * 
 * Andre Zunino <neyzunino@gmail.com>
 * 10 March 2021
 */

#include <utility>
#include <vector>
#include <map>
#include <exception>
#include <iostream>

std::pair<std::size_t, std::size_t> two_sum(const std::vector<int>& nums, int target) {
    std::size_t size = nums.size();
    std::map<int, std::size_t> complements;
    std::size_t i = 0;
    for (;; ++i) {
        int num = nums[i];
        auto iter = complements.find(num);
        if (iter != std::end(complements)) {
            return {iter->second, i};
        }
        complements[target - num] = i;
    }
    throw std::invalid_argument{"Invalid input sequence"};
}

struct TestCase {
    std::vector<int> nums;
    int target;
    std::pair<std::size_t, std::size_t> expected;
};

std::ostream& operator<<(std::ostream& os, const std::pair<std::size_t, std::size_t>& pair) {
    return os << '(' << pair.first << ", " << pair.second << ')';
}

std::ostream& operator<<(std::ostream& os, const std::vector<int>& nums) {
    os << '[';
    for (std::size_t i = 0; i < nums.size(); ++i) {
        if (i != 0) {
            os << ", ";
        }
        os << nums[i];
    }
    return os << ']';
}

void run_tests(const std::vector<TestCase>& test_cases) {
    for (auto& test_case: test_cases) {
        auto got = two_sum(test_case.nums, test_case.target);
        std::cout << "Test " << test_case.nums << " with target " <<
            test_case.target << " | expected " << test_case.expected <<
            "; got " << got;
        const auto& exp = test_case.expected;
        if (got != exp && got != decltype(exp){exp.second, exp.first}) {
            std::cerr << " [FAIL]\n";
            continue;
        }
        std::cout << " [OK]\n";
    }
}

int main() {
    std::vector<TestCase> test_cases = {
        {{2, 7, 11, 15}, 9, {0, 1}},
        {{3, 2, 4}, 6, {1, 2}},
        {{3, 3}, 6, {0, 1}},
        {{-10, -1, -18, -19}, -19, {1, 2}},
    };
    run_tests(test_cases);
}

