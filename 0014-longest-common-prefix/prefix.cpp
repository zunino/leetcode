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

struct Node {
    std::map<char, Node*> children;
    bool end = false;
};

Node* build_trie(const std::vector<std::string>& strs) {
    Node* root = new Node;
    for (auto& s : strs) {
        if (s.empty()) {
            root->end = true;
            return root;
        }
        Node* node = root;
        for (char c : s) {
            if (node->children.find(c) == std::end(node->children)) {
                Node* new_node = new Node;
                node->children[c] = new_node;
                node = new_node;
            } else {
                node = node->children[c];
            }
        }
        node->end = true;
    }
    return root;
}

void delete_trie(Node* trie) {
}

std::string longest_common_prefix(const std::vector<std::string>& strs) {
    Node* node = build_trie(strs);
    std::string prefix;
    while (node->children.size() == 1 && !node->end) {
        auto iter = std::begin(node->children);
        prefix += iter->first;
        node = iter->second;
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

