//
// Created by Viktor Lehnhausen on 21.07.21.
//

#ifndef KLAUSUR_MONSTER_H
#define KLAUSUR_MONSTER_H

#include <string>

class Monster {
private:
    std::string name = "Feuerechse";
    int ap = 5;
    int lp = 20;
    int lp_now = 20;

public:
    Monster() = default;
    Monster(std::string name, int ap, int lp);

    //Getter/Setter
    const std::string &getName() const;
    int getAp() const;
    int getLp() const;
    int getLpNow() const;
    void setName(const std::string &name);
    void setAp(int ap);
    void setLp(int lp);
    void setLpNow(int lpNow);
};


#endif //KLAUSUR_MONSTER_H
