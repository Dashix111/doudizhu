//
//  Pack_Test.cpp
//  doudizhu
//
//  Created by Bowen Dong on 12/24/18.
//  Copyright © 2018 Bowen Dong. All rights reserved.
//

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <cassert>

#include "Pack.h"

int main() {
    //test default constructor
    Pack p = Pack();
    p.printPack();
    Card c = Card(three, spade);
    assert(c == p.dealOne());
    
    //test istream constructor
    const std::string filename = "pack.in";
    std::ifstream is(filename);
    assert(is.is_open());
    Pack p1 = Pack(is);
    p1.printPack();
    Card c1 = Card(three, spade);
    assert(c1 == p1.dealOne());
    
    //test reset
    p.reset();
    assert(c == p.dealOne());
    p1.reset();
    assert(c1 == p1.dealOne());
    
    //test shuffle
    p.shuffle();
    p.reset();
    p.printPack();
    
    p.shuffle();
    p.reset();
    p.printPack();
    
    p1.shuffle();
    p1.reset();
    p1.printPack();
    
    p1.shuffle();
    p1.reset();
    p1.printPack();
    
    //test pickUpcard
    p.pickUpcard();
    std::cout << "New upcard: " << p.getUpcard() << '\n';
    p1.pickUpcard();
    std::cout << "New upcard: " << p1.getUpcard() << '\n';
    
    //test empty
    for(int i = 0; i < Pack::PACK_SIZE; i++) {
        p.dealOne();
        p1.dealOne();
    }
    assert(p.empty());
    assert(p1.empty());
    
    return 0;
}
