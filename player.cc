#include "player.h"
using namespace std;

Player::Player() {}

Player::~Player() {}

void Player::removeTopFromDrawPile() {
    if (this->drawPile.size() == 0 && this->discardPile.size() == 0) {
        if (this->reserve != "") {
            this->drawPile.push_back(this->reserve);
            this->reserve = "";
        }
    } else if (this->drawPile.size() == 0) {
        // call discard to draw
        shuffle(this->discardPile.begin(), this->discardPile.end(), random_device());
        for (auto &c: this->discardPile) {
            this->drawPile.push_back(c);
        }
        this->discardPile.clear();
    }
    this->playCard = this->drawPile.back();
    // cout << this->drawPile.back() << " from romoveTopFromDrawPile function (back)" << endl;
    // cout << this->playCard << " from romoveTopFromDrawPile function" << endl;
    this->drawPile.pop_back();
}

void Player::setOn() {
    this->isComp = true;
}

void Player::setOff() {
    this->isComp = false;
}

bool Player::getIsComp() {
    return this->isComp;
}

string Player::getPlayCard() {
    // this->playCard = this->drawPile.back();
    return this->playCard;
}

string Player::getReserve() {
    return this->reserve;
}

void Player::setReserveToEmpty() {
    this->reserve = "";
}

void Player::init(vector<string> draw) {
    for (size_t i = 0; i < draw.size(); ++i) {
        this->drawPile.push_back(draw.at(i));
    }
    this->playCard = "";
    this->reserve = "";
}

void Player::setCard(std::string suite, std::string num, std::string &card) {
    card = num + suite;
}

int Player::getDiscardPileSize() {
    return this->discardPile.size();
}

int Player::getDrawPileSize() {
    return this->drawPile.size();
}

void Player::addToDiscardPile(std::vector<std::string> heads) {
    for (auto &c: heads) {
        this->discardPile.push_back(c);
    }
}

bool Player::winCheck() {
    if (this->drawPile.size() == 0 && this->discardPile.size() == 0 && this->reserve == "") {
        return true;
    }
    return false;
}

void Player::addTop(string card) {
    // cout << card << " addTop function" << endl;
    this->drawPile.push_back(card);
    // cout << this->drawPile.back() << " addTop function back" << endl;
}

void Player::swapReserve(string &playCard) {
    // cout << "swapReserve -> reserve:" << this->reserve << " playCard:" << playCard << endl;
    string temp = this->reserve;
    this->reserve = playCard;
    playCard = temp;
    // cout << "SWAP" << endl;
    // cout << "swapReserve -> reserve:" << this->reserve << " playCard:" << playCard << endl;
}

void Player::putReserve(string playCard) {
    // cout << "putReserve: " << playCard << endl;
    this->reserve = playCard;
}
