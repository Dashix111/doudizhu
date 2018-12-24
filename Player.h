#ifndef PLAYER_H
#define PLAYER_H
/*  Player.h
 *  Player Interface
 */

#include "Card.h"
#include <string>
#include <vector>

class Player {
private:
    bool isLandlord;
    std::vector<Card> hand;
public:
    //returns player's name
    virtual const std::string & getName() const = 0;

    //adds Card c to Player's hand
    virtual void addCard(const Card &c) = 0;

    //Leads one Card from Player's hand according to their strategy
    //"Lead" means to play the first Card in a trick.
    //The card  is removed the player's hand.
    virtual std::vector<Card> leadCard() = 0;

    //Plays one Card from Player's hand according to their strategy.
    //The card is removed from the player's hand.
    virtual std::vector<Card> playCard(const std::vector<Card> &leadCards) = 0;

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
