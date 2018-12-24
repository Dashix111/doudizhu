//
//  CardTest.cpp
//  
//
//  Created by masteradafa on 12/24/18.
//

#include "Card.h"
#include <cassert>
#include <iostream>
#include "Pack.h"


int main(){
    Pack p1 = Pack();
    for(int i = 0;i < 54;i++){
        std::cout << p1.dealOne();
    }
    
}
