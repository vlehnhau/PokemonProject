#include <random>
#include "Game.h"

int rdmInt(int min, int max) {
    static std::random_device rdmDevice;
    static std::mt19937 randomizer(rdmDevice());

    std::uniform_int_distribution<int> dist(min, max);

    int rdmInt = dist(randomizer);
    return rdmInt;
}

Game::Game() {
    std::fstream input("../map_advanced.txt");
    std::string line;

    for (int i = 0; i < 30; ++i) {
        std::vector<char> vec;
        field.push_back(vec);
        for (int j = 0; j < 80; ++j) {
            field[i].push_back(' ');
        }
    }

    int i = 0;
    while (std::getline(input, line)) {
        for (int j = 0; j < line.size(); ++j) {
            field[i][j] = line[j];
        }
        i++;
    }

    int y;
    int x;
    for (int j = 0; j < field.size(); ++j) {
        for (int k = 0; k < field[j].size(); ++k) {
            if (field[j][k] == '0') {
                y = j;
                x = k;
                field[j][k] = ' ';
            }
        }
    }
    this->p = new Player(x, y);
}

const std::vector<std::vector<char>> &Game::getField() const {
    return field;
}

void Game::movePlayer(std::string moveTo) {
    if (moveTo == "up") {
        if (checkFree(this->p->getLocationX(), this->p->getLocationY() - 1)) {
            this->p->setLocationY(this->p->getLocationY() - 1);
            healingStartet = false;
        }
    } else if (moveTo == "down") {
        if (checkFree(this->p->getLocationX(), this->p->getLocationY() + 1)) {
            this->p->setLocationY(this->p->getLocationY() + 1);
            healingStartet = false;
        }
    } else if (moveTo == "left") {
        if (checkFree(this->p->getLocationX() - 1, this->p->getLocationY())) {
            this->p->setLocationX(this->p->getLocationX() - 1);
            healingStartet = false;
        }
    } else if (moveTo == "right") {
        if (checkFree(this->p->getLocationX() + 1, this->p->getLocationY())) {
            this->p->setLocationX(this->p->getLocationX() + 1);
            healingStartet = false;
        }
    }

    if (field[this->p->getLocationY()][this->p->getLocationX()] == 'T') {
        this->fight();
    }

    if (field[this->p->getLocationY()][this->p->getLocationX()] == 'E') {
        this->win = true;
    }

    if (field[this->p->getLocationY()][this->p->getLocationX()] == 'P') {
        this->heal();
    }

    if (field[this->p->getLocationY()][this->p->getLocationX()] == 'G') {
        int rdmNumber = rdmInt(1,5);
        if (rdmNumber == 5) {
            this->monsterFound = true;
            this->newMonster = new Monster("SuperTaube", 3, 10);
        }
    }
}

bool Game::checkFree(int x, int y) {
    if (0 <= x && 79 >= x && 0 <= y && 29 >= y) {
        if (this->field[y][x] == '#') {
            return false;
        } else {
            return true;
        }
    }
    return false;
}

Player *Game::getP() const {
    return p;
}

void Game::fight() {
//    this->p->getM()->setLpNow(this->p->getM()->getLpNow()-5);
    int rdmNumber = rdmInt(1, 3);
    if (rdmNumber == 1) {
        this->enemyMonster = new Monster("Donnerratte", 5, 16);
    } else if (rdmNumber == 2) {
        this->enemyMonster = new Monster("Baumbaum", 5, 7);
    } else if (rdmNumber == 3) {
        this->enemyMonster = new Monster("Wasserkroete", 3, 10);
    }
    this->field[this->getP()->getLocationY()][this->getP()->getLocationX()] = ' ';
    this->fighting = 1;
}

void Game::deadOrLose() {
    if (this->p->getM()->getLpNow() <= 0) {
        this->p->getAllMonsters()->erase(this->p->getAllMonsters()->begin() + this->getP()->getIndexOfMonster());
        if (this->p->getAllMonsters()->size() == 0) {
            this->lose = true;
        } else {
            this->fighting = 3;
        }
    }
}

bool Game::isLose() const {
    return lose;
}

bool Game::isWin() const {
    return win;
}

void Game::heal() {
    for (int i = 0; i < this->p->getAllMonsters()->size(); ++i) {
        (*this->p->getAllMonsters())[i].setLpNow((*this->p->getAllMonsters())[i].getLp());
    }
}

void Game::newMaxHealth() {
    if (healingStartet) {
        if (int(std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::system_clock::now() - healingStart).count()) > 5000000) {
            p->getM()->setLp(p->getM()->getLp() + 5);
            this->field[this->p->getLocationY()][this->p->getLocationX()] = ' ';
        }
    } else {
        healingStartet = true;
        healingStart = std::chrono::system_clock::now();
    }
}

bool Game::isMonsterFound() const {
    return monsterFound;
}

const Monster &Game::getNewMonster() const {
    return *newMonster;
}

void Game::setMonsterFound(bool monsterFound) {
    Game::monsterFound = monsterFound;
}

void Game::addMonster() {
    this->p->getAllMonsters()->push_back(*newMonster);
    this->p->setM(&(*this->p->getAllMonsters())[this->p->getIndexOfMonster()]);
}

void Game::selectNewMonster(int index) {
    if (this->p->getAllMonsters()->size() > index) {
        if(this->fighting != 0){
            if(enemyMonster->getLpNow() == 0){
                this->fighting = 4;
            } else {
                this->fighting = 2;
            }
        }
        this->p->setIndexOfMonster(index);
        this->p->setM(&(*this->p->getAllMonsters())[index]);
    }
}

int Game::getFighting() const {
    return fighting;
}

void Game::setFighting(int fighting) {
    Game::fighting = fighting;
}

Monster *Game::getEnemyMonster() const {
    return enemyMonster;
}

void Game::setEnemyMonster(Monster *enemyMonster) {
    Game::enemyMonster = enemyMonster;
}

void Game::attack() {
    enemyMonster->setLpNow(enemyMonster->getLpNow() - p->getM()->getAp());
    p->getM()->setLpNow(p->getM()->getLpNow() - enemyMonster->getAp());
    if (enemyMonster->getLpNow() <= 0) {
        enemyMonster->setLpNow(0);
        p->getM()->setAp(p->getM()->getAp() + 1);
        this->fighting = 4;
    }
    deadOrLose();
}

bool Game::isFightHealingUsed() const {
    return fightHealingUsed;
}

void Game::setFightHealingUsed(bool fightHealingUsed) {
    Game::fightHealingUsed = fightHealingUsed;
}

void Game::fightHealing() {
    this->fightHealingUsed = true;
    this->p->getM()->setLpNow(this->p->getM()->getLpNow() + (this->p->getM()->getLp()/2));
    if(this->p->getM()->getLpNow() > this->p->getM()->getLp()) {
        this->p->getM()->setLpNow(this->p->getM()->getLp());
    }
    p->getM()->setLpNow(p->getM()->getLpNow() - enemyMonster->getAp());
    deadOrLose();
}

void Game::run() {
    int rdmNumber = rdmInt(1,10);
    if(rdmNumber < 8) {
        this->setFighting(0);
        this->setFightHealingUsed(false);
    } else {
        p->getM()->setLpNow(p->getM()->getLpNow() - enemyMonster->getAp());
        deadOrLose();
        this->setFighting(2);
    }
}
