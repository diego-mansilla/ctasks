//
// Created by diego on 5/26/20.
//

#include "Collection.h"

// Main function using dynamic programming O(N*T)
void Collection::find_largest_sum(uint32_t T, const std::vector<uint32_t> &I, std::vector<uint32_t> &M, uint32_t &S) {
    size_t N= I.size();
    // Memo array for the dp function which is long so we can store -1 as a flag value
    // This could be more efficient, but this makes code quite simpler
    std::vector<std::vector<long> > memo = std::vector<std::vector<long> >(T + 1,
                                                                                   std::vector<long> (N + 1, -1));

    S = get_largest_sum(T, 0, 0, I, memo);
    get_sum_subset(T, 0, 0, M, I, memo);
}

// Recursive dynamic programming to get the largest value less than T
// Decision: using a value I[idx] or not
uint32_t Collection::get_largest_sum(const uint32_t &T, int value, int idx, const std::vector<uint32_t> &I,
                                     std::vector<std::vector<long>> &memo) {
    // Base case
    if (idx == I.size())
        return value;
    // As vector is set with unsigned ints, -1 is a flag value
    if (memo[value][idx] != -1)
        return memo[value][idx];
    // Not using I[idx]
    uint32_t ans = get_largest_sum(T, value, idx + 1, I, memo);

    // This comparison might overflow
    if (1LL*value + I[idx] <= 1LL*T)
        // Using I[idx] and storing the maximum value
        ans = std::max(ans, get_largest_sum(T, value + I[idx], idx + 1, I, memo));
    memo[value][idx] = ans;
    return ans;
}

// Function to reconstruct the array based on the DP
void Collection::get_sum_subset(const uint32_t &T, int value, int idx, std::vector<uint32_t> &M,
                                const std::vector<uint32_t> &I, std::vector<std::vector<long>> &memo) {
    // Base case
    if (idx == I.size())
        return;

    uint32_t local_ans = get_largest_sum(T, value, idx + 1, I, memo);
    // If not choosing I[idx] leads to an maximum value
    if (local_ans == memo[value][idx]) {
        get_sum_subset(T, value, idx + 1, M, I, memo);
    } else {
        // Otherwise choosing I[idx] leads to optimum value
        if (1LL*value + I[idx] <= T) {
            local_ans = get_largest_sum(T, value + I[idx], idx + 1, I, memo);
            if (local_ans == memo[value][idx]) {
                M.push_back(I[idx]);
                get_sum_subset(T, value + I[idx], idx + 1, M, I, memo);
            }
        }
    }
}
