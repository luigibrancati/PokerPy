#ifndef _ALGORITHMS_NEW_H
#define _ALGORITHMS_NEW_H

#include "global.h"
#include <string>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

namespace algo_new {
    using card_range = pair<int8_t, int8_t>;
    using card_vec = vector<int8_t>;
    const int8_t NULL_PTR = -1;
    const card_range NULL_RANGE = {NULL_PTR, NULL_PTR};
    const uint8_t TOTAL_CARDS = 52;

    template<class T>
    inline void sort_cards(T& cards) {
        std::sort(cards.begin(), cards.end(), [](Card& a, Card& b){return (a>=b);});
    }

    card_vec expand_range(const card_range& range) {
        // Converts two pointers with a range into vector of pointers
        if (range != NULL_RANGE) {
            card_vec card_vec;
            card_vec.reserve(range.second-range.first+1);
            for(int8_t i = range.first; i <= range.second; i++){
                card_vec.push_back(i);
            }
            return card_vec;
        } else {
            return {};
        }
    }

    inline void copy_vec(const array<Card,7>& cards, array<Card, 5>& array, const card_vec& vec) {
        for (int8_t i = 0; i < 5; i++) array[i] = cards[vec[i]];
    }

    inline void sort_vec(card_vec& vec){
        sort(vec.begin(), vec.end(), [](int8_t& a, int8_t& b){return a<=b;});
    }

    card_vec pad_card_vec(card_vec vec, const array<Card,7>& cards, uint8_t N) {
        // Expand a vector of cards by including cards in value order
        // Assumes the cards are ordered in decreasing order
        vec.reserve(N);
        for(int8_t c = 0; (c < cards.size()) && (vec.size() < N); c++) {
            if(find(vec.begin(), vec.end(), c) == vec.end()) {
                vec.push_back(c);
            }
        }
        sort_vec(vec);
        return vec;
    }

    uint8_t count_aces(const array<Card, 7>& array){
        uint8_t count = 0;
        for(Card card:array){
            if(card.value == 13) ++count;
        }
        return count;
    }

    card_vec find_flush(const array<Card,7>& cards) {
        // Returns a vector, either empty or with the 5 cards making a flush
        // Assumes the cards are ordered in decreasing order
        card_vec flush_cards;
        flush_cards.reserve(5);
        for (int8_t start = 0; start < 3; start++){
            Suit s = cards[start].suit;
            uint8_t num_same_suit = 0;
            for (int8_t j = start; j < cards.size(); j++){
                if((num_same_suit < 5) && (cards[j].suit == s)){
                    ++num_same_suit;
                    flush_cards.push_back(j);
                }
            }
            if(num_same_suit>=5){
                return flush_cards;
            } else {
                flush_cards.clear();
            }
        }
        return flush_cards;
    }

    inline bool is_straight(const array<Card,7>& cards, const card_range& range) {
        // Assumes the cards are ordered in decreasing order
        for(int8_t i = range.first+1; i <= range.second; i++) {
            if(cards[i].value != (cards[i-1].value - 1)){
                return false;
            }
        }
        return true;
    }

    vector<card_vec> find_all_straights(const array<Card,7>& cards) {
        // Returns a vector of vectors, either empty or with all straights found
        // Assumes the cards are ordered in decreasing order
        vector<card_vec> all_straight_cards;
        all_straight_cards.reserve(3); // max 3 straights
        // If cards are already ordered one of first, second or third card must be part of a straight (if there's one)
        // Start from high card, so straights are ordered based on high card
        for(uint8_t start = 0; start < 3; start++){
            card_range range = {start, start + 4};
            if(is_straight(cards, range)) {
                all_straight_cards.push_back(expand_range(range));
            }
        }
        // Consider ACE = 1
        uint8_t num_aces = count_aces(cards);
        if(num_aces > 0){
            // In order to convert ACE to 1 take the modulus 12 and reorder the cards
            array<Card,7> cards_module = cards;
            for(uint8_t i = 0; i<num_aces; i++){
                cards_module[i].value = 1;
            }
            sort_cards<array<Card,7>>(cards_module);
            for(uint8_t start = 0; start < 3; start++){
                card_range range = {start, start + 4};
                if(is_straight(cards_module, range)) {
                    // Convert range to original cards
                    card_vec vec = expand_range(range);
                    for(auto& v: vec) v = (v + num_aces)%7;
                    sort_vec(vec);
                    all_straight_cards.push_back(vec);
                }
            }
        }
        return all_straight_cards;
    }

    card_range find_repetition(const array<Card,7>& cards, card_range range, uint8_t N) {
        // Returns a vector, either {null, null} or with the FIRST (i.e. with the highest cards) repetition of N cards found
        // Assumes the cards are ordered in decreasing order
        for(int8_t s = range.first; s <= (range.second - N + 1); s++){
            int8_t e = (s + N - 1);
            if(cards[s].value == cards[e].value){
                return {s, e};
            }
        }
        return NULL_RANGE;
    }

    vector<card_range> find_all_repetitions(const array<Card,7>& cards, uint8_t N) {
        // Returns a vector, either empty or with the ALL repetition of N cards found
        // Assumes the cards are ordered in decreasing order
        vector<card_range> all_reps;
        int8_t start = 0;
        while((cards.size() - start) > 1) {
            card_range rep = {start, cards.size() - 1};
            rep = find_repetition(cards, rep, N);
            if(rep != NULL_RANGE){
                all_reps.push_back(rep);
                start = rep.second + 1;
            } else {
                ++start;
            }
        }
        return all_reps;
    }

    Hand get_best_hand(const array<Card,7>& cards){
        // Assumes the cards are ordered in decreasing order
        card_vec flush_vec = find_flush(cards);
        vector<card_vec> all_straights = find_all_straights(cards);
        bool has_flush = !flush_vec.empty();
        bool has_straight = !all_straights.empty();
        // Look for royal/straight flush
        if(has_flush && has_straight) {
            // Look among straights which one is also a flush
            for(card_vec& straight_vec: all_straights){
                if(flush_vec == straight_vec) {
                    Hand best_hand;
                    best_hand.hand_type = (cards[flush_vec[0]].value == 13)? RoyalFlush : StraightFlush;
                    copy_vec(cards, best_hand.Cards, flush_vec);
                    return best_hand;
                }
            }
        }
        // Look for poker
        card_range poker = find_repetition(cards, card_range({0, cards.size() - 1}), 4);
        if((poker.second + 1 - poker.first) == 4){
            Hand best_hand;
            best_hand.hand_type = Poker;
            card_vec poker_vec = expand_range(poker);
            poker_vec = pad_card_vec(poker_vec, cards, 5);
            copy_vec(cards, best_hand.Cards, poker_vec);
            return best_hand;
        }
        // Look for full house
        card_range triple = find_repetition(cards, card_range({0, cards.size() - 1}), 3);
        if (triple != NULL_RANGE) {
            card_range pair_1 = find_repetition(cards, card_range({0, triple.first - 1}), 2); // Pairs can happen before or after the triple
            card_range pair_2 = find_repetition(cards, card_range({triple.second + 1, cards.size() - 1}), 2);
            card_range pair = (pair_1 != NULL_RANGE ? pair_1 : pair_2);
            if(pair != NULL_RANGE){
                Hand best_hand;
                best_hand.hand_type = FullHouse;
                card_vec full_vec = expand_range(triple);
                card_vec pair_vec = expand_range(pair);
                full_vec.reserve(5);
                full_vec.insert(full_vec.end(), pair_vec.begin(), pair_vec.end());
                sort_vec(full_vec);
                copy_vec(cards, best_hand.Cards, full_vec);
                return best_hand;
            }
        }
        // Look for flush
        if(has_flush){
            Hand best_hand;
            best_hand.hand_type = Flush;
            copy_vec(cards, best_hand.Cards, flush_vec);
            return best_hand;
        }
        // Look for straight
        if(has_straight){
            Hand best_hand;
            best_hand.hand_type = Straight;
            // Straight are already ordered, best is first
            copy_vec(cards, best_hand.Cards, all_straights[0]);
            return best_hand;
        }
        // Look for triples
        // use triple from Full House
        if(triple != NULL_RANGE){
            Hand best_hand;
            best_hand.hand_type = Triples;
            card_vec triple_vec = expand_range(triple);
            triple_vec = pad_card_vec(triple_vec, cards, 5);
            copy_vec(cards, best_hand.Cards, triple_vec);
            return best_hand;
        }
        // Look for pairs or double pairs
        vector<card_range> all_pairs = find_all_repetitions(cards, 2);
        if(all_pairs.size() >= 2) {
            Hand best_hand;
            best_hand.hand_type = DoublePairs;
            card_vec dp_vec = expand_range(all_pairs[0]);
            dp_vec.reserve(5);
            card_vec temp = expand_range(all_pairs[1]);
            dp_vec.insert(dp_vec.end(), temp.begin(), temp.end());
            dp_vec = pad_card_vec(dp_vec, cards, 5);
            copy_vec(cards, best_hand.Cards, dp_vec);
            return best_hand;
        } else if (all_pairs.size() == 1) {
            Hand best_hand;
            best_hand.hand_type = Pairs;
            card_vec pair_vec = expand_range(all_pairs[0]);
            pair_vec = pad_card_vec(pair_vec, cards, 5);
            copy_vec(cards, best_hand.Cards, pair_vec);
            return best_hand;
        }
        // High card
        Hand best_hand;
        best_hand.hand_type = HighCard;
        copy(cards.begin(), cards.begin() + 5, best_hand.Cards.begin());
        return best_hand;
    }

    Hand get_best_hand_not_sorted(array<Card,7> cards){
        sort_cards<array<Card,7>>(cards);
        return get_best_hand(cards);
    }

    void profiling(){
        for(auto& cards: test_cards){
            for (int i = 0; i < profiling_iterations; ++i) {
                get_best_hand_not_sorted(cards);
            }
        }
    }
}

#endif