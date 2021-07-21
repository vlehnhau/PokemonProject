#include "Gui.h"

void Gui::onRefresh() {
    this->clear();
    this->printBoard();
    this->printPlayer();
    this->printInstructions();
    this->printMonster();

    if(!this->game->isMonsterFound() && !this->game->isNeedNewMonster()) {
        if (this->getPressedKey() == CURSOR_UP) {
            this->game->movePlayer("up");
        } else if (this->getPressedKey() == CURSOR_DOWN) {
            this->game->movePlayer("down");
        } else if (this->getPressedKey() == CURSOR_LEFT) {
            this->game->movePlayer("left");
        } else if (this->getPressedKey() == CURSOR_RIGHT) {
            this->game->movePlayer("right");
        } else if (this->getPressedKey() == '1'){
            this->game->selectNewMonster(0);
        } else if (this->getPressedKey() == '2'){
            this->game->selectNewMonster(1);
        } else if (this->getPressedKey() == '3'){
            this->game->selectNewMonster(2);
        } else if (this->getPressedKey() == '4'){
            this->game->selectNewMonster(3);
        } else if (this->getPressedKey() == '5'){
            this->game->selectNewMonster(4);
        } else if (this->getPressedKey() == '6'){
            this->game->selectNewMonster(5);
        }
    } else if(!this->game->isNeedNewMonster()){
        if (this->getPressedKey() == '1' && this->game->getP()->getAllMonsters()->size() < 6) {
            this->game->addMonster();
            this->game->setMonsterFound(false);
        } else if (this->getPressedKey() == '2') {
            this->game->setMonsterFound(false);
        }
    } else {
        if (this->getPressedKey() == '1'){
            this->game->selectNewMonster(0);
        } else if (this->getPressedKey() == '2'){
            this->game->selectNewMonster(1);
        } else if (this->getPressedKey() == '3'){
            this->game->selectNewMonster(2);
        } else if (this->getPressedKey() == '4'){
            this->game->selectNewMonster(3);
        } else if (this->getPressedKey() == '5'){
            this->game->selectNewMonster(4);
        } else if (this->getPressedKey() == '6'){
            this->game->selectNewMonster(5);
        }
    }

    if (this->game->getField()[this->game->getP()->getLocationY()][this->game->getP()->getLocationX()] == 'Y') {
        this->game->newMaxHealth();
    }

    if(this->game->isLose()){
        this->clear();
        this->writeString(0,10, "Sie haben verloren!");
    } else if(this->game->isWin()) {
        this->clear();
        this->writeString(0,10, "Sie haben gewonnen!");
    }

    if(this->game->isMonsterFound()){
        if (this->game->getP()->getAllMonsters()->size() < 6) {
            this->clear();
            this->writeString(0,10, "Ein Monster (" + this->game->getNewMonster().getName() + ") erscheint. Was moechtest du tun?");
            this->writeString(0,11, "1: Fangen | 2: Flucht");
        } else {
            this->clear();
            this->writeString(0,10, "Ein Monster (" + this->game->getNewMonster().getName() + ") erscheint, aber du hast leider keinen Platz mehr");
            this->writeString(0,11, "1: ------ | 2: Flucht");
        }
    }

    if(this->game->isNeedNewMonster()) {
      this->clear();
      this->writeString(0,10, "Dein Monster ist gestortben und du musst ein neues auswaehlen");
      this->writeString(0,11, "Druecke eine Taste zwischen 1 - " + std::to_string(this->game->getP()->getAllMonsters()->size()));
      this->printMonster();
    }
}

Gui::Gui(): ConsoleWindow() {
    this->game = new Game();
}

void Gui::printBoard() {
    for (int i = 0; i < this->game->getField().size(); ++i) {
        for (int j = 0; j < this->game->getField()[i].size(); ++j) {
            setCharacter(j, i, this->game->getField()[i][j]);
        }
    }
}

void Gui::printPlayer() {
    this->setCharacter(this->game->getP()->getLocationX(), this->game->getP()->getLocationY(), '0');
}

void Gui::printInstructions() {
    this->writeString(0,30, "Steuerung: Pfeiltasten / Tasten 1 - 6 zum Waehlen das aktiven Monsters");
}

void Gui::printMonster() {
    std::string name = (*this->game->getP()->getM()).getName();
    this->writeString(0,32, "Aktuelles Monster: " + this->game->getP()->getM()->getName() + " " + std::to_string(this->game->getP()->getM()->getLpNow()) + " / " + std::to_string(this->game->getP()->getM()->getLp()) + " LP  Angriff: " + std::to_string(this->game->getP()->getM()->getAp()));


    for (int i = 0; i < this->game->getP()->getAllMonsters()->size(); ++i) {
        this->writeString(0,34 + i, std::to_string(i+1) + "." + (*this->game->getP()->getAllMonsters())[i].getName() + " " + std::to_string((*this->game->getP()->getAllMonsters())[i].getLpNow()) + " / " + std::to_string((*this->game->getP()->getAllMonsters())[i].getLp()) + " LP  Angriff: " + std::to_string((*this->game->getP()->getAllMonsters())[i].getAp()));
    }
}

