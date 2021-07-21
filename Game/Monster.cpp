//
// Created by Viktor Lehnhausen on 21.07.21.
//

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

void Monster::setName(const std::string &name) {
    Monster::name = name;
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

Monster::Monster(std::string name, int ap, int lp) {
    this->name = name;
    this->ap = ap;
    this->lp = lp;
    this->lp_now = lp;
}
