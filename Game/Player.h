#ifndef KLAUSUR_PLAYER_H
#define KLAUSUR_PLAYER_H

#include "Monster.h"

class Player {
public:
    Player(int x, int y);

    //Getter/Setter
    int getLocationX() const;
    int getLocationY() const;
    Monster *getM() const;
    void setLocationX(int locationX);
    void setLocationY(int locationY);
    void setM(Monster *m);

private:
    int locationX;
    int locationY;

    Monster * m;
};


#endif //KLAUSUR_PLAYER_H
