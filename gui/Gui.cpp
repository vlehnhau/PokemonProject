#include "Gui.h"

void Gui::onRefresh() {
    this->printBoard();

    if(this->getPressedKey() == CURSOR_UP) {

    } else if(this->getPressedKey() == CURSOR_DOWN) {

    } else if(this->getPressedKey() == CURSOR_LEFT) {

    } else if(this->getPressedKey() == CURSOR_RIGHT){

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