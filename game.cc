#include "game.h"
using namespace std;

Game::Game(int numPlayers, int compPlayers, bool pure) {
    this->pure = pure;
    this->numPlayers = numPlayers;
    this->compPlayers = compPlayers;
    this->headSize = 0;
    this->totalHeads = 0;
    vector<string> deck;
    for (int val = 1; val <= 13; ++val) {
        for (int suit = 1; suit <= 4; ++suit) {
            string s = "";
            if (val == 1) {
                s += "A";
            } else if (val == 11) {
                s += "J";
            } else if (val == 12) {
                s += "Q";
            } else if (val == 13) {
                s += "K";
            } else {
                s += to_string(val);
            }
            if (suit == 1) {
                s += "H";
            } else if (suit == 2) {
                s += "S";
            } else if (suit == 3) {
                s += "C";
            } else if (suit == 4) {
                s += "D";
            }
            for (int i = 1; i <= numPlayers; ++i) {
                deck.push_back(s);
            }
            // cout << s << endl;
        }
    }
    for (int i = 1; i <= numPlayers; ++i) {
        deck.push_back("J");
        deck.push_back("J");
    }

    // shuffle the deck now
    shuffle(deck.begin(), deck.end(), random_device());
    int deckSize = deck.size();

    // put players in the vector
    for (int p = 1; p <= numPlayers; ++p) {
        auto player = make_shared<Player>();
        this->players.push_back(player);
    }

    int tempNumComp = this->compPlayers;
    for (int i = this->numPlayers-1; i >= 0; i--) {
        if (tempNumComp > 0) {
            this->players[i]->setOn();
            --tempNumComp;
        } else {
            break;
        }
    }

    // for (auto &c: this->players) {
    //     cout << "Comp: " << c->getIsComp() << endl;
    // }

    // for (int i = 1; i <= this->numPlayers; ++i) {
    //     cout << "Comp: " << this->playerIsComp(i) << endl;
    // }
    
    // put it equally in each player
    int p = 0;
    vector<string> temp;
    for (int i = 0; i < deckSize; ++i) {
        if (i%54 == 0 && i != 0) {
            this->players[p]->init(temp);
            temp.clear();
            ++p;
        }
        temp.push_back(deck[i]);
    }
    this->players[p]->init(temp);

    // for (int i = 0; i < deckSize; ++i) {
    //     cout << deck[i] << endl;
    // }
    
    // for (int i = 0; i < numPlayers; ++i) {
    //     cout << "Player " << i+1 << ":" << endl;
    //     for (auto &p: this->players[i]->drawPile) {
    //         cout << p << endl;
    //     }
    //     cout << this->players[i]->drawPile.size() << endl;
    // }

    // cout << deck.size() << endl;
}

int Game::getPlayerDrawSize(int player) {
    return this->players[player-1]->getDrawPileSize();
}

int Game::getHeadSize() {
    return this->headSize;
}

int Game::getNumPlayers() {
    return this->numPlayers;
}

void Game::attachToPreviousHead(int pos, string s) {
    this->heads.find(pos)->second.push_back(s);
}

void Game::addNewHead(std::string s) {
    vector<string> newHead;
    newHead.push_back(s);
    ++this->headSize;
    ++this->totalHeads;
    this->heads.insert(pair<int, vector<string>>(this->totalHeads, newHead));
    // for (auto it=this->heads.begin(); it!=this->heads.end(); ++it) {
    //     cout << it->first << " => " << it->second[0] << endl;
    // }
}

vector<string> Game::removeHeads(int pos) {
    vector<string> temp = this->heads.find(pos)->second;
    this->heads.erase(pos);
    --this->headSize;
    return temp;
}

string Game::removeTopCard(int playerNum) {
    this->players[playerNum-1]->removeTopFromDrawPile();
    // cout << this->players[playerNum-1]->get_playCard() << " from removeTopCard" << endl;
    return this->players[playerNum-1]->getPlayCard();
}

void Game::addTopCard(int playerNum, string card) {
    this->players[playerNum-1]->addTop(card);
}

std::map<int, std::vector<std::string>>::iterator Game::beginIteratorHeads() {
    return this->heads.begin();
}

std::map<int, std::vector<std::string>>::iterator Game::endIteratorHeads() {
    return this->heads.end();
}

std::vector<std::shared_ptr<Player>>::iterator Game::beginIteratorPlayers() {
    return this->players.begin();
}

std::vector<std::shared_ptr<Player>>::iterator Game::endIteratorPlayers() {
    return this->players.end();
}

Game::~Game() {}

int Game::cardToInt(std::string card) {
    card[0] = toupper(card[0]);
    if (card[0] == 'A') {
        return 1;
    } else if (card[0] == 'J') {
        return 11;
    } else if (card[0] == 'Q') {
        return 12;
    } else if (card[0] == 'K') {
        return 13;
    } else if (card[0] == '2') {
        return 2;
    } else if (card[0] == '3') {
        return 3;
    } else if (card[0] == '4') {
        return 4;
    } else if (card[0] == '5') {
        return 5;
    } else if (card[0] == '6') {
        return 6;
    } else if (card[0] == '7') {
        return 7;
    } else if (card[0] == '8') {
        return 8;
    } else if (card[0] == '9') {
        return 9;
    } else if (card[0] == '1') {
        return 10;
    }
    return -1;
}

bool Game::validMove(int move) {
    for (auto &c: this->heads) {
        if (move == c.first) {
            return true;
        }
    }
    return false;
}

bool Game::hasToCut(int playCard) { // if all heads are smaller than play card then return -1 else return 
    for (auto &c: this->heads) {
        int headCard = cardToInt(c.second.back());
        if (headCard >= playCard || headCard == 1 || playCard == 1) {
            return false;
        }
    }
    return true;
}

vector<string> Game::searchHeads(int move) {
    return this->heads.find(move)->second;
}

bool Game::validSuit(std::string &suit) {
    for (auto &c: suit) {
        c = toupper(c);
    }
    if (suit == "S" || suit == "H" || suit == "C" || suit == "D") {
        return true;
    }
    return false;
}

bool Game::validValue(std::string &val) {
    for (auto &c: val) {
        c = toupper(c);
    }
    if (val == "A" || val == "J" || val == "Q" || val == "K" || val == "2" || val == "3" || val == "4" ||
        val == "5" || val == "6" || val == "7" || val == "8" || val == "9" || val == "10" || val == "JOKER") {
        return true;
    }
    return false;
}

void Game::checkValidMove(int &move, int turn) {
    while (true) {
        if (this->validMove(move)) {
            break;
        }
        cout << endl;
        if (move == 0) {
            if (this->headSize == 1) {
                cout << "Cannot put reserve when number of heads is 1" << endl;
            } else {
                break;
            }
        } else {
            cout << move << " is not a valid head" << endl;
            // cout << "Invalid move " << move << endl;
        }
        cout << "Player " << turn << " move?" << endl;
        cin >> move;
    }
}

bool Game::playerWinCheck(int turn) {
    return this->players[turn-1]->winCheck();
}

string Game::getPlayerReserve(int turn) {
    return this->players[turn-1]->getReserve();
}

void Game::playerAddToDiscardPile(int turn, vector<string> heads) {
    this->players[turn-1]->addToDiscardPile(heads);
}

bool Game::playerIsComp(int turn) {
    return this->players[turn-1]->getIsComp();
}

void Game::playerCompOn(int turn) {
    this->players[turn-1]->setOn();
}

void Game::playerPutReserve(int turn, string card) {
    this->players[turn-1]->putReserve(card);
}

void Game::playerSwapReserve(int turn, string &card) {
    this->players[turn-1]->swapReserve(card);
}

void Game::playerSetReserveToEmpty(int turn) {
    this->players[turn-1]->setReserveToEmpty();
}

int Game::getOldestHead() {
    return this->heads.begin()->first;
}

void Game::checkPlayLessThanHeads(int &move, int playCardInt) {
    while (true) {
        if (this->validMove(move)) {
            int headCardInt = this->cardToInt(this->searchHeads(move).back());
            if (playCardInt <= headCardInt || headCardInt == 1 || playCardInt == 1) {
                break;
            }
        }
        cout << endl;
        cout << "Invalid Move" << endl;
        cout << "Your move?" << endl;
        cin >> move;
    }
}

void Game::jokerConvert(string &card, int move) {
    int headCardInt = this->cardToInt(this->searchHeads(move).back());
    string val;
    cout << "Joker value?" << endl;
    cin >> val;

    for (auto &c: val) {
        c = toupper(c);
    }

    while (true) {
        int valInt = 0;
        if (val == "A") {
            valInt = 1;
        } else if (val == "J") {
            valInt = 11;
        } else if (val == "Q") {
            valInt = 12;
        } else if (val == "K") {
            valInt = 13;
        } else if (val[0] >= 49 && val[0] <= 57) {
            valInt = stoi(val);
        }

        if ((valInt <= headCardInt || headCardInt == 1) && (valInt >= 1 && valInt <= 13)) {
            break;
        }

        cout << endl;

        if (valInt < 1 || valInt > 13) {
            cout << "Invalid Card" << endl;
        } else if (headCardInt != 1) {
            cout << "Joker value must be between (A";
            if (headCardInt == 11) {
                cout << "-J)" << endl;
            } else if (headCardInt == 12) {
                cout << "-Q)" << endl;
            } else if (headCardInt == 13) {
                cout << "-K)" << endl;
            } else {
                cout << "-" << headCardInt << ")" << endl;
            }
        }

        cout << "Joker value?" << endl;
        cin >> val;
    }
    
    card = val+card;
}

bool Game::getPure() {
    return this->pure;
}

int Game::compMove(string playCard) {
    int largestHead = this->cardToInt(this->heads.begin()->second.back());
    int retVal = this->heads.begin()->first;
    int playCardInt = this->cardToInt(playCard);
    int equalHeadRetVal = 0;
    // if it has to cut, then it will cut off the oldest head (ie 1st in the map)
    if (!this->hasToCut(playCardInt)) {
        // if not cut then find the largest head possible
        for (auto it = this->heads.begin(); it != this->heads.end(); ++it) {
            int tempHead = this->cardToInt(it->second.back());
            if (tempHead == playCardInt || tempHead == 1) {
                equalHeadRetVal = it->first;
            } else if (tempHead > largestHead) {
                largestHead = tempHead;
                retVal = it->first;
            }
        }
    }

    if (retVal == this->heads.begin()->first && equalHeadRetVal != 0) {
        retVal = equalHeadRetVal;
    }
    return retVal;
}
