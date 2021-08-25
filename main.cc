#include <iostream>
#include <string>
#include "gamecontroller.h"
using namespace std;

int main(int argc, char *argv[]) {
    int numPlayers;
    cout << "How many players?" << endl;
    cin >> numPlayers;
    while (numPlayers < 2) {
        cout << endl;
        cout << "Sorry, the number of players has to be greater than equal to 2." << endl;
        cin >> numPlayers;
    }
    bool testing = false;
    bool grammar = false;
    bool pure = false;
    bool gui = false;
    bool comp = false;
    for (int i = 1; i < argc; ++i) {
        string input = argv[i];
        for (auto &c: input) {
            c = tolower(c);
        }
        if (input == "-testing") {
            testing = true;
        } else if (input == "--grammar") {
            grammar = true;
        } else if (input == "--pure") {
            pure = true;
        } else if (input == "--gui") {
            gui = true;
        } else if (input == "--comp") {
            comp = true;
        }
    }
    int compPlayers = 0;
    if (comp) {
        cout << "How many computers?" << endl;
        cin >> compPlayers;
        while (compPlayers < 1 || compPlayers > numPlayers) {
            cout << endl;
            cout << "Computers have to be between 1 and " << numPlayers << endl;
            cin >> compPlayers;
        }
    }
    cout << endl;
    cout << "============== WELCOME TO HYDRA ===============" << endl;
    cout << endl;
    // cout << boolalpha << "Testing: " << testing << "; grammar: " << grammar << "; pure: " << pure << "; GUI: " << gui << endl;
    GameController *controller = new GameController{numPlayers, compPlayers, grammar, pure, gui};
    controller->play(testing);
    delete controller;
}