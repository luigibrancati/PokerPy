#ifndef _POKER_UTILS_H
#define _POKER_UTILS_H

#include "global.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

template<class T>
void sort_cards(T& cards) {
    std::sort(cards.begin(), cards.end(), [](Card& a, Card& b){return (a>=b);});
}

string round_float(float a,int num_decimals) {
    int temp = round(a*pow(10,num_decimals));
    string total_number = to_string((float) temp/(pow(10,num_decimals)));
    return total_number.substr(0,total_number.find(".")+2);
}

int binomial_coefficient(const uint8_t n, const uint8_t k) {
    if (k == 0) {
        return 1;
    }
    int step1;
    int step0 = n - k + 1;
    for (uint8_t i = 1; i < k; ++i) {
        step1 = step0 * (n - k + 1 + i) / (i + 1);
        step0 = step1;
    }
    return step1;
}

#endif