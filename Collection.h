//
// Created by diego on 5/26/20.
//

#ifndef NEARSOFT_COLLECTION_H
#define NEARSOFT_COLLECTION_H


#include <cstdint>
#include <vector>

class Collection {
public:
    static void find_largest_sum(const uint32_t T, const std::vector<uint32_t> &I, std::vector<uint32_t> &M, uint32_t &S);

private:
    static uint32_t get_largest_sum(const uint32_t &T, int value, int idx,
                             const std::vector<uint32_t> &I, std::vector<std::vector<long> > &memo);

    static void get_sum_subset(const uint32_t &T, int value, int idx, std::vector<uint32_t> &M,
                        const std::vector<uint32_t> &I, std::vector<std::vector<long> > &memo);
};


#endif //NEARSOFT_COLLECTION_H
