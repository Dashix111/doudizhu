//
//  Pack.cpp

#include <string>
#include <vector>
#include <cassert>
#include <algorithm>

#include "Card.h"
#include "Pack.h"

Pack::Pack() {
    for(Suit s = spade; s <= diamond; s = Suit(s+1)) {
        for(Rank r = three; r <= two; r = Rank(r+1)) {
            cards.push_back(Card(r, s));
        }
    }
    cards.push_back(Card(bJoker, joker));
    cards.push_back(Card(rJoker, joker));
    
    for(int i = 0; i < 3; i++) {
        landLordCards.push_back(cards[51+i]);
    }
    
    next = 0;
    upCard = 0;
}

Pack::Pack(std::istream &packInput) {
    std::string rankInput, suitInput, trash;
    packInput >> upCard;
    Rank r;
    Suit s;
    
    while(packInput.good() && cards.size() < PACK_SIZE) {
        packInput >> rankInput >> trash >> suitInput;
        if(rankInput == "three") {
            r = three;
        } else if (rankInput == "four") {
            r = four;
        } else if (rankInput == "five") {
            r = five;
        } else if (rankInput == "six") {
            r = six;
        } else if (rankInput == "seven") {
            r = seven;
        } else if (rankInput == "eight") {
            r = eight;
        } else if (rankInput == "nine") {
            r = nine;
        } else if (rankInput == "ten") {
            r = ten;
        } else if (rankInput == "jack") {
            r = jack;
        } else if (rankInput == "queen") {
            r = queen;
        } else if (rankInput == "king") {
            r = king;
        } else if (rankInput == "ace") {
            r = ace;
        } else if (rankInput == "two") {
            r = two;
        } else if (rankInput == "bjoker") {
            r = bJoker;
        } else if (rankInput == "rjoker") {
            r = rJoker;
        } else {
            assert(false);
        }
        
        if(suitInput == "spade") {
            s = spade;
        } else if (suitInput == "heart") {
            s = heart;
        } else if (suitInput == "club") {
            s = club;
        } else if (suitInput == "diamond") {
            s = diamond;
        } else if (suitInput == "joker"){
            s = joker;
        } else {
            assert(false);
        }
        
        cards.push_back(Card(r, s));
    }
    
    assert(cards.size() == Pack::PACK_SIZE);
    
    landLordCards.clear();
    for(int i = 0; i < 3; i++) {
        landLordCards.push_back(cards[51+i]);
    }
    
    next = 0;
}

Card Pack::dealOne() {
    assert(next < PACK_SIZE);
    return cards[next++];
}

void Pack::reset() {
    next = 0;
}

void Pack::shuffle() {
    assert(cards.size() == PACK_SIZE);
    srand(time(0));
    
    for(int i = 0; i < PACK_SIZE; i++) {
        int r = i + (rand() % (PACK_SIZE - i));
        std::swap(cards[i], cards[r]);
    }
    
    landLordCards.clear();
    for(int i = 0; i < 3; i++) {
        landLordCards.push_back(cards[51+i]);
    }
}

void Pack::pickUpcard() {
    srand(time(0));
    upCard = rand() % PACK_SIZE;
}

bool Pack::empty() const {
    return next == PACK_SIZE;
}

int Pack::getNext() const {
    return next;
}

int Pack::getUpcard() const {
    return upCard;
}

void Pack::printPack() const {
    std::cout << "Pack Cards:\n";
    for(Card c : cards) {
        std::cout << c;
    }
    std::cout << "\nLandlord Cards:\n";
    for(Card c : landLordCards) {
        std::cout << c;
    }
    std::cout << "Next card index: " << getNext() << '\n';
    std::cout << "Upcard index: " << getUpcard() << '\n';
}
