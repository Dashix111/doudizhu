//  Player.cpp
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

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

std::vector<Card> & Player::getHand() {
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

struct HandValueType {
    int numRound;
    int value;
};

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
    virtual void addCard(const Card &c);
    void rememberCard(const Card &c);
    SimpleBot()
        : Player() {
            cardsUnknown.reserve(54);
            for(Suit s = spade; s <= diamond; s = Suit(s+1)) {
                for(Rank r = three; r <= two; r = Rank(r+1)) {
                    cardsUnknown.push_back(Card(r, s));
                }
            }
            cardsUnknown.push_back(Card(bJoker, joker));
            cardsUnknown.push_back(Card(rJoker, joker));
        }
    SimpleBot(std::string nameIn, Position posIn)
        : Player(nameIn, posIn) {
            cardsUnknown.reserve(54);
            for(Suit s = spade; s <= diamond; s = Suit(s+1)) {
                for(Rank r = three; r <= two; r = Rank(r+1)) {
                    cardsUnknown.push_back(Card(r, s));
                }
            }
            cardsUnknown.push_back(Card(bJoker, joker));
            cardsUnknown.push_back(Card(rJoker, joker));
        }
private:
    //keep track of all cards played and in hand
    std::vector<Card> cardsKnown;
    std::vector<Card> cardsUnknown;
    
    HandValueType calculateHandValue(const std::vector<Card> &hand);
    
    //get the most optimal (highest value) way to play current hand
    std::vector<CardCombo> getBestCardList(const std::vector<Card> &hand);
    
    //find the CardCombo to play that will maximize the value for remaining
    //cards
    //MODIFIES hand
    CardCombo findBestCards(std::vector<Card> &hand);
};

//REQUIRE sorted cardsKnown
bool noRocket(const std::vector<Card> &cardsKnown) {
    return cardsKnown[0].getRank() == rJoker &&
    cardsKnown[1].getRank() == bJoker;
}

//REQUIRE sorted cards
//return the index of the first card of the bomb in cards or -1
int getIndexOfBiggest(const std::vector<Card> &cards, CardComboType type) {
    if(type == bomb){
        int count = 1;
        for(int i = 1; i < cards.size(); i++) {
            if(cards[i] == cards[i-1]) {
                if(++count == 4) {
                    return i-3;
                }
            } else {
                count = 1;
            }
            
        }
        return -1;
    }
    
    return -1;
}

void SimpleBot::rememberCard(const Card &c) {
    cardsKnown.push_back(c);
    for(int i = 0; i < cardsUnknown.size(); i++) {
        if(cardsUnknown[i].getRank() == c.getRank() &&
           cardsUnknown[i].getSuit() == c.getSuit()) {
            cardsUnknown.erase(cardsUnknown.begin()+i);
        }
    }
}

void SimpleBot::addCard(const Card &c) {
    Player::addCard(c);
    rememberCard(c);
}

HandValueType SimpleBot::calculateHandValue(const std::vector<Card> &hand) {
    CardCombo combo(hand);
    if(combo.getType() != error &&
       combo.getType() != bomb &&
       combo.getType() != rocket) {
        return {1, combo.getValue()};
    }
    
    std::vector<CardCombo> bestCardList = getBestCardList(hand);
    int totalValue = 0;
    
    for(const auto & combo : bestCardList) {
        totalValue += combo.getValue();
    }
    
    return {(int)(bestCardList.size()), totalValue};
}

int SimpleBot::bid(int currentBid) {
    int handScore = calculateHandValue(getHand()).value;
    
    if(handScore >= 20 && currentBid < 3) {
        return 3;
    } else if (handScore >= 15 && handScore < 20 && currentBid < 2) {
        return 2;
    } else if (handScore >= 10 && handScore < 15 && currentBid < 1) {
        return 1;
    }
    return 0;
}


CardCombo SimpleBot::findBestCards(std::vector<Card> &hand) {
    
    return CardCombo();
}

CardCombo SimpleBot::leadCard() {
    //if there is only one combo is left, play it
    std::vector<Card> hand = getHand();
    CardCombo combo(hand);
    if(combo.getType() != error && combo.getType() != zero) {
        hand.clear();
        return combo;
    }
    
    //if there are two combos left, and one of which is unbeatable
    //play the unbeatable combo
    //unbeatable combo = rockets || biggest bomb || biggest of each type
    if(hand[0].getRank() == rJoker && hand[1].getRank() == bJoker &&
       CardCombo(std::vector<Card>(hand.begin()+2, hand.end())).getType() !=
       error) {
        combo = CardCombo(std::vector<Card>(hand.begin(), hand.begin()+2));
        hand.erase(hand.begin(), hand.begin()+2);
        return combo;
    }
    std::sort(cardsKnown.rbegin(), cardsKnown.rend());
    if(noRocket(cardsKnown)) {
        int bombIndexHand = getIndexOfBiggest(hand, bomb);
        int bombIndexUnknownCards = getIndexOfBiggest(cardsUnknown, bomb);
        //check have biggest possible bomb or not
        if(bombIndexHand != -1) {
            if(hand[bombIndexHand] > cardsUnknown[bombIndexUnknownCards]) {
                //find all cards that are not a part of the bomb and check whether
                //they are a combo
                std::vector<Card> remainingCards;
                for(int i = 0; i < hand.size(); i++) {
                    if(i < bombIndexHand || i > bombIndexHand + 3) {
                        remainingCards.push_back(hand[i]);
                    }
                }
                if(CardCombo(remainingCards).getType() != error) {
                    combo = CardCombo(std::vector<Card>(
                                    hand.begin()+bombIndexHand,
                                    hand.begin()+bombIndexHand+4));
                    hand = remainingCards;
                    return combo;
                }
            }
        } else {
            //no possible bombs, so whether have the biggest of each type
            if(bombIndexUnknownCards == -1) {
                std::vector<Card> remainingCards;
                //single
                int indexHand = getIndexOfBiggest(hand, single);
                int indexUC = getIndexOfBiggest(cardsUnknown, single);
                if(!(hand[indexHand] < cardsUnknown[indexUC])) {
                    for(int i = 0; i < hand.size(); i++) {
                        if(i != indexHand) {
                            remainingCards.push_back(hand[i]);
                        }
                    }
                    if(CardCombo(remainingCards).getType() != error) {
                        combo = CardCombo(std::vector<Card>(hand.begin()+indexHand, hand.begin()+indexHand+1));
                        hand = remainingCards;
                        return combo;
                    }
                }
                //pair
                indexHand = getIndexOfBiggest(hand, pair);
                indexUC = getIndexOfBiggest(cardsUnknown, pair);
                if(indexHand != -1 &&
                   !(hand[indexHand] < cardsUnknown[indexUC])) {
                    remainingCards.clear();
                    for(int i = 0; i < hand.size(); i++) {
                        if(i < indexHand || i > indexHand+1) {
                            remainingCards.push_back(hand[i]);
                        }
                    }
                    if(CardCombo(remainingCards).getType() != error) {
                        combo = CardCombo(std::vector<Card>(hand.begin()+indexHand, hand.begin()+indexHand+2));
                        hand = remainingCards;
                        return combo;
                    }
                }
                //trio
                indexHand = getIndexOfBiggest(hand, trio);
                indexUC = getIndexOfBiggest(cardsUnknown, trio);
                if(indexHand != -1 &&
                   !(hand[indexHand] < cardsUnknown[indexUC])) {
                    remainingCards.clear();
                    for(int i = 0; i < hand.size(); i++) {
                        if(i < indexHand || i > indexHand+2) {
                            remainingCards.push_back(hand[i]);
                        }
                    }
                    if(CardCombo(remainingCards).getType() != error) {
                        combo = CardCombo(std::vector<Card>(hand.begin()+indexHand, hand.begin()+indexHand+3));
                        hand = remainingCards;
                        return combo;
                    }
                }
                //straight
                //pairStraight
                //trioStraight
                //trioSingle,
                //trioPair
                //airplaneSingle,
                //airPlanePair
            }
        }
        
    }
    
    //if there are three combos left, and one of which is unbeatable
    //and the unbeatble combo can beat another combo,
    //play the combo that can be beaten by the unbeatable combo
    
    
    //else call findBestCards
    
}

CardCombo SimpleBot::playCard(const CardCombo &c) {
    
    return CardCombo();
}

std::vector<CardCombo> SimpleBot::getBestCardList(const std::vector<Card> &hand) {
    std::vector<CardCombo> result;
    std::vector<Card> cards = hand;
    
    while(!cards.empty()) {
        CardCombo combo = findBestCards(cards);
        assert(combo.getType() != error || combo.getType() != zero);
        
        result.push_back(combo);
    }
    
    return result;
}

class SmartBot : public SimpleBot {
    
};
