#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>

class Player {
    private:

    // draw pile of each player (vector of strings where each string is a card)
    std::vector<std::string> drawPile;

    // discard pile of each player
    std::vector<std::string> discardPile;

    // player's reserve card ("" -> initially, filled with a card when a player puts/swaps a reserve)
    std::string reserve;

    // player's card in hand
    std::string playCard;

    // determines if a player is a human or a computer
    bool isComp = false;

    public:

    // constructor call for Player class
    Player();

    // destructor for Player class
    ~Player();

    // sets isComp to true
    void setOn();

    // sets isComp to false
    void setOff();

    bool getIsComp();

    // initializes the player's drawPile by pushing the elements of the argument 
    void init(std::vector<std::string> draw);
    
    // removes top card from draw pile and sets it as the playCard
    void removeTopFromDrawPile();

    // returns the playcard
    std::string getPlayCard();

    // returns the reserve of the player
    std::string getReserve();

    // returns the size of the drawPile
    int getDrawPileSize();

    // returns the size of the discardPile
    int getDiscardPileSize();

    // sets the player card where (card = num+suit)
    void setCard(std::string suit, std::string num, std::string &card);

    // adds the heads to the player's discard pile
    void addToDiscardPile(std::vector<std::string> heads);

    // returns true if player wins the game and false otherwise
    bool winCheck();

    // swaps the playCard with the reserve
    void swapReserve(std::string &playCard);

    // puts the playCard to the reserve
    void putReserve(std::string playCard);

    // adds the card to the top of the drawPile
    void addTop(std::string card);

    // sets the reserve to empty
    void setReserveToEmpty();
};

#endif
