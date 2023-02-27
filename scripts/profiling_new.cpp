#include "src/global.h"
#include "src/utils.h"
#include "src/poker_algorithms_new.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <array>

using namespace std;

int main(){
    vector<vector<Card>> test_cards = {{Card(13, 4), Card(12, 4)}, {Card(11, 4), Card(10, 4)}, {Card(3, 4), Card(2, 4)}};
    for (int i = 0; i < 10; i++) {
        poker_algo_new::calculate_hand_frequency(test_cards, {});
    }
    return 0;
}
