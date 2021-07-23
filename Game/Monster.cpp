#include "Monster.h"

const std::string &Monster::getName() const {
    return name;
}

int Monster::getAp() const {
    return ap;
}

int Monster::getLp() const {
    return lp;
}

int Monster::getLpNow() const {
    return lp_now;
}

void Monster::setAp(int ap) {
    Monster::ap = ap;
}

void Monster::setLp(int lp) {
    Monster::lp = lp;
}

void Monster::setLpNow(int lpNow) {
    lp_now = lpNow;
}

//Hier wird ein Monster erstellt welches von dem anfangsmonster abweicht und alle werte werden gesetzt
Monster::Monster(std::string name, int ap, int lp, int special) {
    this->name = name;
    this->ap = ap;
    this->lp = lp;
    this->lp_now = lp;
    this->special = special;
}

int Monster::getSpecial() const {
    return special;
}

void Monster::setSpecial(int special) {
    Monster::special = special;
}
