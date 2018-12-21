#ifndef PACK_H
#define PACK_H
/* Pack.h
 *
 * Represents a pack of playing cards
 *
 * by Andrew DeOrio <awdeorio@umich.edu>
 * 2014-12-21
 */


#include "Card.h"
#include <array>
#include <string>

class Pack {
public:
    Pack();
    
    //initialize by input
    Pack(std::istream& pack_input);

    // REQUIRES: cards remain in the Pack
    // EFFECTS: Returns the next card in the pack and increments the next index
    Card deal_one();

    // EFFECTS: Resets next index to first card in the Pack
    void reset();

    // EFFECTS: Shuffles the Pack and resets the next index. This
    //          performs an in shuffle seven times. See
    //          https://en.wikipedia.org/wiki/In_shuffle.
    void shuffle();

    // EFFECTS: returns true if there are no more cards left in the pack
    bool empty() const;

private:
    static const int PACK_SIZE = 54;
    std::array<Card, PACK_SIZE> cards;
    int next; //index of next card to be dealt
};

#endif
