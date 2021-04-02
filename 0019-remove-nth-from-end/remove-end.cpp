/**
 * REMOVE-END.CPP
 * 
 * https://leetcode.com/problems/remove-nth-node-from-end-of-list/
 * 
 * Andre Zunino <neyzunino@gmail.com>
 * 2 April 2021
 */

#include <bits/c++config.h>
#include <iterator>
#include <string_view>
#include <string>
#include <vector>
#include <stack>
#include <iostream>

using namespace std::string_literals;

struct ListNode {
    ListNode() {}
    ListNode(int v) : val{v} {}
    ListNode(int v, ListNode* next) : val{v}, next{next} {}
    int val = 0;
    ListNode* next = nullptr;
};

ListNode* make_list(const std::vector<int>& elements) {
    if (elements.empty()) {
        return nullptr;
    }
    ListNode* root = new ListNode{elements[0]};
    ListNode* node = root;
    for (short n = 1; n < elements.size(); ++n) {
        ListNode* next_node = new ListNode{elements[n]};
        node->next = next_node;
        node = next_node;
    }
    return root;
}

void delete_list(const ListNode* node) {
    while (node) {
        ListNode* next_node = node->next;
        delete node;
        node = next_node;
    }
}

bool compare_lists(const ListNode* l1, const ListNode* l2) {
    if (l1 == l2) {
        return true;
    }
    while (l1) {
        if (!l2) return false;
        if (l1->val != l2->val) return false;
        l1 = l1->next;
        l2 = l2->next;
    }
    if (l2) return false;
    return true;
}

ListNode* remove_nth_from_end(ListNode* list, int ridx) {
    short len = 0;
    for (ListNode* node = list; node; node = node->next) {
        ++len;
    }
    short prev_idx = len - ridx - 1;
    ListNode* removed_node;
    if (prev_idx < 0) {   // removed node is the head of the list
        removed_node = list;
        list = list->next;
    } else {
        ListNode* prev_node = list;
        for (short i = 0; i < prev_idx; ++i) {
            prev_node = prev_node->next;
        }
        removed_node = prev_node->next;
        prev_node->next = prev_node->next->next;
    }
    delete removed_node;
    return list;
}

struct TestCase {
    std::vector<int> elems;
    int ridx;
    std::vector<int> expected;
};

std::ostream& operator<<(std::ostream& os, const ListNode* node) {
    if (!node) {
        return os << '.';
    }
    while (node) {
        os << node->val;
        if (node->next) {
            os << "⤏ ";
        }
        node = node->next;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<int>& v) {
    os << '[';
    for (auto& e : v) {
        os << e << ' ';
    }
    if (!v.empty()) {
        os << '\b';
    }
    return os << ']';
}

inline std::string red(std::string_view s, std::ostream& os=std::cout) {
    return "\x1b[31m"s + s.data() + "\x1b[0m";
}

inline std::string green(std::string_view s, std::ostream& os=std::cout) {
    return "\x1b[32m"s + s.data() + "\x1b[0m";
}

void run_tests(std::vector<TestCase>& test_cases) {
    for (auto& test_case: test_cases) {
        ListNode* original_list = make_list(test_case.elems);
        ListNode* expected_list = make_list(test_case.expected);
        std::cout << "Test " << original_list << " ridx " << test_case.ridx
            << "; expected " << expected_list;
        auto modified_list = remove_nth_from_end(original_list, test_case.ridx);
        std::cout << "; got " << modified_list;
        if (!compare_lists(modified_list, expected_list)) {
            std::cerr << red(" [FAIL]\n");
            continue;
        }
        std::cout << green(" [OK]\n");
        delete_list(expected_list);
        delete_list(modified_list);
    }
}

int main() {
    std::vector<TestCase> test_cases{
        {{1,2}, 1, {1}},
        {{1,2,3,4,5}, 2, {1,2,3,5}},
        {{1}, 1, {}},
        {{1,2,3}, 3, {2,3}},
    };
    run_tests(test_cases);
}

