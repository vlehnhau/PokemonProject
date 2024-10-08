#ifndef KLAUSUR_MONSTER_H
#define KLAUSUR_MONSTER_H

#include <string>

class Monster
{
private:
    std::string name = "FeuerEchse";
    int ap = 5;
    int lp = 20;
    int lp_now = 20;
    int special = 0;
    /* 0 -> no special
     * 1 -> man kann zu 100% Fliehen
     * 2 -> man zieht dem Gegner 2 AP ab (Minimum ist 1 ap)
     * 3 -> man klaut dem gegnerischen monster 2 LP und bekommt sie selbst
     * */

public:
    // Konstruktor Destruktor
    Monster() = default;
    Monster(std::string name, int ap, int lp, int special);
    ~Monster() = default;

    // Getter/Setter
    const std::string &getName() const;
    int getAp() const;
    int getLp() const;
    int getLpNow() const;
    void setAp(int ap);
    void setLp(int lp);
    void setLpNow(int lpNow);
    int getSpecial() const;
    void setSpecial(int special);
};

#endif // KLAUSUR_MONSTER_H
