#include "Gui.h"

void Gui::onRefresh() {
    this->printBoard();
    this->printPlayer();
    this->printInstructions();
    this->printMonster();

    if(this->getPressedKey() == CURSOR_UP) {
        this->game->movePlayer("up");
    } else if(this->getPressedKey() == CURSOR_DOWN) {
        this->game->movePlayer("down");
    } else if(this->getPressedKey() == CURSOR_LEFT) {
        this->game->movePlayer("left");
    } else if(this->getPressedKey() == CURSOR_RIGHT){
        this->game->movePlayer("right");
    }

    if(this->game->isLose()){
        this->clear();
        this->writeString(10,10, "Sie haben verloren!");
    } else if(this->game->isWin()) {
        this->clear();
        this->writeString(10,10, "Sie haben gewonnen!");
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
    this->writeString(0,30, "Steuerung: Pfeiltasten");
}

void Gui::printMonster() {
    this->writeString(0,31, this->game->getP()->getM()->getName() + " " + std::to_string(this->game->getP()->getM()->getLpNow()) + " / " + std::to_string(this->game->getP()->getM()->getLp()) + " LP  Angriff: " + std::to_string(this->game->getP()->getM()->getAp()));
}

