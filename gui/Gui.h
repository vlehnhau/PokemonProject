#ifndef KLAUSUR_GUI_H
#define KLAUSUR_GUI_H

#include "../copyme/console-window-master/ConsoleWindow.h"
#include "../Game/Game.h"
#include <iostream>

class Gui: public ConsoleWindow{
protected:
    void onRefresh() override;

public:
    Gui();

private:
    Game *game;

    void printBoard();
    void printPlayer();
    void printInstructions();
    void printMonster();
};


#endif //KLAUSUR_GUI_H