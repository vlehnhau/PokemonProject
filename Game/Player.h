#ifndef KLAUSUR_PLAYER_H
#define KLAUSUR_PLAYER_H

#include <vector>
#include "Monster.h"

class Player {
public:
    //konstruktor destruktor
    Player(int x, int y);
    ~Player() = default;

    //Getter/Setter
    int getLocationX() const;
    int getLocationY() const;
    Monster *getM() const;
    void setLocationX(int locationX);
    void setLocationY(int locationY);
    void setM(Monster *m);
    std::vector<Monster> *getAllMonsters();
    int getIndexOfMonster() const;
    void setIndexOfMonster(int indexOfMonster);

private:
    int locationX;
    int locationY;

    int indexOfMonster = 0;
    std::vector<Monster> monsters;
    Monster *m;
};


#endif //KLAUSUR_PLAYER_H
