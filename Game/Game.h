#ifndef KLAUSUR_GAME_H
#define KLAUSUR_GAME_H

#include <vector>
#include "Player.h"
#include <fstream>

class Game {
private:
    std::vector<std::vector<char>> field;
    Player *p;

public:
    Game();

    //Getter/Setter
    const std::vector<std::vector<char>> &getField() const;

};


#endif //KLAUSUR_GAME_H
