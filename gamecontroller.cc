#include "gamecontroller.h"
using namespace std;

GameController::GameController(int numPlayers, int compPlayers, bool grammar, bool pure, bool gui) {
    this->game = new Game{numPlayers, compPlayers, pure};
    this->print = new Print{grammar};
}

GameController::~GameController() {
    delete this->game;
    delete this->print;
}

void GameController::play(bool test) {
    // cout << boolalpha << testing << endl;
    int turn = 1;
    const int numPlayers = this->game->getNumPlayers();
    string firstHead = this->game->removeTopCard(turn);
    
    // testing with first head
    if (test) {
        cout << endl << endl;
        cout << "--- TESTING MODE ---" << endl;
        cout << endl;
        cout << "Set first Head Player 1" << endl;
        testing(firstHead);
    }

    // change Joker if it is the first head
    if (firstHead == "J") {
        firstHead = "2J";
    }

    // cout << firstHead << ": first head" << endl;
    // add first head to the game
    this->game->addNewHead(firstHead);
     
    // int a = 0;    testing integer to limit the value

    while (true) {
        // print the heads
        this->print->printHeads(this->game->beginIteratorHeads(), this->game->endIteratorHeads());

        // limit the turn within the number of players
        ++turn;
        if (turn > numPlayers) {
            turn = 1;
        }

        // print initial stage of players
        this->print->printPlayerInitial(this->game->beginIteratorPlayers(), this->game->endIteratorPlayers(), turn);

        
        int headSize = this->game->getHeadSize();
        while (headSize > 0) {
            // print heads everytime a player has a move
            this->print->printHeads(this->game->beginIteratorHeads(), this->game->endIteratorHeads());
            
            // remove the top card of the player whose turn it is and set it as the play card
            string playCard = this->game->removeTopCard(turn);

            // testing mode
            if (test) {
                cout << endl << endl;
                cout << "--- TESTING MODE ---" << endl;
                cout << endl;
                cout << "Set Player " << turn << " Head" << endl;
                testing(playCard);
            }

            // cout << "actual top card: " << playCard << endl;

            // get the player's reserve card whose turn it is
            string reserve = this->game->getPlayerReserve(turn);
            // cout << "Reserve: " << reserve << endl;
            bool reserveValid = false;
            // checks if the reserve is actually a valid card
            if (reserve != "") {
                reserveValid = true;
            }

            // prints the playing stage of every player and the active player's card in hand, remaining cards to play and the reserve
            this->print->printPlayerPlay(this->game->beginIteratorPlayers(), this->game->endIteratorPlayers(), turn, headSize-1, reserveValid, playCard);

            int move;
            if (!this->game->playerIsComp(turn)) {
                cin >> move;
            } else {
                cout << endl;
                cout << "=== COMPUTER PLAYER ===" << endl;
                move = this->game->compMove(playCard);
                cout << "Computer Player " << turn << " move: #" << move << endl;
            }

            // checks if the move entered by the player is actually valid
            this->game->checkValidMove(move, turn);

            // PLAYCARD AND RESERVE
            // reserve call
            if (move == 0) {
                // executes only if number of heads is greater than 1
                if (this->game->getHeadSize() > 1) {
                    // puts the card in reserve if the reserve is empty other swaps it with reserve
                    if (this->game->getPlayerReserve(turn) == "") {
                        this->game->playerPutReserve(turn, playCard);
                        --headSize;
                    } else {
                        this->game->playerSwapReserve(turn, playCard);
                        // cout << playCard << " added to the top of player " << turn << endl;
                        this->game->addTopCard(turn, playCard);
                        // cout << "Reserve after swapping: " << this->game->getPlayer(turn)->get_reserve() << endl;
                        // cout << "Top card: " << this->game->getPlayer(turn)->drawPile.back() << endl;
                    }
                    continue;
                }
            }

            // convert playCard if joker
            if (playCard == "J") {
                this->game->jokerConvert(playCard, move);
            }
            
            // compare the previous and the current card
            int playCardInt = this->game->cardToInt(playCard);
            bool hasToCut = this->game->hasToCut(playCardInt);
            // cout << boolalpha << "Has to cut " << hasToCut << endl;
            
            int oldestHead = this->game->getOldestHead();
            if (hasToCut) {
                // cut off the oldest head
                if (move != oldestHead) {
                    cout << move << " is not the oldest head." << endl;
                    // cout << "Cutting out " << oldestHead << endl;
                }
                cout << "Cutting out heads #" << oldestHead << endl;
                this->game->playerAddToDiscardPile(turn, this->game->removeHeads(oldestHead));
                vector <string> temp;
                temp.push_back(playCard);
                this->game->playerAddToDiscardPile(turn, temp);
                for (int i = 1; i <= 2; ++i) {
                    string newHead = this->game->removeTopCard(turn);

                    if (test) {
                        cout << endl << endl;
                        cout << "--- TESTING MODE ---" << endl;
                        cout << endl;
                        cout << "Player " << turn << " New Heads" << endl;
                        testing(newHead);
                    }

                    if (newHead == "J") {
                        newHead = "2J";
                    }
                    this->game->addNewHead(newHead);
                }
            } else {
                // first check if headCardInt is greater than or equal to playCardInt
                this->game->checkPlayLessThanHeads(move, playCardInt);
                string headCard = this->game->searchHeads(move).back();
                int headCardInt = this->game->cardToInt(headCard);
                // if so then differentiate between both actions
                if (headCardInt == playCardInt) {
                    if (headCard.back() == playCard.back() && this->game->getPure()) {
                        cout << "== Pure House ==" << endl;
                        while (headSize > 0) {
                            // win check
                            if (this->game->playerWinCheck(turn)) {
                                this->print->playerWin(turn);
                                return;
                            }
                            this->game->attachToPreviousHead(move, this->game->removeTopCard(turn));
                            --headSize;
                        }
                    } else {
                        this->game->attachToPreviousHead(move, playCard);
                    }
                    break;
                } else if (playCardInt < headCardInt || headCardInt == 1 || playCardInt == 1) {
                    this->game->attachToPreviousHead(move, playCard);
                }
            }

            --headSize;
            
            // win check
            if (this->game->playerWinCheck(turn)) {
                this->print->playerWin(turn);
                return;
            }
        }

        // win check
        if (this->game->playerWinCheck(turn)) {
            this->print->playerWin(turn);
            return;
        }

        // puts the reserve if any on top of the draw pile of the player since the turn is over
        string reserve = this->game->getPlayerReserve(turn);
        if (reserve != "") {
            this->game->addTopCard(turn, reserve);
            this->game->playerSetReserveToEmpty(turn);
        }
        
        cout << endl;


        // ++a;
        // if (a >= 50) {
        //     break;
        // }

        char ans;
        if (!this->game->playerIsComp(turn)) {
            cout << "Does Player " << turn << " want to leave? The computer will take over for the player. (y/n)" << endl;
            cin >> ans;
            ans = toupper(ans);
            while (ans != 'Y' && ans != 'N') {
                cout << "Invalid choice" << endl;
                cin >> ans;
                ans = toupper(ans);
            }
            if (ans == 'Y') {
                this->game->playerCompOn(turn);
                cout << "Player " << turn << " left the game." << endl;
            }
        }
    }
}

void GameController::testing(string &card) {
    string value = "";
    string suit = "";
    while (true) {
        cout << "Card value?" << endl;
        cin >> value;
        if (this->game->validValue(value)) {
            break;
        }
    }
    if (value == "JOKER") {
        value = "J";
    } else {
        while (true) {
            cout << "Suit?" << endl;
            cin >> suit;
            if (this->game->validSuit(suit)) {
                break;
            }
        }
    }
    card = value + suit;
}
