#include "Game.h"

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
    while(std::getline(input, line)) {
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
        if (checkFree(this->p->getLocationX(), this->p->getLocationY()-1)) {
            this->p->setLocationY(this->p->getLocationY()-1);
            healingStartet = false;
        }
    } else if (moveTo == "down") {
        if (checkFree(this->p->getLocationX(), this->p->getLocationY()+1)) {
            this->p->setLocationY(this->p->getLocationY()+1);
            healingStartet = false;
        }
    } else if (moveTo == "left") {
        if (checkFree(this->p->getLocationX()-1, this->p->getLocationY())) {
            this->p->setLocationX(this->p->getLocationX()-1);
            healingStartet = false;
        }
    } else if (moveTo == "right") {
        if (checkFree(this->p->getLocationX()+1, this->p->getLocationY())) {
            this->p->setLocationX(this->p->getLocationX()+1);
            healingStartet = false;
        }
    }

    if (field[this->p->getLocationY()][this->p->getLocationX()] == 'T'){
        this->fight();
    }

    if (field[this->p->getLocationY()][this->p->getLocationX()] == 'E'){
        this->win = true;
    }

    if (field[this->p->getLocationY()][this->p->getLocationX()] == 'P'){
        this->heal();
    }
}

bool Game::checkFree(int x, int y) {
    if (0 <= x && 79 >= x && 0 <= y && 29 >= y){
        if (this->field[y][x] == '#'){
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
    this->p->getM()->setLpNow(this->p->getM()->getLpNow()-5);
    std::cout << this->p->getM()->getLpNow();

    this->field[this->getP()->getLocationY()][this->getP()->getLocationX()] = ' ';

    if (this->p->getM()->getLpNow() <= 0) {
        this->lose = true;
    }
}

bool Game::isLose() const {
    return lose;
}

bool Game::isWin() const {
    return win;
}

void Game::heal() {
    this->p->getM()->setLpNow(this->p->getM()->getLp());
}

void Game::newMaxHealth() {
        if(healingStartet){
            if (int(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - healingStart).count()) > 5000000){
                std::cout << "it worked" << std::endl;
                p->getM()->setLp(p->getM()->getLp() + 5);
                this->field[this->p->getLocationY()][this->p->getLocationX()] = ' ';
            }
        } else {
            healingStartet = true;
            healingStart = std::chrono::system_clock::now();
        }
}