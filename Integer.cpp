//
// Created by diego on 5/26/20.
//

#include "Integer.h"
#include <climits>
#include <stdexcept>

// If x and y are both negatives (can overflow)
// this function makes both values positives so I can check overflow
// normally, I subtract 1 as |INT_MIN| = INT_MAX + 1
void Integer::handle_negative_values(int &x, int &y) {
    if (x == INT_MIN) {
        y = -y;
        x = INT_MAX;
    } else {
        if (y == INT_MIN) {
            x = -x;
            y = INT_MAX;
        } else {
            x = -x;
            y = -y -1;
        }
    }
}

int Integer::add(int x, int y) {
    // Only different case is when x and y are both negatives
    if (x < 0 && y < 0) {
        handle_negative_values(x, y);
        int result = get_sum(x, y);
        if (result == INT_MAX)
            throw std::runtime_error("Operation overflows integer value");
        return -result - 1;
    }

    return get_sum(x, y);
}

// I check if bit in position 31 is set as this would make overflow
// when x and y have different signs, add won't overflow
bool Integer::positive_overflows(const int &x, const int &y, const int &carry) {
    if (x > 0 && y > 0) {
        // Check if bit in position 31 is set
        if (carry & (1<<30))
            return true;
    }
    return false;
}

// Half adder O(log(x+y))
int Integer::get_sum(int x, int y) {
    int result = x;
    int remaining = y;
    // Until there is no more to sum
    while (remaining != 0) {
        // Check when both bits are set as this is going to be a carry operation
        int carry = result & remaining;
        // Sum between bits
        result = result ^ remaining;
        if (positive_overflows(x, y, carry))
            throw std::runtime_error("Operation overflows integer value");
        // now I sum the carry bits moved to the next left bit
        remaining = carry << 1;
    }
    return result;
}
