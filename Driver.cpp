//
//  main.cpp
//  doudizhu
//
//  Created by Bowen Dong on 12/21/18.
//  Copyright © 2018 Bowen Dong. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <vector>

#include "Player.h"
#include "Pack.h"
#include "Card.h"

class Game {
private:
    std::vector<Player> players;
    Pack pack;
    int landLordIndex;
    int callerIndex;
    int lastWinnerIndex;
    int currentPlayerIndex;
    CardCombo currentCombo;
public:
    Game();
    Game(Player *p1, Player *p2, Player *p3,
         Pack &pack);
    
    bool isOverGame();
    
    void shufflePack();
    
    void deal();
    
    void callLandLord();
    
    //return next leader
    int playRound();
};
