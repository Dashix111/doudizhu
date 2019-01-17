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

Note: a player passing on one turn does not prevent the player from playing on the same round. For example, player A leads with 3, player B passes, Player C plays 4, Player A plays 5, Play B can still play. 

###### Legal Combinations 
1. Single Card: rank from 3 to Red Joker
2. Pair: rank from 3 to 2
3. Trio: rank from 3 to 2
4. Trio with a Single: a Trio with any added card that differs from the Trio, e.g. 3-3-3-4. Rank according to the Trio, so 8-8-8-3 beats 7-7-7-Red Joker
5. Trio with a Pair: a Trio with another pair, e.g. 3-3-3-4-4. Rank according to the Trio.
6. Straight: at least 5 consecutive cards from 3 to Ace, e.g. 10-J-Q-K-A. Rank according to the biggest card. Straight can only beat straight of the same length, so for example, 10-J-Q-K-A cannot beat 3-4-5-6-7-8. 
7. Straight of Pairs: at least 3 consecutive Pairs from 3 to Ace, e.g. 3-3-4-4-5-5. Rank according to the biggest Pair. 
8. Straight of Trios: at least 2 consecutive Trios from 3 to Ace, e.g. 3-3-3-4-4-4. Rank according to the biggest Trio. 
9. Airplane with Singles: at least 2 consecutive Trios from 3 to Ace with another card for each Trio, e.g. 3-3-3-4-4-4-5-6. Rank according to the biggest Trio. 
10. Airplane with Pairs: at least 2 consecutive Trios from 3 to Ace with another Pair for each Trio, e.g. 3-3-Q-Q-Q-K-K-K-2-2.
11. Bomb: 4 cards of the same rank, e.g. 2-2-2-2. Rank from 3 to 2. A Bomb can beat any card of combination 1-10, 12, and 13 as well as smaller bombs.
12. Quad with Singles: a quad with 2 other cards of the different kind, e.g. 3-4-2-2-2-2. Rank from 3 to 2. Quad with Singles do not have the ability of the bomb to beat cards of other combinaitons. 
13. Quad with Pairs: a quad with 2 different Pairs, e.g. 3-3-4-4-4-4-5-5. Rank from 3 to 2. Quad with Singles do not have the ability of the bomb to beat cards of other combinations. 
14. Rockets: Black Joker with Red Joker. A rocket can beat any combination of cards. 
