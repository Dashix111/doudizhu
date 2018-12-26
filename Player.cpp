//  Player.cpp
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "Player.h"
#include "Card.h"

Player::Player()
    : name("unnamed"), pos(landlord) {}
Player::Player(std::string nameIn, Position posIn)
    : name(nameIn), pos(posIn) {}

const std::string & Player::getName() const {
    return name;
}

const std::vector<Card> & Player::getHand() const {
    return hand;
}

const Position Player::getPosition() const {
    return pos;
}

void Player::addCard(const Card &c) {
    hand.push_back(c);
    std::sort(hand.rbegin(), hand.rend());
}

Card Player::popCard(int index) {
    Card c = hand[index];
    hand.erase(hand.begin() + index);
    return c;
}

void Player::sortHand() {
    std::sort(hand.rbegin(), hand.rend());
}

//Human Player
class Human : public Player {
public:
    CardCombo leadCard();
    CardCombo playCard(const CardCombo &c);
    int bid(int currentBid);
    Human()
        : Player() {}
    Human(std::string nameIn, Position posIn)
        : Player(nameIn, posIn) {}
private:
    //print the hand for human player
    void printHand() const;
};

void Human::printHand() const {
    const std::vector<Card> & hand = getHand();
    for(int i = 0; i < hand.size(); i++) {
        std::cout << "[" << i << "]: " << hand[i];
    }
}

int Human::bid(int currentBid) {
    std::cout << "Human player " << getName() << "'s turn to bid\n";
    std::cout << "Current highest bid is " << currentBid << '\n';
    
    int input;
    std::cin >> input;
    
    while(input < 0 || input > 3) {
        std::cout << "Invalid Bid\n";
        std::cout << "Current highest bid is " << currentBid << '\n';
        
        std::cin >> input;
    }
    
    return input;
}

CardCombo Human::leadCard() {
    bool played = false;
    CardCombo combo;

    while (!played) {
        printHand();
        std::cout << "Human player " << getName() << "'s turn to play\n";
        std::cout << "Select card indicies separated by ','\n";
        std::cout << "e.g.: 0, 1\n";
    
        int input;
        std::vector<Card> cardsPlayed;
    
        while(std::cin >> input) {
            cardsPlayed.push_back(popCard(input));
        }
        std::sort(cardsPlayed.rbegin(), cardsPlayed.rend());
    
        combo = CardCombo(cardsPlayed);
    
        if(combo.getType() == error || combo.getType() == zero) {
            std::cout << "Invalid play\n";
            for(const Card &c : cardsPlayed) {
                addCard(c);
            }
            sortHand();
        } else {
            played = true;
        }
    }
    
    return combo;
}

CardCombo Human::playCard(const CardCombo &c) {
    bool played = false;
    CardCombo combo;
    
    while (!played) {
        printHand();
        std::cout << "Human player " << getName() << "'s turn to play\n";
        std::cout << "select card indicies separated by ','\n";
        std::cout << "e.g.: 0, 1\n";
        std::cout << "Current combo is ";
        c.printCombo();
        
        int input;
        std::vector<Card> cardsPlayed;
        
        while(std::cin >> input) {
            cardsPlayed.push_back(popCard(input));
        }
        std::sort(cardsPlayed.rbegin(), cardsPlayed.rend());
        
        combo = CardCombo(cardsPlayed);
        
        if(combo.getType() == error || (combo.getType() != zero && combo < c)) {
            std::cout << "Invalid play\n";
            for(const Card &c : cardsPlayed) {
                addCard(c);
            }
            sortHand();
        } else {
            played = true;
        }
    }
    
    return combo;
}

//SimpleBot, will play cards if it is possible
//will play cards that have the smallest value
// value (-inf, 9]: call 0
// value [10, 14]: call 1
// value [15, 19]: call 2
// value [20, inf): call 3
class SimpleBot : public Player {
public:
    virtual int bid(int currentBid);
    virtual CardCombo leadCard();
    virtual CardCombo playCard(const CardCombo &c);
    SimpleBot()
        : Player() {}
    SimpleBot(std::string nameIn, Position posIn)
        : Player(nameIn, posIn) {}
private:
    int calculateHandValue();
};

class SmartBot : public SimpleBot {
    
};
