#ifndef KLAUSUR_GUI_H
#define KLAUSUR_GUI_H

#include "../console-window-master/ConsoleWindow.h"
#include "../Game/Game.h"
#include <iostream>

class Gui: public ConsoleWindow{
protected:
    //die funktion welche wiederholt aufgerufen wird
    void onRefresh() override;

public:
    //konstruktor destruktor
    Gui();
    ~Gui() override = default;

private:
    //Die eigentliche Spiellogig
    Game *game;

    //Die runden Zeit (der Startpunkt)
    std::chrono::system_clock::time_point startRoundTime = std::chrono::system_clock::now();

    //alle Print funktionen
    void printBoard();
    void printPlayer();
    void printInstructions();
    void printMonster();
    void printFight(std::string msg);
    void printFight(std::string msg, std::string msg2);
};


#endif //KLAUSUR_GUI_H