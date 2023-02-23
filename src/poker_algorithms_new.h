#ifndef _POKER_ALGORITHMS_NEW_H
#define _POKER_ALGORITHMS_NEW_H

#include "global.h"
#include "utils.h"
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <algorithm>

namespace poker_algo_new {
    using card_range = std::pair<int8_t, int8_t>;
    using card_vec = std::vector<int8_t>;
    const int8_t NULL_PTR = -1;
    const card_range NULL_RANGE = {NULL_PTR, NULL_PTR};
    const uint8_t TOTAL_CARDS = 52;

    card_vec expand_range(card_range range) {
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

    void copy_vec(std::array<Card,7>& cards, std::array<Card, 5>& array, card_vec& vec) {
        for (int8_t i = 0; i < 5; i++) array[i] = cards[vec[i]];
    }

    void sort_vec(card_vec& vec){
        std::sort(vec.begin(), vec.end(), [](int8_t& a, int8_t& b){return a<=b;});
    }

    card_vec pad_card_vec(card_vec vec, std::array<Card,7>& cards, uint8_t N) {
        // Expand a vector of cards by including cards in value order
        // Assumes the cards are ordered in decreasing order
        vec.reserve(N);
        for(int8_t c = 0; (c < cards.size()) && (vec.size() < N); c++) {
            if(std::find(vec.begin(), vec.end(), c) == vec.end()) {
                vec.push_back(c);
            }
        }
        sort_vec(vec);
        return vec;
    }

    uint8_t count_aces(std::array<Card, 7>& array){
        uint8_t count = 0;
        for(Card card:array){
            if(card.value == 13) ++count;
        }
        return count;
    }

    card_vec find_flush(std::array<Card,7>& cards) {
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

    bool is_straight(std::array<Card,7>& cards, card_range range) {
        // Assumes the cards are ordered in decreasing order
        for(int8_t i = range.first+1; i <= range.second; i++) {
            if(cards[i].value != (cards[i-1].value - 1)){
                return false;
            }
        }
        return true;
    }

    std::vector<card_vec> find_all_straights(std::array<Card,7>& cards) {
        // Returns a vector of vectors, either empty or with all straights found
        // Assumes the cards are ordered in decreasing order
        std::vector<card_vec> all_straight_cards;
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
            std::array<Card,7> cards_module = cards;
            for(uint8_t i = 0; i<num_aces; i++){
                cards_module[i].value = 1;
            }
            sort_cards<std::array<Card,7>>(cards_module);
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

    card_range find_repetition(std::array<Card,7>& cards, card_range range, uint8_t N) {
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

    std::vector<card_range> find_all_repetitions(std::array<Card,7>& cards, uint8_t N) {
        // Returns a vector, either empty or with the ALL repetition of N cards found
        // Assumes the cards are ordered in decreasing order
        std::vector<card_range> all_reps;
        int8_t start = 0;
        while((cards.size() - start) > 1) {
            card_range rep = find_repetition(cards, card_range({start, cards.size() - 1}), N);
            if(rep != NULL_RANGE){
                all_reps.push_back(rep);
                start = rep.second + 1;
            } else {
                ++start;
            }
        }
        return all_reps;
    }

    Hand get_best_hand(std::array<Card,7>& cards){
        // Assumes the cards are ordered in decreasing order
        Hand best_hand;
        card_vec flush_vec = find_flush(cards);
        std::vector<card_vec> all_straights = find_all_straights(cards);
        bool has_flush = !flush_vec.empty();
        bool has_straight = !all_straights.empty();
        // Look for royal/straight flush
        if(has_flush && has_straight) {
            // Look among straights which one is also a flush
            for(card_vec& straight_vec: all_straights){
                if(flush_vec == straight_vec) {
                    best_hand.hand_type = (cards[flush_vec[0]].value == 13)? RoyalFlush : StraightFlush;
                    copy_vec(cards, best_hand.Cards, flush_vec);
                    return best_hand;
                }
            }
        }
        // Look for poker
        card_range poker = find_repetition(cards, card_range({0, cards.size() - 1}), 4);
        if((poker.second + 1 - poker.first) == 4){
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
            best_hand.hand_type = Flush;
            copy_vec(cards, best_hand.Cards, flush_vec);
            return best_hand;
        }
        // Look for straight
        if(has_straight){
            best_hand.hand_type = Straight;
            // Straight are already ordered, best is first
            copy_vec(cards, best_hand.Cards, all_straights[0]);
            return best_hand;
        }
        // Look for triples
        // use triple from Full House
        if(triple != NULL_RANGE){
            best_hand.hand_type = Triples;
            card_vec triple_vec = expand_range(triple);
            triple_vec = pad_card_vec(triple_vec, cards, 5);
            copy_vec(cards, best_hand.Cards, triple_vec);
            return best_hand;
        }
        // Look for pairs or double pairs
        std::vector<card_range> all_pairs = find_all_repetitions(cards, 2);
        if(all_pairs.size() >= 2) {
            best_hand.hand_type = DoublePairs;
            card_vec dp_vec = expand_range(all_pairs[0]);
            dp_vec.reserve(5);
            card_vec temp = expand_range(all_pairs[1]);
            dp_vec.insert(dp_vec.end(), temp.begin(), temp.end());
            dp_vec = pad_card_vec(dp_vec, cards, 5);
            copy_vec(cards, best_hand.Cards, dp_vec);
            return best_hand;
        } else if (all_pairs.size() == 1) {
            best_hand.hand_type = Pairs;
            card_vec pair_vec = expand_range(all_pairs[0]);
            pair_vec = pad_card_vec(pair_vec, cards, 5);
            copy_vec(cards, best_hand.Cards, pair_vec);
            return best_hand;
        }
        // High card
        best_hand.hand_type = HighCard;
        std::copy(cards.begin(), cards.begin() + 5, best_hand.Cards.begin());
        return best_hand;
    }

    Hand get_best_hand_not_sorted(std::array<Card,7> cards){
        sort_cards<std::array<Card,7>>(cards);
        return get_best_hand(cards);
    }

    bool has_card(const Card& card, const std::vector<Card>& cards) {
        for (auto& temp : cards) {
            if (card == temp) {
                return true;
            }
        }
        return false;
    }

    void next_combination(std::vector<uint8_t>& indexes, const uint8_t& num_remaining_cards) {
        // Create a new combination of indexes
        // Iterate backwards through the indexes
        // TODO expand this to accept also less than 2 cards per user
        for (uint8_t i = indexes.size() - 1; i >= 0; --i) {
            // Check if index can be aumented 
            if (indexes[i] < (num_remaining_cards - indexes.size() + i)) {
                ++indexes[i];
                // Go through the following indexes to reduce them to the minimum possible value
                for (uint8_t j = i+1; j < indexes.size(); ++j) {
                    indexes[j] = indexes[j-1] + 1;
                }
                break;
            }
        }
    }

    std::vector<std::map<string,int>> calculate_hand_frequency(std::vector<std::vector<Card>> hand_cards, std::vector<Card> table_cards) {
        // Create array with all dealt cards and some helper variables
        std::vector<Card> all_dealt_cards = table_cards;
        for (auto player : hand_cards) all_dealt_cards.insert(all_dealt_cards.end(), player.begin(), player.end());
        const uint8_t num_players = hand_cards.size();
        const uint8_t num_turns = hand_cards[0].size() + table_cards.size();
        const uint8_t num_missing_turns = (7-num_turns);
        const uint8_t num_table_cards = table_cards.size();
        // Create the map with the hand_types and the number of hands of that type
        const string possible_hand_types[10] = {"Royal Flush","Straight Flush","Poker","Full House","Flush","Straight","Triples","Double Pairs","Pairs","High Card"};
        std::vector<std::map<string,int>> players_hand_possibilities;
        players_hand_possibilities.reserve(num_players);
        for (uint8_t p = 0; p < num_players; p++) {
            std::map<string,int> hand_possibilities;
            for (auto pht : possible_hand_types) hand_possibilities[pht] = 0;
            hand_possibilities["Win"] = 0;
            hand_possibilities["Draw"] = 0;
            players_hand_possibilities.push_back(hand_possibilities);
        }
        // Create all possible cards
        std::vector<Card> remaining_cards;
        remaining_cards.reserve(TOTAL_CARDS - all_dealt_cards.size());
        for (uint8_t v = 13; v > 0; v--) {
            for (uint8_t s = 4; s > 0; s--) {
                Card new_card = {v, s};
                if(!has_card(new_card, all_dealt_cards)) remaining_cards.push_back(new_card);
            }
        }
        const uint8_t num_remaining_cards = remaining_cards.size();
        // Create the new hand array for passing it to the get_best_hand Function
        std::vector<uint8_t> indexes(num_missing_turns);
        for(uint8_t i = 0; i < num_missing_turns; ++i) indexes[i] = i;
        int num_possible_cases = 0;
        int player_hand_euristic = 0;
        std::array<int, 10> drawed_players_indx = {0,0,0,0,0,0,0,0,0,0};
        while (true) {
            int max_hand_heuristic = 0;
            int drawed_players = 0;
            // Extract missing cards to build possible hand
            std::array<Card,7> new_hand;
            for (uint8_t i = 0; i < indexes.size(); i++) new_hand[i] = remaining_cards[indexes[i]];
            for (uint8_t p = 0; p < num_players; p++) {
                // Insert player cards
                std::copy(hand_cards[p].begin(), hand_cards[p].end(), new_hand.begin() + indexes.size());
                // Compute best hand
                Hand result = get_best_hand_not_sorted(new_hand);
                players_hand_possibilities[p][hand_names[result.hand_type - 1]]++;
                // Check if win or draw
                player_hand_euristic = result.hand_heuristic();
                if (player_hand_euristic > max_hand_heuristic) {
                    max_hand_heuristic = player_hand_euristic;
                    drawed_players = 1;
                    drawed_players_indx[0] = p;
                } else if (player_hand_euristic == max_hand_heuristic) {
                    drawed_players_indx[drawed_players] = p;
                    drawed_players++;
                }
            }
            // Calculate who won
            if (drawed_players == 1) {
                players_hand_possibilities[drawed_players_indx[0]]["Win"]++;
            } else {
                for (int i = 0; i < drawed_players; i++) players_hand_possibilities[drawed_players_indx[i]]["Draw"]++;
            }
            // Check wheter to continue the loop and computes next combination of indexes
            ++num_possible_cases;
            if (indexes[0] == num_remaining_cards-num_missing_turns) {
                break;
            }
            next_combination(indexes, num_remaining_cards);
        }
        for (int p = 0; p < num_players; p++) players_hand_possibilities[p]["Total Cases"] = num_possible_cases;
        return players_hand_possibilities;
    }
}

#endif