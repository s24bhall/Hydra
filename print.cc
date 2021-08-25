#include "print.h"
using namespace std;

Print::Print(bool grammar) {
    this->grammar = grammar;
}

void Print::printHeads(std::map<int, std::vector<std::string>>::iterator begin, 
                        std::map<int, std::vector<std::string>>::iterator end) {
    cout << endl;
    cout << "Heads:" << endl;
    for (auto it = begin; it != end; ++it) {
        cout << it->first << ": " << it->second[it->second.size()-1];
        cout << " (" << it->second.size() << ")" << endl;
    }
}

void Print::printPlayerInitial(std::vector<std::shared_ptr<Player>>::iterator begin,
                                std::vector<std::shared_ptr<Player>>::iterator end, int turn) {
    cout << endl;
    cout << "Players:" << endl;
    int count = 1;
    for (auto it = begin; it != end; ++it) {
        int drawSize = (*it)->getDrawPileSize();
        int discardSize = (*it)->getDiscardPileSize();
        cout << "Player " << count << ": " << drawSize+discardSize << " (" << drawSize << " draw, ";
        cout << discardSize << " discard)" << endl;
        ++count;
    }
    cout << endl;
    cout << "Player " << turn << ", it is your turn." << endl << endl;
}

void Print::printPlayerPlay(std::vector<std::shared_ptr<Player>>::iterator begin,
                            std::vector<std::shared_ptr<Player>>::iterator end, int turn,
                            int remain, bool reserve, string playCard) {
    cout << endl;
    cout << "Players:" << endl;
    int count = 1;
    for (auto it = begin; it != end; ++it) {
        int drawSize = (*it)->getDrawPileSize();
        int discardSize = (*it)->getDiscardPileSize();
        cout << "Player " << count << ": " << drawSize+discardSize << " (" << drawSize << " draw, ";
        cout << discardSize << " discard)";
        if (count == turn) {
            cout << " + 1 in hand, " << remain << " remaining, " << noboolalpha << reserve << " in reserve";
        }
        cout << endl;
        ++count;
    }
    cout << endl;
    if (playCard == "J") {
        playCard = "Joker";
    }
    cout << "Player " << turn << " you are holding a";
    
    if (this->grammar && (playCard[0] == 'A' || playCard[0] == '8')) {
        cout << "n";
    }
    cout << " " << playCard << ". Your move?" << endl;
}

void Print::playerWin(int turn) {
    cout << "Player " << turn << " wins!" << endl;
}
