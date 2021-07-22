#ifndef KLAUSUR_GAME_H
#define KLAUSUR_GAME_H

#include <vector>
#include "Player.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>
#include <random>

int rdmInt(int min, int max);

class Game {
private:
    std::vector<std::vector<char>> field; //Das Spielfeld
    Player *p; //Der Spieler

    bool lose = false;
    bool win = false;

    bool healingStartet = false;
    bool monsterFound = false;
    bool fightHealingUsed = false;

    int fighting = 0;
    /* 0 -> not fiting
     * 1 -> start dialog
     * 2 -> all choices (atack/heal/run/change)
     * 3 -> monsterDead / chaching monster
     * 4 -> win
     * */

    Monster *newMonster{};
    Monster *enemyMonster{};

    std::chrono::system_clock::time_point healingStart;

    void fight();
    void heal();
    bool checkFree(int x, int y);
    void deadOrLose();

public:
    //konstruktor destruktor
    Game();
    ~Game() = default;

    void attack();
    void movePlayer(const std::string& moveTo);
    void newMaxHealth();
    void addMonster();
    void selectNewMonster(int index);
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
    bool isFightHealingUsed() const;
    void setFightHealingUsed(bool fightHealingUsed);
};

#endif //KLAUSUR_GAME_H
