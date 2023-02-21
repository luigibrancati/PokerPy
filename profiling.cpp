#include "src/global.h"
#include "src/utils.h"
#include "src/poker_algorithms_new.h"
#include "src/poker_algorithms_old.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <array>
#include <iterator>
#include <algorithm>
#include <random>

using namespace std;

// static array<Card, 52> generate_all_cards(){
//     array<Card, 52> all_cards;
//     for(int v = 13; v>1; v--){
//         for(int s = 4; s>0; s--){
//             all_cards[(s-1)*(v-2) + (s-1)] = Card(v, s);
//         }
//     }
//     sort_cards<array<Card, 52>>(all_cards);
//     return all_cards;
// }

int main(){
    // array<Card, 52> all_cards = generate_all_cards();
    vector<vector<Card>> test_cards = {{Card(13, 4), Card(12, 4)}, {Card(11, 4), Card(10, 4)}};
    // sample(all_cards.begin(), all_cards.end(), test_cards.begin(), 7, mt19937{random_device{}()});
    for (int i = 0; i < 10; i++) {
        poker_algo_new::calculate_hand_frequency(test_cards, {});
    }
    return 0;
}
