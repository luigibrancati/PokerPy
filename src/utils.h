#ifndef _POKER_UTILS_H
#define _POKER_UTILS_H

#include "global.h"
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;

template<class T>
void sort_cards(T& cards) {
    std::sort(cards.begin(), cards.end(), [](Card& a, Card& b){return (a.value>=b.value);});
}

string round_float(float a,int num_decimals) {
    int temp = round(a*pow(10,num_decimals));
    string total_number = to_string((float) temp/(pow(10,num_decimals)));
    return total_number.substr(0,total_number.find(".")+2);
}

#endif