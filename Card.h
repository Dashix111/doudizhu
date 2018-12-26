#ifndef CARD_H
#define CARD_H
/* Card.h
 */

#include <iostream>
#include <string>
#include <vector>

enum Rank {
    three=3, four, five, six, seven, eight, nine, ten, jack, queen, king, ace, two,
    bJoker, rJoker
};

enum Suit {
    spade, heart, club, diamond, joker
};

class Card {
private:
    Rank rank;
    Suit suit;
    
public:
    const Rank getRank() const {return rank;}
    const Suit getSuit() const {return suit;}
    Card();
    Card(Rank rankIn, Suit suitIn);
};

bool operator<(const Card &lhs, const Card &rhs);
bool operator>(const Card &lhs, const Card &rhs);
bool operator==(const Card &lhs, const Card &rhs);
bool operator!=(const Card &lhs, const Card &rhs);
std::ostream & operator<<(std::ostream &os, const Card &card);

enum CardComboType {
    error, zero, single, pair, trio, straight, pairStraight, trioStraight,
    trioSingle, trioPair, airplaneSingle, airplanePair, fourSingles,
    fourPairs, bomb, rocket
};


class CardCombo {
private:
    //sorted highest to lowest
    std::vector<Card> cards;
    Card compareCard;
    int numCards;
    int value;
    CardComboType type;
    int calculateValue();
public:
    CardCombo();
    CardCombo(const std::vector<Card> &cardsIn, Card &compareCardIn,
              int numCardsIn, int valueIn, CardComboType typeIn);
    CardCombo(const std::vector<Card> &cardsIn);
    int getValue() const {return value;}
    int getNumCards() const {return numCards;}
    CardComboType getType() const {return type;}
    Card getCompareCard() const {return compareCard;}
    std::vector<Card> getCards() const {return cards;}
    
};


bool isSameType(const CardCombo &a, const CardCombo &b);

//Require same type or bombs/rockets
bool operator<(const CardCombo &lhs, const CardCombo &rhs);
bool operator>(const CardCombo &lhs, const CardCombo &rhs);
std::ostream & operator<<(std::ostream &os, const CardCombo &combo);
bool isStraight(const std::vector<Card> &cards);
bool isPairStraight(const std::vector<Card> &cards);
bool isTrioStraight(const std::vector<Card> &cards);
//Return the index of the compare card or -1
int isAirPlaneSingle(const std::vector<Card> &cards);
int isAirPlanePair(const std::vector<Card> &cards);


#endif
