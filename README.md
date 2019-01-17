# doudizhu
The goal for this project is to create a terminal based simulator and an AI algorithm for the popular Chinese card game, Dou Dizhu(斗地主). Dou Dizhu is usually played with 3 players, one of which is the landlord (Dizhu地主), the other two are the peasants and work as a team. The goal for the landlord is to first play out all of his cards with valid combinations, and the goal for the peasants is to let one of them first play out all of his cards with the same valid combinations.

## Game Set Up
The game uses the standard 54 cards pack. The suit is ignored.

The cards rank from the lowest to highest: 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K, A, 2, Black Joker, Red Joker

#### Deal 
Before the dealer deals the cards, one card selected at random will be turned to face up and inserted into the pack to be dealt. The player who has that card will have the priviledge to start the auction. The dealer will deal 17 cards to each player and leave 3 cards in the pack. These cards will later be given to the play who win the auction as the landlord. 

#### Auction
Players can bid 1, 2, 3, or pass in order to become the landlord. The player with the face up card call first, and each play call either pass or bid higher. The winner (the first player who calls 3 or the player with the highest bid) is going to become the landlord and take the remaining cards in the pack. If everyone decides to pass, the cards will be collected and re-dealt. 

#### Play
The landlord plays first. A player can play any legal combination when he leads a round. In one round, each subsequent player can either pass or play a higher combination of the same type and of the same number of cards. There are two exceptions: a rocket (Black Joker and Red Joker) can beat any combination of cards, a bomb (4 cards of the same rank) can beat any combination of cards except the rockets and bombs higher than it. The round will end when two consecutive players pass. 

###### Legal Combinations 
