#include <string>
#include <map>
#include <limits>
#include <sstream>
#include <iostream>

constexpr int INT_MIN = -2147483648;
constexpr int INT_MAX = 2147483647;

inline bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

inline bool is_sign(char c) {
    return c == '+' || c == '-';
}

inline bool is_space(char c) {
    return c == ' ';
}

int my_atoi(std::string str) {
    const int len = str.size();
    if (len < 1) return 0;
    int ini_idx = 0;
    for (; ini_idx < len; ++ini_idx) {
        if (!is_space(str[ini_idx])) break;
    }
    if (!is_digit(str[ini_idx]) && !is_sign(str[ini_idx])) {
        return 0;
    }
    int fin_idx = ini_idx + 1;
    for (; fin_idx < len; ++fin_idx) {
        if (!is_digit(str[fin_idx])) {
            break;
        }
    }
    bool has_sign = is_sign(str[ini_idx]);
    bool neg = str[ini_idx] == '-';
    if (has_sign) {
        ini_idx++;
    }
    int num_len = fin_idx - ini_idx;
    if (has_sign && num_len < 1) {
        return 0;
    }
    int value = 0;
    if (num_len > 9) {
        value = neg ? INT_MIN : INT_MAX;
    } else {
        int mult = 1;
        for (int i = 1; i < num_len; ++i) {
            mult *= 10;
        }
        for (int idx = ini_idx; idx < fin_idx; ++idx) {
            int v = (str[idx] - 0x30) * mult;
            value += v;
            mult /= 10;
        }
        if (neg) {
            if (value + INT_MIN > 0) {
                value = INT_MIN;
            } else {
                value *= -1;
            }
        } else if (value > INT_MAX) {
            value = INT_MAX;
        }
    }
    return value;
}

using Test_Data = std::map<std::string, int>;

void run_tests(const Test_Data& test_data) {
    for (const auto& [k, v] : test_data) {
        int got = my_atoi(k);
        std::cout << "Test \"" << k << "\"; expected " << v << "; got " << got;
        if (got != v) {
            std::cerr << " [FAIL]\n";
            continue;
        }
        std::cout << " [OK]\n";
    }
}

int main() {
    Test_Data test_data{
        {"", 0},
        {"4", 4},
        {"42", 42},
        {"-4", -4},
        {"    42", 42},
        {"   -42", -42},
        {"    42  ", 42},
        {"   -42  ", -42},
        {"91283472332", INT_MAX},
        {"-91283472332", INT_MIN},
        {"words and 987", 0},
    };
    run_tests(test_data);
}

