#ifndef _POKER_ALGORITHMS_NEW_H
#define _POKER_ALGORITHMS_NEW_H

#include "global.h"
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <algorithm>

using namespace std;

namespace poker_algo_new {

    vector<Card> find_flush(array<Card,7> cards) {
        // Returns a vector, either empty or with the 5 cards making a flush
        // Assumes the cards are ordered in decreasing order
        vector<Card> flush_cards;
        flush_cards.reserve(5);
        for (uint8_t i = 0; i<4; i++){
            short num_same_suit = 0;
            for (Card card: cards){
                if(card.suit == i){
                    ++num_same_suit;
                    flush_cards.push_back(card);
                }
            }
            if(num_same_suit>=5){
                return flush_cards;
            } else {
                flush_cards.clear();
            }
        }
    }

    vector<vector<Card>> find_all_straights(array<Card,7> cards) {
        // Returns a vector of vectors, either empty or with all straights found
        // Assumes the cards are ordered in decreasing order
        vector<vector<Card>> all_straight_cards;
        vector<Card> current_straight_cards;
        current_straight_cards.reserve(5);
        // If cards are already ordered one of first, second or third card must be part of a straight (if there's one)
        // Start from high card, so straights are ordered based on high card
        for(uint8_t i = 0; i<3; i++){
            current_straight_cards.push_back(cards[i]);
            short straight_size = 1;
            for (uint8_t j = i+1; j<cards.size(); j++){
                if((straight_size<5) && (cards[j].value == (cards[j-1].value + 1))){
                    ++straight_size;
                    current_straight_cards.push_back(cards[j]);
                } else {
                    break;
                }
            }
            if(straight_size==5){
                all_straight_cards.push_back(current_straight_cards);
            } else {
                current_straight_cards.clear();
            }
        }
        return all_straight_cards;
    }

    pair<Card*, Card*> find_repetition(array<Card,7> cards, short N) {
        // Returns a vector, either empty or with the FIRST (i.e. with the highest cards) repetition of N cards found
        // Assumes the cards are ordered in decreasing order
        pair<Card*, Card*> rep = {cards.begin(), cards.begin()};
        for(auto start = cards.begin(); start != (cards.end() - N); start++){
            auto end = (start + N);
            if(start->value == end->value){
                rep = {start, end};
                return rep;
            }
        }
        return rep;
    }

    void pad_card_range(array<Card,7> cards, short N, pair<Card*, Card*>& range) {
        // Hands must have 5 cards
        // Expand (start, end) range by including cards in value order
        // Assumes the cards are ordered in decreasing order
        uint8_t range_size = poker.second - poker.first;
        while(range_size < N){
            if(poker.first != cards.begin()){
                --poker.first;
            } else {
                ++poker.second;
            }
            ++range_size;
        }
    }

    vector<pair<Card*, Card*>> find_all_repetitions(array<Card,7> cards, short N) {
        // Returns a vector, either empty or with the ALL repetition of N cards found
        // Assumes the cards are ordered in decreasing order
        vector<pair<Card*, Card*>> all_reps;
        auto start = cards.begin(); 
        auto end = start;
        while(start != cards.end()) {
            for(auto rep_start = start; rep_start != (cards.end() - N); rep_start++){
                auto rep_end = (rep_start + N);
                if(rep_start->value == rep_end->value){
                    start = rep_start;
                    end = rep_end;
                    all_reps.push_back({start, end});
                    start = end;
                    continue;
                } else {
                    ++start;
                }
            }
        }
        return all_reps;
    }

    Hand get_best_hand(array<Card,7> cards){
        // WARNING This function assumes the cards are sorted beforehand
        Hand best_hand;
        auto flush = find_flush(cards);
        auto all_straights = find_all_straights(cards);
        bool has_flush = !flush.empty();
        bool has_straight = !all_straights.empty();
        // Look for royal/straight flush
        if(has_flush) {
            // Look among straights which one is also a flush
            for(auto straight: all_straights){
                if(straight == flush) {
                    best_hand.hand_type = (flush[0].value == 13)? RoyalFlush : StraightFlush;
                    copy(flush.begin(), flush.end(), best_hand.Cards.begin());
                    return best_hand;
                }
            }
        }
        // Look for poker
        auto poker = find_repetition(cards, 4);
        if((poker.second - poker.first) == 4){
            best_hand.hand_type = Poker;
            pad_card_range(cards, 5, poker);
            std::copy(poker.begin(), poker.end(), best_hand.Cards.begin());
            return best_hand;
        }
        // Look for full house
        auto full_end_1 = cards.end() - 1; // first pair/triple
        auto full_start_1 = full_end_1;    
        for(auto end = full_end_1; end != cards.begin(); end--){
            for(auto start = end-1; (end - start) < 3; start--){
                if(start->value == end->value){
                    full_start_1 = start;
                    full_end_1 = end;
                } else {
                    break;
                }
            }
            if (full_start_1 != full_end_1) break;
        }
        auto full_end_2 = full_start_1 - 1; // second pair/triple
        auto full_start_2 = full_end_2;
        for(auto end = full_end_2; end != cards.begin(); end--){
            for(auto start = end-1; (end - start) < 3; start--){
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
            return best_hand;
        } else if((len_1 + len_2) == 6){ // It may happen that there are 2 triples, but it's still a full house -> get the pair from the lowest triple
            best_hand.hand_type = FullHouse;
            std::copy(full_start_1, full_end_1+1, best_hand.Cards.begin());
            std::copy(full_start_2+1, full_end_2+1, best_hand.Cards.begin() + len_1);
            return best_hand;
        }
        // Look for flush
        if(has_flush){
            best_hand.hand_type = Flush;
            std::copy(flush.begin(), flush.end(), best_hand.Cards.begin());
            return best_hand;
        }
        // Look for best straight
        if(has_straight){
            best_hand.hand_type = Straight;
            // Straight are already ordered, best is first
            std::copy(all_straights[0].begin(), all_straights[0].end(), best_hand.Cards.begin());
            return best_hand;
        }
        // Look for triples
        pair<Card *, Card *> triples = find_repetition(cards, 3);
        if((triples.second - triples.second) == 3){
            best_hand.hand_type = Triples;
            pad_card_range(cards, 5, triples);
            std::copy(triples.begin(), triples.end(), best_hand.Cards.begin());
            return best_hand;
        }
        // Look for pairs or double pairs
        vector<pair<Card *, Card *>> all_pairs = find_all_repetitions(cards, 2);
        if(all_pairs.size() >= 2) {
            best_hand.hand_type = DoublePairs;
            std::copy(all_pairs[0].first, all_pairs[0].second, best_hand.Cards.begin());
            std::copy(all_pairs[1].first, all_pairs[1].second, best_hand.Cards.begin() + 2);
            if (all_pairs[0].first->value != cards.begin()->value) {
                best_hand.Cards[4] = cards[0];
            } else if (all_pairs[0].second != all_pairs[1].first){
                best_hand.Cards[4] = *(all_pairs[0].second + 1);
            } else {
                best_hand.Cards[4] = *(all_pairs[1].second + 1);
            }
            return best_hand;
        } else if (all_pairs.size() == 1) {
            best_hand.hand_type = Pairs;
            pad_card_range(cards, 5, all_pairs[0]);
            std::copy(all_pairs[0].first, all_pairs[0].second, best_hand.Cards.begin());
            return best_hand;
        }
        // High card
        best_hand.hand_type = HighCard;
        std::copy(cards.begin(), cards.begin() + 5, best_hand.Cards.begin());
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