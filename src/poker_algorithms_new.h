#ifndef _POKER_ALGORITHMS_NEW_H
#define _POKER_ALGORITHMS_NEW_H

#include "global.h"
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <algorithm>

namespace poker_algo_new {
    // TODO: I still lack a good way of expanding ranges it with the remaining cards
    using card_range = pair<Card*, Card*>;
    using card_vec = vector<Card*>;

    card_vec expand_range(Card*& start, Card*& end) {
        // Converts two pointers with a range into vector of pointers
        card_vec card_vec;
        card_vec.reserve(end-start+1);
        for(auto i = start; i != end + 1; i++){
            card_vec.push_back(i);
        }
        return card_vec;
    }

    card_vec expand_range(card_range& range) {
        // Converts two pointers with a range into vector of pointers
        return expand_range(range.first, range.second);
    }

    void copy_vec(array<Card, 5>& array, card_vec& vec) {
        for (uint8_t i = 0; i < 5; i++) array[i] = *vec[i];
    }

    card_vec find_flush(array<Card,7>& cards) {
        // Returns a vector, either empty or with the 5 cards making a flush
        // Assumes the cards are ordered in decreasing order
        card_vec flush_cards;
        flush_cards.reserve(5);
        for (uint8_t i = 1; i < 5; i++){
            short num_same_suit = 0;
            for (Card& card: cards){
                if((num_same_suit < 5) && (card.suit == i)){
                    ++num_same_suit;
                    flush_cards.push_back(&card);
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

    vector<card_vec> find_all_straights(array<Card,7>& cards) {
        // Returns a vector of vectors, either empty or with all straights found
        // Assumes the cards are ordered in decreasing order
        vector<card_vec> all_straight_cards;
        all_straight_cards.reserve(3); // max 3 straights
        uint8_t straigh_num = 1;
        // If cards are already ordered one of first, second or third card must be part of a straight (if there's one)
        // Start from high card, so straights are ordered based on high card
        for(uint8_t start = 0; start < 3; start++){
            card_vec curr_straight = {&cards[start]};
            straigh_num = 1;
            uint8_t end = start+1;
            for(end; end < cards.size(); end++){
                if((cards[start].value == (cards[end].value + straigh_num)) && (cards[end].value != cards[end - 1].value)){
                    ++straigh_num;
                    curr_straight.push_back(&cards[end]);
                    if(straigh_num == 5){
                        all_straight_cards.push_back(curr_straight);
                    }
                } else if (cards[end].value == cards[end - 1].value) {
                    continue;
                } else {
                    break;
                }
            }
        }
        return all_straight_cards;
    }

    
    void pad_card_vec(card_vec& vec, array<Card,7>& cards, short N) {
        // Expand a vector of cards by including cards in value order
        // Assumes the cards are ordered in decreasing order
        vec.reserve(N);
        bool is_in = false;
        for(auto c = cards.begin(); (c != cards.end()) && (vec.size() < N); c++) {
            is_in = false;
            for(auto v : vec){
                if(*c == *v){
                    is_in = true;
                    break;
                }
                
            }
            if(!is_in) {
                vec.push_back(c);
            }
        }
    }

    card_range find_repetition(array<Card,7>& cards, short N) {
        // Returns a vector, either empty or with the FIRST (i.e. with the highest cards) repetition of N cards found
        // Assumes the cards are ordered in decreasing order
        card_range rep;
        for(auto start = cards.begin(); start < (cards.end() - N + 1); start++){
            auto end = (start + N - 1);
            if(start->value == end->value){
                rep = {start, end};
                return rep;
            }
        }
        return rep;
    }

    vector<card_range> find_all_repetitions(array<Card,7>& cards, short N) {
        // Returns a vector, either empty or with the ALL repetition of N cards found
        // Assumes the cards are ordered in decreasing order
        vector<card_range> all_reps;
        auto start = cards.begin();
        auto end = start;
        while((cards.end() - start) > 1) {
            for(auto rep_start = start; rep_start < (cards.end() - N + 1); rep_start++){
                auto rep_end = (rep_start + N - 1);
                if(rep_start->value == rep_end->value){
                    start = rep_start;
                    end = rep_end;
                    all_reps.push_back({start, end});
                    start = end;
                    continue;
                }
            }
            ++start;
        }
        return all_reps;
    }

    Hand get_best_hand(array<Card,7>& cards){
        // WARNING This function assumes the cards are sorted beforehand
        Hand best_hand;
        auto flush_vec = find_flush(cards);
        auto all_straights = find_all_straights(cards);
        bool has_flush = !flush_vec.empty();
        bool has_straight = !all_straights.empty();
        // Look for royal/straight flush
        if(has_flush) {
            // Look among straights which one is also a flush
            for(auto straight_vec: all_straights){
                uint8_t same_cards = 0;
                // auto straight_vec = expand_range(straight);
                for(uint8_t i = 0; i<5; i++){
                    if(*straight_vec[i] == *flush_vec[i]) ++same_cards;
                }
                if(same_cards == 5) {
                    best_hand.hand_type = (flush_vec[0]->value == 13)? RoyalFlush : StraightFlush;
                    copy_vec(best_hand.Cards, flush_vec);
                    sort_cards(best_hand.Cards);
                    return best_hand;
                }
            }
        }
        // Look for poker
        auto poker = find_repetition(cards, 4);
        if((poker.second + 1 - poker.first) == 4){
            best_hand.hand_type = Poker;
            // pad_card_range(cards, 5, poker);
            auto poker_vec = expand_range(poker);
            pad_card_vec(poker_vec, cards, 5);
            copy_vec(best_hand.Cards, poker_vec);
            sort_cards(best_hand.Cards);
            return best_hand;
        }
        // Look for full house
        auto full_start_1 = cards.begin();  
        auto full_end_1 = full_start_1; // first pair/triple
        for(auto start = full_start_1; start != cards.end(); start++){
            for(auto end = start+1; (end - start) < 3; end++){
                if(start->value == end->value){
                    full_start_1 = start;
                    full_end_1 = end;
                } else {
                    break;
                }
            }
            if (full_start_1 != full_end_1) break;
        }
        auto full_start_2 = full_end_1 + 1; // second pair/triple
        auto full_end_2 = full_start_2;
        for(auto start = full_start_2; start != cards.end(); start++){
            for(auto end = start+1; (end - start) < 3; end++){
                if(start->value == end->value){
                    full_start_2 = start;
                    full_end_2 = end;
                } else {
                    break;
                }
            }
            if (full_start_2 != full_end_2) break;
        }
        uint8_t len_1 = full_end_1 - full_start_1 + 1;
        uint8_t len_2 = full_end_2 - full_start_2 + 1;
        if((len_1 + len_2) == 5){
            best_hand.hand_type = FullHouse;
            std::copy(full_start_1, full_end_1+1, best_hand.Cards.begin());
            std::copy(full_start_2, full_end_2+1, best_hand.Cards.begin() + len_1);
            sort_cards(best_hand.Cards);
            return best_hand;
        } else if((len_1 + len_2) == 6){ // It may happen that there are 2 triples, but it's still a full house -> get the pair from the lowest triple
            best_hand.hand_type = FullHouse;
            std::copy(full_start_1, full_end_1+1, best_hand.Cards.begin());
            std::copy(full_start_2+1, full_end_2+1, best_hand.Cards.begin() + len_1);
            sort_cards(best_hand.Cards);
            return best_hand;
        }
        // Look for flush
        if(has_flush){
            best_hand.hand_type = Flush;
            // for (uint8_t i = 0; i < flush.size(); i++) best_hand.Cards[i] = *flush[i];
            copy_vec(best_hand.Cards, flush_vec);
            sort_cards(best_hand.Cards);
            return best_hand;
        }
        // Look for best straight
        if(has_straight){
            best_hand.hand_type = Straight;
            // Straight are already ordered, best is first
            copy_vec(best_hand.Cards, all_straights[0]);
            // std::copy(all_straights[0].first, all_straights[0].second + 1, best_hand.Cards.begin());
            sort_cards(best_hand.Cards);
            return best_hand;
        }
        // Look for triples
        auto triples = find_repetition(cards, 3);
        if((triples.second + 1 - triples.first) == 3){
            best_hand.hand_type = Triples;
            // pad_card_range(cards, 5, triples);
            auto triple_vec = expand_range(triples);
            pad_card_vec(triple_vec, cards, 5);
            copy_vec(best_hand.Cards, triple_vec);
            sort_cards(best_hand.Cards);
            return best_hand;
        }
        // Look for pairs or double pairs
        auto all_pairs = find_all_repetitions(cards, 2);
        if(all_pairs.size() >= 2) {
            best_hand.hand_type = DoublePairs;
            auto dp_vec = expand_range(all_pairs[0]);
            auto temp = expand_range(all_pairs[1]);
            dp_vec.insert(dp_vec.end(), temp.begin(), temp.end());
            pad_card_vec(dp_vec, cards, 5);
            copy_vec(best_hand.Cards, dp_vec);
            sort_cards(best_hand.Cards);
            return best_hand;
        } else if (all_pairs.size() == 1) {
            best_hand.hand_type = Pairs;
            auto pair_vec = expand_range(all_pairs[0]);
            pad_card_vec(pair_vec, cards, 5);
            copy_vec(best_hand.Cards, pair_vec);
            sort_cards(best_hand.Cards);
            return best_hand;
        }
        // High card
        best_hand.hand_type = HighCard;
        std::copy(cards.begin(), cards.begin() + 5, best_hand.Cards.begin());
        sort_cards(best_hand.Cards);
        return best_hand;
    }

    vector<map<string,int>> calculate_hand_frequency(vector<vector<Card>> cards){
        int num_given_cards = cards[0].size();
        vector<array<Card,7>> players_cards;
        // Sort the cards and plaace them in arrays of 7 cards
        for (int i = 0; i < cards.size(); i++)
        {
            array<Card,7> temp;
            sort(cards[i].begin(),cards[i].end(),[](Card &a,Card &b){return a.value > b.value;});
            copy(cards[i].begin(),cards[i].end(),temp.begin());
            players_cards.push_back(temp);
        }
        // Create the new hand array for passing it to the get_best_hand Function
        array<Card,7> new_hand;
        string possible_hand_types[10] = {"Royal Flush","Straight Flush","Poker","Full House","Flush","Straight","Triples","Double Pairs","Pairs","High Card"};
        // Create the map with the hand_types and the number of hands of that type
        vector<map<string,int>> players_hand_posibilities;
        map<string,int> hand_posibilities;
        for (int i = 0; i < 10; i++)
        {
            hand_posibilities[possible_hand_types[i]] = 0;
        }
        hand_posibilities["Win"] = 0;
        hand_posibilities["Draw"] = 0;
        for (int l = 0; l < players_cards.size(); l++)
        {
            players_hand_posibilities.push_back(hand_posibilities);

        }
        Hand result;
        // Create all possible cards
        vector<Card> possible_cards;
        for (int j = 13; j > 0; j--)
        {
            for (int i = 4; i > 0; i--)
            {
                Card new_card;
                bool alredy_in_hand = false;
                for (int l = 0; l < players_cards.size(); l++)
                {
                    for (int k = 0; k < num_given_cards; k++)
                    {
                        if (players_cards[l][k].value == j && players_cards[l][k].suit == i){
                            alredy_in_hand = true;
                            break;
                        }
                    }
                }
                if (!alredy_in_hand){
                    new_card.value = j;
                    new_card.suit = (Suit)i;
                    possible_cards.push_back(new_card);
                }
            }
            
        }
        
        array<int,5> indexes = {0,1,2,3,4};
        int n = (7-num_given_cards);
        int N = possible_cards.size();
        int num_possible_cases = 1;
        int intersected_cards = 0;
        int player_hand_euristic = 0;
        array<int,10> drawed_players_indx = {0,0,0,0,0,0,0,0,0,0};
        while (true){
            int max_hand_heuristic = 0;
            int drawed_players = 0;
            for (int l = 0; l < players_cards.size(); l++)
            {
                // Sort efficiently the hand cards for efficiency
                intersected_cards = 0;
                for (int i = 0; i < 7; i++)
                {
                    if (intersected_cards < num_given_cards){
                        if (i-intersected_cards >= n){
                            new_hand[i] = players_cards[l][intersected_cards];
                            intersected_cards++;
                            continue;
                        }else if (players_cards[l][intersected_cards].value >= possible_cards[indexes[i-intersected_cards]].value){
                            new_hand[i] = players_cards[l][intersected_cards];
                            intersected_cards++;
                            continue;
                        }
                    }
                    new_hand[i] = possible_cards[indexes[i-intersected_cards]];
                }

                result = get_best_hand(new_hand);
                players_hand_posibilities[l][hand_names[result.hand_type - 1]]++;
                // Check if win or draw
                player_hand_euristic = result.hand_heuristic();
                if (player_hand_euristic > max_hand_heuristic){
                    max_hand_heuristic = player_hand_euristic;
                    drawed_players = 1;
                    drawed_players_indx[0] = l;
                }else if (player_hand_euristic == max_hand_heuristic){
                    drawed_players_indx[drawed_players] = l;
                    drawed_players++;
                }
            }
            if (drawed_players == 1){
                players_hand_posibilities[drawed_players_indx[0]]["Win"]++;
            }else{
                for (int i = 0; i < drawed_players; i++)
                {
                    players_hand_posibilities[drawed_players_indx[i]]["Draw"]++;
                }
            }
            num_possible_cases++;
            if (indexes[0] == N-n){
                break;
            }
            // Create a new combination of indexes
            // Iterate backwards through the indexes
            for (int i = 1; i <= n ; i++) {
                // Check if index can be aumented 
                if (indexes[n-i] < N-i) {
                    indexes[n-i]++;
                    // Go through the following indexes to reduce them to the minimum possible value
                    for (int j = n-i+1; j < n; j++) {
                        indexes[j] = indexes[j-1] + 1;
                    }
                    break;
                }
            }
        }
        for (int l = 0; l < players_cards.size(); l++)
        {
            players_hand_posibilities[l]["Total Cases"] = num_possible_cases;
        }
        return players_hand_posibilities;
    }

    Hand get_best_hand_not_sorted(array<Card,7> cards){
        sort(cards.begin(),cards.end(),[](Card &a,Card &b){return a > b;});
        return get_best_hand(cards);
    }
}

#endif