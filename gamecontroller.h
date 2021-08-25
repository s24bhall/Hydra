#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <iostream>
#include <exception>
#include "game.h"
#include "print.h"

class GameController {
    private:
    // keeps track of the game board
    Game *game;
    // keeps track for printing
    Print *print;

    public:
    // constructor call for GameController. Sets the number of players passed in and 
    //   shuffles and distributes 54 cards each equally among all
    GameController(int numPlayers, int compPlayers, bool grammar, bool pure, bool gui);

    // destructor for GameController
    ~GameController();

    //controller called by main responsible for calling all the game and print methods and implements the game logic
    void play(bool testing);

    // used to set card during testing
    void testing(std::string &card);
};

#endif
