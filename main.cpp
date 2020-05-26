#include <vector>
#include <climits>
#include <stdexcept>
#include <cassert>
#include "Integer.h"
#include "Collection.h"

// Just so this main is cleaner
using namespace  std;

// This and get_vector_sum could be created in a Util class
void test_add_exception(int x, int y) {
    bool exception_thrown = false;
    try {
        Integer::add(x, y);
    } catch(runtime_error) {
        exception_thrown = true;
    }
    assert(exception_thrown);
}

uint32_t get_vector_sum(vector<uint32_t> &V) {
    int sum = 0;
    for(int i=0; i<V.size(); ++i)
        sum += V[i];
    return sum;
}

void test_integer() {
    assert(Integer::add(1, 1) == 2);
    assert(Integer::add(0, 1) == 1);
    assert(Integer::add(-1, -2) == -3);
    assert(Integer::add(-1, 1) == 0);
    assert(Integer::add(-2000, 2500) == 500);
    assert(Integer::add(INT_MIN, 0) == INT_MIN);
    assert(Integer::add(INT_MAX, -1) == INT_MAX - 1);
    test_add_exception(INT_MIN, -1);
    test_add_exception(INT_MAX, 1);
    test_add_exception(2000000000, 2000000000);
}

// I should be a new object as is passed by reference
void test_largest_sum_case(uint32_t T, vector<uint32_t> I, uint32_t answer) {
    vector<uint32_t> M;
    uint32_t S;
    Collection::find_largest_sum(T, I, M, S);
    assert(S == answer);
    assert(get_vector_sum(M) == answer);
}

void test_largest_sum() {
    test_largest_sum_case(11, vector<uint32_t> {1, 2, 3, 4, 5, 6, 7}, 11);
    test_largest_sum_case(0, vector<uint32_t> {1, 2, 3, 4, 5, 6, 7}, 0);
    test_largest_sum_case(2, vector<uint32_t> {10, 20, 3, 4, 5, 6, 7}, 0);
    test_largest_sum_case(2, vector<uint32_t> {}, 0);
    test_largest_sum_case(2, vector<uint32_t> {1}, 1);
    test_largest_sum_case(125, vector<uint32_t> {1000000}, 0);
    test_largest_sum_case(125, vector<uint32_t> {1000000, 1}, 1);
}

int main() {
    test_integer();
    test_largest_sum();
    return 0;
}
