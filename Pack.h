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
    
    //initialize by input, the first line of input should be
    //  the index of the upCard, then each line should contain
    //  the rank and suit of a Card in the format "RANK of SUIT"
    //  e.g. three of spade
    //each pack should contain PACK_SIZE = 54 cards
    Pack(std::istream& packInput);

    //Returns the next card in the pack and increments the next index
    Card dealOne();

    //Resets next index to first card in the Pack
    void reset();
    
    //shuffle the deck, determine the landLordCards(last three cards after
    //  shuffling)
    void shuffle();
    
    //select card that faces up
    void pickUpcard();

    //returns true if there are no more cards left in the pack
    bool empty() const;
    
    //for testing purposes
    void printPack() const;
    
    //for testing purposes
    int getNext() const;
    
    //for testing purposes
    int getUpcard() const;
    
    static const int PACK_SIZE = 54;

private:
    std::vector<Card> cards;
    std::vector<Card> landLordCards;
    int next; //index of next card to be dealt
    int upCard;
};

#endif
