#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <string>
#include <array>

enum Suit {Hearts = 1, Diamonds, Clubs, Spades = 4};
enum HandType {
    HighCard = 1,
    Pairs,
    DoublePairs,
    Triples,
    Straight,
    Flush,
    FullHouse,
    Poker,
    StraightFlush,
    RoyalFlush = 10
};

struct Card{
    // 1 to 13 (2 to A)
    short value;
    // 0 to 3 (H to D)
    Suit suit;

    Card():
        value(0),
        suit((Suit) 0)
    {}

    Card(short value, short suit):
        value(value),
        suit((Suit) suit)
    {}

    bool operator==(const Card& rhs) const {
        return (this->value == rhs.value) && (this->suit == rhs.suit);
    }

    bool operator>(const Card& rhs) const {
        if(this->value > rhs.value){
            return true;
        } else if(this->value == rhs.value) {
            return this->suit > rhs.suit;
        }
        return false;
    }

    bool operator>=(const Card& rhs) const {
        return (*this > rhs) || (*this == rhs);
    }
};

struct Hand{
    HandType hand_type;
    std::array<Card,5> Cards;
    
    Hand():
        hand_type(HighCard),
        Cards()
    {}

    Hand(short hand_type, std::array<Card,5> cards):
        hand_type((HandType) hand_type),
        Cards(cards)
    {}
};

const std::array<std::array<Card, 7>, 10> test_cards = {{
    {Card(13, 2), Card(12, 2), Card(11, 2), Card(10, 2), Card(9, 2), Card(8, 2), Card(7, 2)},
    {Card(12, 2), Card(11, 2), Card(10, 2), Card(9, 2), Card(8, 2), Card(7, 2), Card(6, 2)},
    {Card(13, 4), Card(13, 3), Card(13, 2), Card(13, 1), Card(9, 3), Card(4, 1), Card(3, 3)},
    {Card(13, 4), Card(13, 3), Card(13, 2), Card(9, 3), Card(9, 1), Card(4, 1), Card(3, 3)},
    {Card(13, 2), Card(11, 2), Card(6, 2), Card(5, 2), Card(5, 2), Card(5, 2), Card(2, 2)},
    {Card(12, 1), Card(11, 3), Card(10, 4), Card(9, 1), Card(8, 3), Card(4, 2), Card(3, 2)},
    {Card(13, 3), Card(13, 2), Card(13, 1), Card(10, 2), Card(9, 3), Card(4, 1), Card(3, 3)},
    {Card(13, 3), Card(12, 3), Card(12, 2), Card(9, 1), Card(4, 3), Card(2, 3), Card(2, 2)},
    {Card(13, 3), Card(12, 3), Card(12, 2), Card(9, 1), Card(4, 3), Card(3, 2), Card(2, 2)},
    {Card(13, 3), Card(11, 3), Card(10, 2), Card(9, 1), Card(8, 3), Card(3, 2), Card(2, 2)}
}};
const int profiling_iterations = 2000000;

#endif