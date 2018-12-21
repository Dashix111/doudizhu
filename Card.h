#ifndef CARD_H
#define CARD_H
/* Card.h
 *
 * Represents a single playing card
 *
 * by Andrew DeOrio
 * awdeorio@umich.edu
 * 2014-12-21
 */

#include <iostream>
#include <string>

enum Rank {
    three=3, four, five, six, seven, eight, nine, ten, jack, queen, king, ace,
    bJoker, rJoker
};

enum Suit {
    spade, heart, club, diamond
};

class Card {
private:
    Rank rank;
    Suit suit;
    
public:
    Rank getRank() {return rank;}
    Suit getSuit() {return suit;}
    Card();
    Card(Rank rankIn, Suit suitIn);
};

bool operator<(const Card &lhs, const Card &rhs);
bool operator>(const Card &lhs, const Card &rhs);
bool operator==(const Card &lhs, const Card &rhs);
bool operator!=(const Card &lhs, const Card &rhs);
std::ostream & operator<<(std::ostream &os, const Card &card);


#endif
