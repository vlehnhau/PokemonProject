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

    int score = 0;

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
    Game(int lvl);
    ~Game() = default;

    void attack();
    void movePlayer(const std::string& moveTo);
    void newMaxHealth();
    void addMonster();
    void selectNewMonster(int index);
    void fightHealing();
    void run();
    void train();
    void specialAttack(int index);

    //Getter/Setter
    const std::vector<std::vector<char>> &getField() const;
    Player *getP() const;
    bool isLose() const;
    bool isWin() const;
    bool isMonsterFound() const;
    void setMonsterFound(bool monsterFound);
    Monster *getNewMonster();
    int getFighting() const;
    void setFighting(int fighting);
    Monster *getEnemyMonster() const;
    bool isFightHealingUsed() const;
    void setFightHealingUsed(bool fightHealingUsed);
    int getScore() const;
    void setScore(int score);
    void setNewMonster(Monster *newMonster);
    void setEnemyMonster(Monster *enemyMonster);
};

#endif //KLAUSUR_GAME_H
