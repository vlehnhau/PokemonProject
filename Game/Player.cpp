#include "Player.h"

Player::Player(int x, int y) {
    this->locationX = x;
    this->locationY = y;

    this->m = new Monster();
}

int Player::getLocationX() const {
    return locationX;
}

int Player::getLocationY() const {
    return locationY;
}

void Player::setLocationX(int locationX) {
    Player::locationX = locationX;
}

void Player::setLocationY(int locationY) {
    Player::locationY = locationY;
}

Monster *Player::getM() const {
    return m;
}

void Player::setM(Monster *m) {
    Player::m = m;
}
