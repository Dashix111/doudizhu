#ifndef PACK_H
#define PACK_H
/* Pack.h
 */
#include "Card.h"
#include <vector>
#include <string>

class Pack {
public:
    Pack();
    
    //initialize by input
    Pack(std::istream& pack_input);

    //Returns the next card in the pack and increments the next index
    Card deal_one();

    //Resets next index to first card in the Pack
    void reset();
    
    void shuffle();

    //returns true if there are no more cards left in the pack
    bool empty() const;

private:
    static const int PACK_SIZE = 54;
    std::vector<Card> cards;
    int next; //index of next card to be dealt
};

#endif
