/**
 * ADD-2-NUM.CPP
 * 
 * https://leetcode.com/problems/add-two-numbers/
 * 
 * Andre Zunino <neyzunino@gmail.com>
 * 10 March 2021
 */

#include <stack>
#include <vector>
#include <utility>
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

std::ostream& operator<<(std::ostream& os, const ListNode& node_ref) {
    const ListNode* node = &node_ref;
    while (node) {
        os << node->val;
        if (node->next) {
            os << "->";
        }
        node = node->next;
    }
    return os;
}

int to_int(ListNode* node) {
    std::stack<int> s;
    int multiplier = 1;
    while (node) {
        s.push(node->val);
        node = node->next;
        multiplier *= 10;
    }
    int n = 0;
    multiplier /= 10;
    while (!s.empty()) {
        n += s.top() * multiplier;
        s.pop();
        multiplier /= 10;
    }
    return n;
}

ListNode* add_two_numbers(ListNode* l1, ListNode* l2) {
    int sum = to_int(l1) + to_int(l2);
    std::stack<int> s;
    while (sum > 1) {
        s.push(sum % 10);
        sum /= 10;
    }
    if (s.empty()) {
        s.push(0);
    }
    ListNode* node = new ListNode{s.top()};
    s.pop();
    while (!s.empty()) {
        node = new ListNode{s.top(), node};
        s.pop();
    }
    return node;
}

void delete_nodes(ListNode* node) {
    while (node) {
        ListNode* next = node->next;
        delete node;
        node = next;
    }
}

struct TestCase {
    ListNode* l1;
    ListNode* l2;
    ListNode* expected;
};

ListNode* make_list(std::initializer_list<int>&& items) {
    ListNode* node = nullptr;
    ListNode* other = nullptr;
    for (auto iter = std::rbegin(items); iter != rend(items); ++iter) {
        node = new ListNode{*iter, other};
        other = node;
    }
    return node;
}

TestCase make_test_case(
        std::initializer_list<int>&& l1,
        std::initializer_list<int>&& l2,
        std::initializer_list<int>&& expected) {

    TestCase test_case{
        make_list(std::move(l1)),
        make_list(std::move(l2)),
        make_list(std::move(expected))
    };

    return test_case;
}

bool operator==(const ListNode& node1, const ListNode& node2) {
    const ListNode* l1 = &node1;
    const ListNode* l2 = &node2;
    while (l1) {
        if (!l2 || (l2->val != l1->val)) {
            return false;
        }
        l1 = l1->next;
        l2 = l2->next;
    }
    if (l2) {
        return false;
    }
    return true;
}

void run_test_cases(std::vector<TestCase>& test_cases) {
    for (auto& test : test_cases) {
        ListNode* got = add_two_numbers(test.l1, test.l2);
        std::cout << "Test " << *test.l1 << " | " << *test.l2 <<
            " expected " << *test.expected <<
            " got " << *got;
        if (*got != *test.expected) {
            std::cerr << " [FAIL]\n";
            delete_nodes(got);
            continue;
        }
        std::cout << " [OK]\n";
        delete_nodes(got);
    }
}

int main() {
    std::vector<TestCase> test_cases{
        make_test_case(
            {2, 4, 3},
            {5, 6, 4},
            {7, 0, 8}
        ),
        make_test_case(
            {0},
            {0},
            {0}
        ),
        make_test_case(
            {9, 9, 9, 9, 9, 9, 9},
            {9, 9, 9, 9},
            {8, 9, 9, 9, 0, 0, 0, 1}
        ),
    };
    run_test_cases(test_cases);
}

