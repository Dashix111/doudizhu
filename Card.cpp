//
//  Card.cpp
#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

#include "Card.h"

Card::Card() {
    rank = three;
    suit = spade;
}

Card::Card(Rank rankIn, Suit suitIn) {
    rank = rankIn;
    suit = suitIn;
}

bool operator<(const Card &lhs, const Card &rhs) {
    return lhs.getRank() < rhs.getRank();
}

bool operator>(const Card &lhs, const Card &rhs) {
    return lhs.getRank() > rhs.getRank();
}

bool operator==(const Card &lhs, const Card &rhs) {
    return lhs.getRank() == rhs.getRank();
}

bool operator!=(const Card &lhs, const Card &rhs) {
    return lhs.getRank() != rhs.getRank();
}

std::ostream & operator<<(std::ostream &os, const Card &card){
    std::string suit, rank;
    switch (card.getSuit()) {
        case spade:
            suit = "spade";
            break;
        case heart:
            suit = "heart";
            break;
        case diamond:
            suit = "diamond";
            break;
        case club:
            suit = "club";
            break;
        default:
            suit = "Joker";
            break;
    }
    
    switch (card.getRank()) {
        case three:
            rank = "three";
            break;
        case four:
            rank = "four";
            break;
        case five:
            rank = "five";
            break;
        case six:
            rank = "six";
            break;
        case seven:
            rank = "seven";
            break;
        case eight:
            rank = "eight";
            break;
        case nine:
            rank = "nine";
            break;
        case ten:
            rank = "ten";
            break;
        case jack:
            rank = "jack";
            break;
        case queen:
            rank = "queen";
            break;
        case king:
            rank = "king";
            break;
        case ace:
            rank = "ace";
            break;
        case two:
            rank = "two";
            break;
        case bJoker:
            rank = "bJoker";
            break;
        case rJoker:
            rank = "rJoker";
            break;
            
        default:
            break;
    }

    os << rank << " of " << suit << '\n';
    return os;
}

CardCombo::CardCombo(const std::vector<Card> &cardsIn, Card &compareCardIn, int numCardsIn, int valueIn, CardComboType typeIn) {
    numCards = numCardsIn;
    value = valueIn;
    type = typeIn;
    compareCard = compareCardIn;
    for(int i = 0; i < numCards; i++) {
        cards[i] = cardsIn[i];
    }
    std::sort(cards.rbegin(), cards.rend());
}

bool isSameType(const CardCombo &a, const CardCombo &b) {
    return a.getType() == b.getType();
}

bool operator<(const CardCombo &lhs, const CardCombo &rhs) {
    if(isSameType(lhs, rhs)) {
        return lhs.getCompareCard() < rhs.getCompareCard();
    } else {
        if(lhs.getType() == rocket) {
            return false;
        } else if (rhs.getType() == rocket) {
            return true;
        } else if (lhs.getType() == bomb) {
            return false;
        } else if (rhs.getType() == bomb) {
            return true;
        }
    }
    
    assert(false);
    return false;
}

bool operator>(const CardCombo &lhs, const CardCombo &rhs) {
    if(isSameType(lhs, rhs)) {
        return lhs.getCompareCard() > rhs.getCompareCard();
    } else {
        if(lhs.getType() == rocket) {
            return true;
        } else if (rhs.getType() == rocket) {
            return false;
        } else if (lhs.getType() == bomb) {
            return true;
        } else if (rhs.getType() == bomb) {
            return false;
        }
    }
    
    assert(false);
    return false;
}
std::ostream & operator<<(std::ostream &os, const CardCombo &combo){
    std::string type;
    switch (combo.getType()) {
        case zero:
            type = "zero";
            break;
        case single:
            type = "single";
            break;
        case pair:
            type = "pair";
            break;
        case trio:
            type = "trio";
            break;
        case straight:
            type = "straight";
            break;
        case pairStraight:
            type = "pairStraight";
            break;
        case trioStraight:
            type = "trioStraight";
            break;
        case trioSingle:
            type = "trioSingle";
            break;
        case trioPair:
            type = "trioPair";
            break;
        case airplanePair:
            type = "airplanePair";
            break;
        case airplaneSingle:
            type = "airplaneSingle";
            break;
        case fourSingles:
            type = "fourSingles";
            break;
        case fourPairs:
            type = "fourPairs";
            break;
        case bomb:
            type = "bomb";
            break;
        case rocket:
            type = "rocket";
            break;
        
        default:
            type = "error";
            break;
    }
    os << type << '\n';
    for(int i = 0; i < combo.getNumCards(); i++){
        os << combo.getCards()[i];
    }
    return os<<'\n';
}

//Require sorted in descending order
bool isStraight(const std::vector<Card> &cards) {
    if(cards[0] > Card(ace, spade)) {
        return false;
    }
    for(int i = 1; i < cards.size(); i++) {
        if(cards[i-1].getRank() != cards[i-1].getRank() + 1) {
            return false;
        }
    }
    return true;
}

//Require sorted in descending order
bool isPairStraight(const std::vector<Card> &cards) {
    if(cards[0] > Card(ace, spade)) {
        return false;
    }
    if(cards.size() % 2 == 1 ||
       cards.size() < 6 ||
       cards[0] != cards[1] ) {
        return false;
    }
    
    for(int i = 2; i < cards.size(); i += 2) {
        if(cards[i] != cards[i+1] ||
           cards[i-2].getRank() != cards[i].getRank() + 1) {
            return false;
        }
    }
    return true;
}

//Require sorted in descending order
bool isTrioStraight(const std::vector<Card> &cards) {
    if(cards[0] > Card(ace, spade)) {
        return false;
    }
    if(cards.size() % 3 != 0 ||
       cards.size() < 6 ||
       (cards[0] != cards[1] || cards[1] != cards[2])) {
        return false;
    }
    
    for(int i = 3; i < cards.size(); i += 3) {
        if(cards[i] != cards[i+1] || cards[i+1] != cards[i+2] ||
           cards[i-3].getRank() != cards[i].getRank() + 1) {
            return false;
        }
    }
    
    return true;
}

//Require sorted in descending order
int isAirPlaneSingle(const std::vector<Card> &cards) {
    if(cards.size() < 8) {
        return -1;
    }
    
    int numSingle = 0, numTrio = 0, currentSize = 1;
    int previousRank = cards[0].getRank();
    int compareCardIndex = -1;
    
    for(int i = 1; i < cards.size(); i++) {
        if(currentSize == 3) {
            currentSize = 0;
            previousRank = cards[i].getRank();
            if(numTrio++ == 0) {
                compareCardIndex = i - 1;
            }
        }
        
        if(cards[i].getRank() == previousRank) {
            currentSize++;
            
        } else {
            numSingle+=currentSize;
            currentSize = 1;
            previousRank = cards[i].getRank();
        }
    }
    if(currentSize == 3) {
        numTrio++;
    } else {
        numSingle++;
    }
    
    if(numSingle == numTrio && numTrio > 1) {
        return compareCardIndex;
    }
    return -1;
}

//Require sorted in descending order
int isAirPlanePair(const std::vector<Card> &cards) {
    if(cards.size() < 10) {
        return -1;
    }
    int numDouble = 0, numTrio = 0, currentSize = 1;
    int previousRank = cards[0].getRank();
    int compareCardIndex = -1;
    
    //3355566777
    for(int i = 1; i < cards.size(); i++) {
        if(cards[i].getRank() == previousRank) {
            currentSize++;
        } else {
            if (currentSize == 2) {
                numDouble++;
            } else if (currentSize == 3) {
                if(numTrio++ == 0) {
                    compareCardIndex = i - 1;
                }
            } else {
                return -1;
            }
            currentSize = 1;
            previousRank = cards[i].getRank();
        }
    }
    if(currentSize == 3) {
        numTrio++;
    } else if(currentSize == 2) {
        numDouble++;
    } else {
        return -1;
    }
    
    if(numTrio == numDouble && numTrio > 1) {
        return compareCardIndex;
    }
    
    return -1;
}

int CardCombo::calculateValue() {
    if(type == error) {
        return 0;
    } else if (type == zero) {
        return 0;
    } else if (type == single) {
        return (int)(compareCard.getRank()) - 10; //range from -7~7
    } else if (type == pair) {
        return (int)(compareCard.getRank()) - 10;
    } else if (type == trio) {
        return (int)(compareCard.getRank()) - 10;
    } else if (type == straight) {
        return (int)(compareCard.getRank()) - 10 + 1;
    } else if (type == pairStraight) {
        return (int)(compareCard.getRank()) - 10 + 1;
    } else if (type == trioStraight) {
        return ((int)(compareCard.getRank()) - 3 + 1) / 2;
    } else if (type == trioSingle) {
        return (int)(compareCard.getRank()) - 10;
    } else if (type == trioPair) {
        return (int)(compareCard.getRank()) - 10;
    } else if (type == airplaneSingle) {
        return ((int)(compareCard.getRank()) - 3 + 1) / 2;
    } else if (type == airplanePair) {
        return ((int)(compareCard.getRank()) - 3 + 1) / 2;
    } else if (type == fourSingles) {
        return ((int)(compareCard.getRank()) - 3) / 2;
    } else if (type == fourPairs) {
        return ((int)(compareCard.getRank()) - 3) / 2;
    } else if (type == bomb) {
        return (int)(compareCard.getRank()) - 3 + 7;
    } else if (type == rocket) {
        return 20;
    }
    return 0;
}

CardCombo::CardCombo(const std::vector<Card> &cardsIn) {
    numCards = (int)cardsIn.size();
    for(int i = 0; i < numCards; i++) {
        cards.push_back(cardsIn[i]);
    }
    std::sort(cards.rbegin(), cards.rend());
    
    
    if(cards.size() == 0) {
        type = zero;
        compareCard = Card();
    } else {
        compareCard = cards[0];
        if (cards.size() == 1) {
            type = single;
        } else if (cards.size() == 2) {
            if(cards[0].getRank() == rJoker &&
               cards[1].getRank() == bJoker) {
                type = rocket;
            } else if (cards[0] == cards[1]) {
                type = pair;
            } else {
                type = error;
            }
        } else if (cards.size() == 3) {
            if(cards[0] == cards[1] &&
               cards[1] == cards[2]) {
                type = trio;
            } else {
                type = error;
            }
        } else if (cards.size() == 4) {
            if(cards[1] == cards[2]) {
                if(cards[0] == cards[1]) {
                    if(cards[2] == cards[3]) {
                        type = bomb;
                    } else {
                        type = trioSingle;
                    }
                } else if (cards[2] == cards[3]) {
                    type = trioSingle;
                    compareCard = cards[1];
                } else {
                    type = error;
                }
            } else {
                type = error;
            }
        } else if (cards.size() == 5) {
            if(cards[0] == cards[1] &&
               cards[3] == cards[4]) {
                if(cards[2] == cards[0]) {
                    type = trioPair;
                } else if (cards[2] == cards[4]) {
                    compareCard = cards[2];
                    type = trioPair;
                } else {
                    type = error;
                }
            } else if (isStraight(cardsIn)) {
                type = straight;
            } else {
                type = error;
            }
        } else if (cards.size() == 6) {
            if(isStraight(cards)){
                type = straight;
            }else if(isTrioStraight(cards)){
                type = trioStraight;
            }else if(isPairStraight(cards)){
                type = pairStraight;
            }else if(cards[0]==cards[3] || cards[1]==cards[4] || cards[2]== cards[5]){
                type = fourSingles;
                compareCard = cards[2];
            }else{
                type = error;
            }
        } else if (cards.size() == 8) {
            int aps = isAirPlaneSingle(cards);
            int app = isAirPlanePair(cards);
            
            if(cards[0] == cards[1] && cards[2] == cards[3] &&
               cards[4] == cards[5] && cards[6] == cards[7]) {
                if(cards[0] == cards[2]) {
                    type = fourPairs;
                } else if (cards[2] == cards[4]) {
                    type = fourPairs;
                    compareCard = cards[2];
                } else if (cards[4] == cards[6]) {
                    type = fourPairs;
                    compareCard = cards[4];
                } else if (isPairStraight(cards)) {
                    type = pairStraight;
                } else {
                    type = error;
                }
            } else if (isStraight(cards)) {
                type = straight;
            } else if (isTrioStraight(cards)) {
                type = trioStraight;
            } else if (aps != -1) {
                type = airplaneSingle;
                compareCard = cards[aps];
            } else if (app != -1) {
                type = airplanePair;
                compareCard = cards[app];
            } else if(isStraight(cards)) {
                type = straight;
            } else {
                type = error;
            }
        } else {
            int aps = isAirPlaneSingle(cards);
            int app = isAirPlanePair(cards);
            
            if(isStraight(cards)) {
                type = straight;
            } else if (isPairStraight(cards)) {
                type = pairStraight;
            } else if (isTrioStraight(cards)) {
                type = trioStraight;
            } else if (aps != -1) {
                type = airplaneSingle;
                compareCard = cards[aps];
            } else if (app != -1) {
                type = airplanePair;
                compareCard = cards[app];
            } else {
                type = error;
            }
        }
    }
    
    value = calculateValue();
}

void CardCombo::printCombo() const {
    for(int i = 0; i < numCards; i++) {
        std::cout << cards[i];
    }
}
