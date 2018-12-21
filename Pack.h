#ifndef PACK_H
#define PACK_H
/* Pack.h
 */
#include "Card.h"
#include <vector>
#include <string>
#include <iostream>

class Pack {
public:
    Pack();
    
    //initialize by input
    Pack(std::istream& packInput);

    //Returns the next card in the pack and increments the next index
    Card dealOne();

    //Resets next index to first card in the Pack
    void reset();
    
    //shuffle the deck, determine the landLordCards(last three cards after
    //  shuffling)
    void shuffle();
    
    //select card that faces up
    int pickUpcard();

    //returns true if there are no more cards left in the pack
    bool empty() const;

private:
    static const int PACK_SIZE = 54;
    std::vector<Card> cards;
    std::vector<Card> landLordCards;
    int next; //index of next card to be dealt
    int upCard;
};

#endif
