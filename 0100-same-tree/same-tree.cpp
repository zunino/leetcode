/**
 * SAME-TREE.CPP
 * 
 * https://leetcode.com/problems/same-tree/
 * 
 * Andre Zunino <neyzunino@gmail.com>
 * Created 30 March 2021
 * Modified 31 March 2021
 */

#include <bits/c++config.h>
#include <iterator>
#include <string_view>
#include <string>
#include <vector>
#include <deque>
#include <limits>
#include <iostream>

using namespace std::string_literals;

constexpr int EMPTY = std::numeric_limits<int>::min();

struct TreeNode {
    TreeNode() {}
    TreeNode(int v) : val{v} {}
    TreeNode(int v, TreeNode* left, TreeNode* right) : val{v}, left{left}, right{right} {}
    int val = 0;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
};

TreeNode* make_tree(const std::vector<int>& elems) {
    const unsigned short len = elems.size();
    if (len == 0) {
        return nullptr;
    }
    std::vector<TreeNode*> nodes{len};
    TreeNode* root = new TreeNode{elems[0]};
    nodes[0] = root;
    for (short i = 0; i < len; ++i) {
        TreeNode* node = nodes[i];
        short left_idx = 2*i + 1;
        short right_idx = left_idx + 1;
        if (left_idx < len) {
            int value = elems[left_idx];
            if (value != EMPTY) {
                TreeNode* left_child = new TreeNode{value};
                node->left = left_child;
                nodes[left_idx] = left_child;
            }
        }
        if (right_idx < len) {
            int value = elems[right_idx];
            if (value != EMPTY) {
                TreeNode* right_child = new TreeNode{value};
                node->right = right_child;
                nodes[right_idx] = right_child;
            }
        } else {
            break;
        }
    }
    return root;
}

void delete_tree(TreeNode* node) {
    if (!node) {
        return;
    }
    TreeNode* left = node->left;
    TreeNode* right = node->right;
    if (left) {
        delete_tree(left);
    }
    if (right) {
        delete_tree(right);
    }
    delete node;
}

void print_tree(TreeNode* tree, std::ostream& os=std::cout) {
    if (!tree) {
        return;
    }
    std::deque<TreeNode*> nodes;
    nodes.push_back(tree);
    unsigned char nodes_per_line = 1;
    unsigned char nodes_printed = 0;
    while (!nodes.empty()) {
        TreeNode* node = nodes.front();
        nodes.pop_front();
        if (node) {
            os << node->val << ' ';
        } else {
            os << "- ";
        }
        ++nodes_printed;
        if (nodes_printed == nodes_per_line) {
            os << '\n';
            nodes_per_line *= 2;
            nodes_printed = 0;
        }
        if (!node) continue;
        TreeNode* left = node->left;
        TreeNode* right = node->right;
        nodes.push_back(left);
        nodes.push_back(right);
    }
    os << '\n';
}

bool is_same_tree(TreeNode* t1, TreeNode* t2) {
    if (t1 == t2) {
        return true;
    }
    if (t1 && t2) {
        std::deque<TreeNode*> nodes_1;
        std::deque<TreeNode*> nodes_2;
        nodes_1.push_back(t1);
        nodes_2.push_back(t2);
        while (!nodes_1.empty()) {
            if (nodes_2.empty()) {
                return false;
            }

            TreeNode* n1 = nodes_1.front();
            nodes_1.pop_front();
           
            TreeNode* n2 = nodes_2.front();
            nodes_2.pop_front();

            if (!n1 && !n2) {
                continue;
            }
            if (!n1 || !n2) {
                return false;
            }
            if (n1->val != n2->val) {
                return false;
            }

            nodes_1.push_back(n1->left);
            nodes_1.push_back(n1->right);

            nodes_2.push_back(n2->left);
            nodes_2.push_back(n2->right);
        }
        if (!nodes_2.empty()) {
            return false;
        }
        return true;
    }
    return false;
}

struct TestCase {
    std::vector<int> tree_1;
    std::vector<int> tree_2;
    bool expected;
};

std::ostream& operator<<(std::ostream& os, const std::vector<int> v) {
    os << '[';
    for (int e : v) {
        if (e != EMPTY) {
            os << e << ' ';
            continue;
        }
        os << "- ";
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
        TreeNode* tree_1 = make_tree(test_case.tree_1);
        TreeNode* tree_2 = make_tree(test_case.tree_2);
        auto got = is_same_tree(tree_1, tree_2);
        delete_tree(tree_2);
        delete_tree(tree_1);
        std::cout << "Test " << test_case.tree_1 << '|' << test_case.tree_2
            << "; expected " << test_case.expected << "; got " << got;
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
        {{}, {}, true},
        {{1,2,3}, {1,2,3}, true},
        {{1,2}, {1,EMPTY,2}, false},
        {{1,2,1}, {1,1,2}, false},
        {{1,2,3,4,5}, {1,2,3,4,5,6}, false},
        {{1,2,3,4,5,EMPTY,6}, {1,2,3,4,5,6}, false},
    };
    run_tests(test_cases);
}

