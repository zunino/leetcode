/**
 * ADD-2-NUM.CPP
 * 
 * https://leetcode.com/problems/add-two-numbers/
 * 
 * Since the sum result should also be given as a reversed linked list, the
 * trick was in realizing the nodes had to be pre-allocated. I wonder if
 * there's a different mathematical approach that would allow for a simpler
 * solution.
 *
 * Andre Zunino <neyzunino@gmail.com>
 * Created 10 March 2021
 * Modified 12 March 2021
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

ListNode* add_two_numbers(ListNode* l1, ListNode* l2) {
    ListNode* head = new ListNode;
    ListNode* node = head;
    ListNode* prev = nullptr;
    int carry_over = 0;
    while (l1 && l2) {
        int sum = l1->val + l2->val + carry_over;
        carry_over = 0;
        if (sum > 9) {
            carry_over = 1;
            sum -= 10;
        }
        node->val = sum;
        node->next = new ListNode;
        prev = node;
        node = node->next;
        l1 = l1->next;
        l2 = l2->next;
    }
    if (l1 || l2) {
        ListNode* l = l1 ? l1 : l2;
        while (l) {
            int sum = l->val + carry_over;
            carry_over = 0;
            if (sum > 9) {
                carry_over = 1;
                sum -= 10;
            }
            node->val = sum;
            node->next = new ListNode;
            prev = node;
            node = node->next;
            l = l->next;
        }
    }
    if (carry_over == 0) {
        delete prev->next;
        prev->next = nullptr;
    } else {
        node->val = 1;
    }
    return head;
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
    for (auto iter = std::rbegin(items); iter != rend(items); ++iter) {
        node = new ListNode{*iter, node};
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

void delete_test_cases(const std::vector<TestCase>& test_cases) {
    for (const TestCase& test : test_cases) {
        delete_nodes(test.expected);
        delete_nodes(test.l2);
        delete_nodes(test.l1);
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
        make_test_case(
            {1, 5, 7},
            {9, 4, 2},
            {0, 0, 0, 1}
        ),
    };
    run_test_cases(test_cases);
    delete_test_cases(test_cases);
}

