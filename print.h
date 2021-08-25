#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include "game.h"

class Print {
    private:

    bool grammar;


    public:

    // constructor call for print class
    Print(bool grammar);

    // prints all the heads from the game
    void printHeads(std::map<int, std::vector<std::string>>::iterator begin, std::map<int, std::vector<std::string>>::iterator end);
    
    // prints the status of every player before the turn starts
    void printPlayerInitial(std::vector<std::shared_ptr<Player>>::iterator begin, std::vector<std::shared_ptr<Player>>::iterator end, int turn);
    
    // prints the status of every player during the turn
    void printPlayerPlay(std::vector<std::shared_ptr<Player>>::iterator begin, std::vector<std::shared_ptr<Player>>::iterator end, int turn, int remain, bool reserve, std::string playCard);
    
    // prints the player that won the game
    void playerWin(int player);
};

#endif