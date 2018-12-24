//
//  CardTest.cpp
//  
//
//  Created by masteradafa on 12/24/18.
//

#include "Card.h"
#include <cassert>
#include <iostream>
#include <vector>
#include "Pack.h"


int main(){
    Pack p1 = Pack();
    std::vector<Card> cards;
    std::vector<Card> sixes;
    
    for(int i = 0;i < 54;i++){
        Card c = p1.dealOne();
        cards.push_back(c);
        if(i%13==3){
            sixes.push_back(c);
        }
    }
    
    for(Card a:sixes){
        std::cout << a;
    }
    assert(sixes[0]==sixes[1]);
    assert(sixes[2]==sixes[1]);
    assert(sixes[3]==sixes[1]);
    
    const std::vector<Card> a = sixes;
    CardCombo c = CardCombo(a);
    std::cout << c;
}
