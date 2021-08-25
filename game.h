#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <utility>
#include <algorithm>
#include <random>
#include "player.h"

class Game {

    private:

    // id = int, value = vector of strings (where each string is a card)
    std::map<int, std::vector<std::string>> heads;

    // vector of shared pointers to player objects playing the game
    std::vector<std::shared_ptr<Player>> players;

    // keeps track of the number of players playing
    int numPlayers;

    // keeps track of number of computers if any or 0
    int compPlayers;

    // keeps track of the current number of heads
    int headSize;

    // keeps track of the total number of heads (current and removed)
    int totalHeads;

    // true if the pure rule applies
    bool pure;
    

    public:

    // constructor call for Game Class. Sets the board (heads) and shuffles card to every player
    Game(int numPlayers, int compPlayers, bool pure);
    
    // destructor for Game Class
    ~Game();
    
    // returns the begining iterator (first element) to the map of heads
    std::map<int, std::vector<std::string>>::iterator beginIteratorHeads();

    // returns the ending iterator (last element) to the map of heads
    std::map<int, std::vector<std::string>>::iterator endIteratorHeads();

    // returns the begining iterator (last element) to the vector of pointer to players
    std::vector<std::shared_ptr<Player>>::iterator beginIteratorPlayers();

    // returns the ending iterator (first element) to the vector of pointer to players
    std::vector<std::shared_ptr<Player>>::iterator endIteratorPlayers();

    // returns the head number of the oldest heads in the map of heads
    int getOldestHead();

    // gets the number of current heads
    int getHeadSize();

    int getPlayerDrawSize(int player);

    // returns the value of pure
    bool getPure();

    // checks if the move is valid and if the play card can be played on that head according to the rules
    void checkPlayLessThanHeads(int &move, int playCardInt);

    // removes the heads with id pos and returns all the cards (vector of strings) in that heads
    std::vector<std::string> removeHeads(int pos);

    // attaches card (string) to the heads with id pos
    void attachToPreviousHead(int pos, std::string card);

    // creates a new head and adds card (string) to it
    void addNewHead(std::string card);

    // removes the top card from the drawpile of the player passed in
    std::string removeTopCard(int playerNum);

    // adds the card to the to the drawpile of the player passed in
    void addTopCard(int playerNum, std::string card);

    // returns the number of players
    int getNumPlayers();

    // returns the integer value of the card
    int cardToInt(std::string card);

    // returns true if the move is valid and false otherwise
    bool validMove(int move);

    // returns true if the only option for the player is to cut the head and false otherwise
    bool hasToCut(int playCardInt);

    // returns the head pile (vector of strings) with id = move
    std::vector<std::string> searchHeads(int move);

    // returns true if the suit is a valid suit and false otherwise
    bool validSuit(std::string &suit);

    // returns true if the value is valid and false otherwise
    bool validValue(std::string &val);

    // checks if the move is valid and repeats it until the player enters a valid move
    void checkValidMove(int &move, int turn);

    // returns true if the player has won and false otherwise
    bool playerWinCheck(int player);

    // checks if player is a computer
    bool playerIsComp(int turn);

    void playerCompOn(int turn);

    // returns the reserve card of the player
    std::string getPlayerReserve(int player);

    // adds the heads (vector of strings) to the discard pile of the player
    void playerAddToDiscardPile(int player, std::vector<std::string> heads);

    // adds the card (string) to the reserve of the player
    void playerPutReserve(int player, std::string card);

    // swaps the reserve of the player with the current card
    void playerSwapReserve(int player, std::string &card);

    // sets the reserve of of the player to empty
    void playerSetReserveToEmpty(int player);

    // converts the Joker card passed in to set the appropriate value
    void jokerConvert(std::string &card, int move);

    // basic computer strategy
    int compMove(std::string playCard);
};

#endif
