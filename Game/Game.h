#ifndef KLAUSUR_GAME_H
#define KLAUSUR_GAME_H

#include <vector>
#include "Player.h"
#include <fstream>
#include <iostream>

class Game {
private:
    std::vector<std::vector<char>> field;
    Player *p;
    bool lose = false;
    bool win = false;

    void fight();

public:
    Game();
    void movePlayer(std::string moveTo);
    bool checkFree(int x, int y);

    //Getter/Setter
    const std::vector<std::vector<char>> &getField() const;
    Player *getP() const;
    bool isLose() const;
    bool isWin() const;
};


#endif //KLAUSUR_GAME_H
