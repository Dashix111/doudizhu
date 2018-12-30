#ifndef PLAYER_H
#define PLAYER_H
/*  Player.h
 *  Player Interface
 */

#include "Card.h"
#include <string>
#include <vector>

enum Position {
    landlord = 0, earlyHand, lateHand
};

class Player {
private:
    std::vector<Card> hand;
    std::string name;
    Position pos;

public:
    Player();
    Player(std::string nameIn, Position posIn);
    
    //returns player's name
    const std::string & getName() const;
    
    const std::vector<Card> & getHand() const;
    
    std::vector<Card> & getHand();

    const Position getPosition() const;

    //adds Card c to Player's hand
    virtual void addCard(const Card &c);
    
    //remove and return hand[index]
    Card popCard(int index);
    
    //sort hand in descending order
    void sortHand();
    
    //bidding for landlord wiht value 0, 1, 2, 3
    //the highest bidder will be the landlord
    virtual int bid(int currentBid) = 0;

    //"Lead" means to play the first set Cards in a trick.
    //Cards are removed from the player's hand.
    virtual CardCombo leadCard() = 0;

    //Plays a set of Cards from Player's hand according to their strategy.
    //Cards are removed from the player's hand.
    virtual CardCombo playCard(const CardCombo &c) = 0;

    //destructor
    virtual ~Player() {}
};

//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
Player * PlayerFactory(const std::string &name, const std::string &strategy);

//Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p);

#endif
