#ifndef KLAUSUR_GAME_H
#define KLAUSUR_GAME_H

#include <vector>
#include "Player.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>

int rdmInt(int min, int max);

class Game {
private:
    std::vector<std::vector<char>> field;
    Player *p;
    bool lose = false;
    bool win = false;
    bool healingStartet = false;
    bool monsterFound = false;
    bool fightHealingUsed = false;
    int fighting = 0;
    /* 0 -> not fiting
     * 1 -> start dialog
     * 2 -> all choices (atack/heal/run/change)
     * 3 -> monsterDead
     * 4 -> win
     * */

    Monster *newMonster;
    Monster *enemyMonster;

    std::chrono::system_clock::time_point healingStart;

    void fight();
    void heal();


public:
    void attack();
    Game();
    void movePlayer(std::string moveTo);
    bool checkFree(int x, int y);
    void newMaxHealth();
    void addMonster();
    void selectNewMonster(int index);
    void deadOrLose();
    void fightHealing();
    void run();

    //Getter/Setter
    const std::vector<std::vector<char>> &getField() const;
    Player *getP() const;
    bool isLose() const;
    bool isWin() const;
    bool isMonsterFound() const;
    void setMonsterFound(bool monsterFound);
    const Monster &getNewMonster() const;
    int getFighting() const;
    void setFighting(int fighting);
    Monster *getEnemyMonster() const;
    void setEnemyMonster(Monster *enemyMonster);
    bool isFightHealingUsed() const;
    void setFightHealingUsed(bool fightHealingUsed);
};

#endif //KLAUSUR_GAME_H
