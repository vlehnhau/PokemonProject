#include "Player.h"

// Es wird ein neuer Spieler erzeugt und seine Position wird abgespeichert
Player::Player(int x, int y)
{
    this->locationX = x;
    this->locationY = y;

    // Das Startmonster des Spielers wird erzeugt und als aktives Monster gesetzt
    this->monsters.emplace_back();
    this->m = &monsters[0];
}

int Player::getLocationX() const
{
    return locationX;
}

int Player::getLocationY() const
{
    return locationY;
}

void Player::setLocationX(int locationX)
{
    Player::locationX = locationX;
}

void Player::setLocationY(int locationY)
{
    Player::locationY = locationY;
}

Monster *Player::getM() const
{
    return m;
}

void Player::setM(Monster *m)
{
    Player::m = m;
}

std::vector<Monster> *Player::getAllMonsters()
{
    return &monsters;
}

int Player::getIndexOfMonster() const
{
    return indexOfMonster;
}

void Player::setIndexOfMonster(int indexOfMonster)
{
    Player::indexOfMonster = indexOfMonster;
}
