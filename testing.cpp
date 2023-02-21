#include "src/global.h"
#include "src/utils.h"
#include "src/poker_algorithms_new.h"
#include "src/poker_algorithms_old.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <array>

using namespace std;

int main(){
    array<Card, 7> test_cards = {Card(13, 3), Card(12, 2), Card(11, 1), Card(10, 4), Card(9, 3), Card(8, 2), Card(7, 1)};
    Hand hand = poker_algo_new::get_best_hand_not_sorted(test_cards);
    return 0;
}
