//
// Created by diego on 5/26/20.
//

#ifndef NEARSOFT_INTEGER_H
#define NEARSOFT_INTEGER_H


class Integer {
public:
    static int add(int x, int y);
private:
    static bool positive_overflows(const int &x, const int &y, const int &carry);

    static int get_sum(int x, int y);

    static void handle_negative_values(int &x, int &y);
};


#endif //NEARSOFT_INTEGER_H
