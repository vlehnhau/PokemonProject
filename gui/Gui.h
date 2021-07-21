#ifndef KLAUSUR_GUI_H
#define KLAUSUR_GUI_H

#include "../copyme/console-window-master/ConsoleWindow.h"
#include "../Game/Game.h"

class Gui: public ConsoleWindow{
protected:
    void onRefresh() override;

public:
    Gui();

private:
    Game *game;

    void printBoard();
};


#endif //KLAUSUR_GUI_H