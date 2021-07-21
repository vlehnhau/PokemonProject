#ifndef KLAUSUR_GAME_H
#define KLAUSUR_GAME_H

#include <vector>
#include "Player.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>

class Game {
private:
    std::vector<std::vector<char>> field;
    Player *p;
    bool lose = false;
    bool win = false;
    bool healingStartet = false;

    std::chrono::system_clock::time_point healingStart;

    void fight();
    void heal();

public:
    Game();
    void movePlayer(std::string moveTo);
    bool checkFree(int x, int y);
    void newMaxHealth();

    //Getter/Setter
    const std::vector<std::vector<char>> &getField() const;
    Player *getP() const;
    bool isLose() const;
    bool isWin() const;
};

#endif //KLAUSUR_GAME_H
