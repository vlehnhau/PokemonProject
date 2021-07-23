#include "Game.h"

//Zufallszahl
int rdmInt(int min, int max) {
    std::random_device rdmDevice;
    std::mt19937 randomizer(rdmDevice());

    std::uniform_int_distribution<int> dist(min, max);

    return dist(randomizer);
}

//konstruktor
Game::Game(int lvl) {
    //die einzulesene map
    std::fstream input;
    if(lvl == 1){
        input = std::fstream("map_basic.txt");
    } else if(lvl == 2){
        input = std::fstream("map_advanced.txt");
    } else if(lvl == 3) {
        input = std::fstream("map_test.txt");
    }

    std::string line;

    for (int i = 0; i < 30; ++i) {
        std::vector<char> vec;
        field.push_back(vec);
        for (int j = 0; j < 80; ++j) {
            field[i].push_back(' ');
        }
    }

    //die ganze map wird in ein char vector gepackt
    int i = 0;
    while (std::getline(input, line)) {
        for (int j = 0; j < line.size(); ++j) {
            field[i][j] = line[j];
        }
        i++;
    }

    //Der Spiel wird identifiziert und vom Board entfert
    //sein Standort wird im Spielerobjekt gespeichert
    int y;
    int x;
    for (int j = 0; j < field.size(); ++j) {
        for (int k = 0; k < field[j].size(); ++k) {
            if (field[j][k] == '0') {
                y = j;
                x = k;
                field[j][k] = ' ';
            }
        }
    }
    this->p = new Player(x, y);
}

const std::vector<std::vector<char>> &Game::getField() const {
    return field;
}

//Diese Methode bewegt den Spieler und wird aufgerufen wenn die entsprechenden Tasten gedrückt werden
void Game::movePlayer(const std::string &moveTo) {
    int x = this->getP()->getLocationX(); //allte Location wird abgespeichert
    int y = this->getP()->getLocationY(); //allte Location wird abgespeichert
    if (moveTo == "up") {
        if (checkFree(this->p->getLocationX(), this->p->getLocationY() -
                                               1)) {    //Hier wird überprüft ob der Spieler das gewünschte Feld betreten kann
            this->p->setLocationY(
                    this->p->getLocationY() - 1);                //Es wird der neue Standpunkt von dem Spieler gesetzt
            healingStartet = false;                                                     //Der Healing fortschrit wird zurück gesetzt sobald der Spieler sich bewegt
        }
    } else if (moveTo == "down") {
        if (checkFree(this->p->getLocationX(), this->p->getLocationY() + 1)) {
            this->p->setLocationY(this->p->getLocationY() + 1);
            healingStartet = false;
        }
    } else if (moveTo == "left") {
        if (checkFree(this->p->getLocationX() - 1, this->p->getLocationY())) {
            this->p->setLocationX(this->p->getLocationX() - 1);
            healingStartet = false;
        }
    } else if (moveTo == "right") {
        if (checkFree(this->p->getLocationX() + 1, this->p->getLocationY())) {
            this->p->setLocationX(this->p->getLocationX() + 1);
            healingStartet = false;
        }
    }

    if (field[this->p->getLocationY()][this->p->getLocationX()] ==
        'T') {           //Wenn der Spieler auf einen Gegner trifft, wird die kampfmethode aufgerufen
        this->fight();
    }

    if (field[this->p->getLocationY()][this->p->getLocationX()] ==
        'E') {           //Wenn der Spieler ins Ziel geht, wird die win Variable auf ture gesetzt, sodass sich die anzeige ändern kann
        this->win = true;
        this->score = score + 50;
    }

    if (field[this->p->getLocationY()][this->p->getLocationX()] ==
        'P') {           //Wenn der Spieler auf ein Heilfeld trifft, wird die heilmethode aufgerufen
        this->heal();
    }

    if (field[this->p->getLocationY()][this->p->getLocationX()] ==
        '*') {           //Wenn der Spieler auf ein Bonusfeld;
        this->score = score + 20;
        field[this->p->getLocationY()][this->p->getLocationX()] = ' ';
    }

    if (field[this->p->getLocationY()][this->p->getLocationX()] ==                          //Wenn der Spieler auf ein Waldfeld trifft
        'G' && (this->p->getLocationY() != y || this->p->getLocationX() != x)) {           //Es wird überprüft ob der Spieler sich auch wirklich bewegt hat
        int rdmNumber = rdmInt(1,
                               5);                                      //Wird eine Zufallszahl zwischen 1 und 5 ausgewählt (20%)
        if (rdmNumber == 5) {
            rdmNumber = rdmInt(1, 5);
            this->monsterFound = true;                                              //Wird die monster fangen Phase eingeleitet
            if (rdmNumber == 1) {
                this->newMonster = new Monster("SuperTaube", 3,10);      //und eine neues Monster erzeugt und in der dafür vorgesehenen variable abgespeichert
            } else if (rdmNumber == 2) {
                this->newMonster = new Monster("Fisch", 1,1);
            } else if (rdmNumber == 3) {
                this->newMonster = new Monster("OverPower", 50,50);
            } else if (rdmNumber == 4) {
                this->newMonster = new Monster("Tanki", 3,50);
            } else if (rdmNumber == 5) {
                this->newMonster = new Monster("SuperStark", 10,5);
            }
        }
    }
}

bool Game::checkFree(int x, int y) { //Hier wird überprüft ob das feld betretbar ist
    if (0 <= x && 79 >= x && 0 <= y && 29 >= y) {   //Das Feld darf nicht außerhalb von dem Spielfeld sein
        if (this->field[y][x] == '#') { //Wenn das Feld eine Bariere ist wird false zurückgegeben ansonsten true
            return false;
        } else {
            return true;
        }
    }
    return false;
}

Player *Game::getP() const {
    return p;
}

//Die Kampfmethode
void Game::fight() {
    int rdmNumber = rdmInt(1, 3); //Es wird eine Zufallszahl bestimmt um zu entscheiden welches monster der Gegner hat
    if (rdmNumber == 1) {
        this->enemyMonster = new Monster("Donnerratte", 5, 16);
    } else if (rdmNumber == 2) {
        this->enemyMonster = new Monster("Baumbaum", 5, 7);
    } else if (rdmNumber == 3) {
        this->enemyMonster = new Monster("Wasserkroete", 3, 10);
    }
    //Das entsprechende Monster wurde erstellt und in der entsprechenden Variable abgespeichert

    this->field[this->getP()->getLocationY()][this->getP()->getLocationX()] = ' '; //Der Gegner wird entfert da er nach dem Kapf nicht mehr auf dem Feld sein wird
    this->fighting = 1; //Die erste Kampfphase wird eingeleitet
}

//Hier wird überpfrüft ob der Spieler verloren hat oder ein monster von ihm gestorben ist
void Game::deadOrLose() {
    if (this->p->getM()->getLpNow() <=
        0) { //Er kann nur verloren haben oder sein monster wechseln müssen wenn sein hauptmonster unter oder genau 0Lp hat
        this->p->getAllMonsters()->erase(this->p->getAllMonsters()->begin() +
                                         this->getP()->getIndexOfMonster()); //Das Tote hauptmonster wird entfernt
        if (this->p->getAllMonsters()->size() == 0) { //Wenn kein Monster mehr vorhanden ist -> hat der Spieler verloren
            this->lose = true;
            this->score = score - 50;
            if(this->score < 0){
                this->score = 0;
            }
        } else {
            this->fighting = 3; //Es wird die Phase eingeleitet in welcher der Spieler in neues Monster auswählen muss
            this->score = score - 5;
        }
    }
}

bool Game::isLose() const {
    return lose;
}

bool Game::isWin() const {
    return win;
}

//Hier werden all Monster geheilt
void Game::heal() {
    for (auto &i : *this->p->getAllMonsters()) {   //Jedes Monster des Spielers wird durchgegangen und sein Lp auf den maximalwert gesetzt
        i.setLpNow(i.getLp());
    }
}

//Hier wird der Maximalwert für die Lp bestimmt
void Game::newMaxHealth() {
    //Wenn der Spieler auf einem Y Feld ist wird diese methode immerwieder aufgerufen
    if (healingStartet) { //Wenn das healing bereitsgestartet wurde wird überprüft ob seid dem start schon 5 sekunden vergangen sind wenn ja werden die maximalen lp um 5 erhöt und das Feld entfernt
        if (int(std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now() - healingStart).count()) > 5) {
            p->getM()->setLp(p->getM()->getLp() + 5);
            this->field[this->p->getLocationY()][this->p->getLocationX()] = ' ';
        }
    } else { //Wenn diese Methode das erstemal aufgerufen wird, wird die start zeit abgespeichert und sich gemerkt dass gestartet wurde
        healingStartet = true;
        healingStart = std::chrono::system_clock::now();
    }
}

bool Game::isMonsterFound() const {
    return monsterFound;
}

Monster *Game::getNewMonster() {
    return newMonster;
}

void Game::setMonsterFound(bool monsterFound) {
    Game::monsterFound = monsterFound;
}

//Hier wird ein neues Monster zu den Spielermonstern hinzugefügt
void Game::addMonster() {
    this->p->getAllMonsters()->push_back(*newMonster); //das Gefundene Monster wird hinzugefügt
    this->p->setM(&(*this->p->getAllMonsters())[this->p->getIndexOfMonster()]); //Das vorherig aktive monster, wird zum aktiven monster
    this->score = score + 5;
}

//Hier wird ein neues Monster ausgefählt -> der übergabe werde ist die Stelle im vector an welchem sich dieses befindet
void Game::selectNewMonster(int index) {
    if (this->p->getAllMonsters()->size() > index) { //der index wird nochmal überprüft
        if (this->fighting !=
            0) {                     //Es wird überprüft ob man sich gerade im Kampf befindet, um zu schauen ob man die Kampfphase danach wieder ändern müss
            if (enemyMonster->getLpNow() == 0) {
                this->fighting = 4;                  //Das monster ist zwar tot aber der Spieler hat noch ein anderes und danach trd. gewonnen weil der gegner im selben zug gestorben ist
                this->score = score + 20;
            } else {
                this->fighting = 2;                  //Der Kampf geht normal weiter
            }
        }
        this->p->setIndexOfMonster(
                index);           //Der Index des neuen aktive Monsters wird in der entsprechenden Variable abgespeichert
        this->p->setM(&(*this->p->getAllMonsters())[index]); //Das entsprechende monster wird zum aktiven monster
    }
}

int Game::getFighting() const {
    return fighting;
}

void Game::setFighting(int fighting) {
    Game::fighting = fighting;
}

Monster *Game::getEnemyMonster() const {
    return enemyMonster;
}

//Es wird angegriffen
void Game::attack() {
    enemyMonster->setLpNow(
            enemyMonster->getLpNow() - p->getM()->getAp()); //Das leben von dem gegnerischen monster wird runter gesetzt
    p->getM()->setLpNow(p->getM()->getLpNow() -
                        enemyMonster->getAp()); //Das leben des eigenen Monsterswird entsprechend runter gesetzt
    if (enemyMonster->getLpNow() <= 0) {  //Es wird nachgeschaut ob das gegnerische monster tot ist
        enemyMonster->setLpNow(
                0);  //damit die anzeige stimmt müssen die lp auf 0 gesetzt werden da sie sonst evtl. negativ wären
        p->getM()->setAp(p->getM()->getAp() + 1); //Die Ap des aktiven monsters des Spielers werden um 1 angehoben
        this->fighting = 4; //Die letzte Phase des Kampfes wird eingeleitet
        this->score = score + 20;
    }
    deadOrLose(); //Es wird nachgeschaut ob der Spieler dies Runde überlebt hat
}

bool Game::isFightHealingUsed() const {
    return fightHealingUsed;
}

void Game::setFightHealingUsed(bool fightHealingUsed) {
    Game::fightHealingUsed = fightHealingUsed;
}

//Das heilen eines Monsters im Kampf
void Game::fightHealing() {
    this->fightHealingUsed = true; //Das healing wurde bnutzt und kann nicht nochmal verwendet werden
    this->p->getM()->setLpNow(
            this->p->getM()->getLpNow() + (this->p->getM()->getLp() / 2)); //Die Lp werden wieder angehoben
    if (this->p->getM()->getLpNow() > this->p->getM()->getLp()) {
        this->p->getM()->setLpNow(this->p->getM()->getLp());
    }
    p->getM()->setLpNow(p->getM()->getLpNow() - enemyMonster->getAp()); //Der Gegner kann in diesem Zug trd. angreifen
    deadOrLose(); //hat der Spieler diese Runde überlebt
}

//Das fliehen aus einem Kampf
void Game::run() {
    int rdmNumber = rdmInt(1,
                           10); //Eine Zufallszahl zwischen 1-10 und die zahl muss kleiner als oder gleich 8 sein (80% warscheinlichkeit)
    if (rdmNumber <= 8) {
        this->setFighting(0);   //Die kampfphase ist beendet
        this->setFightHealingUsed(false);
        delete this->enemyMonster;
        this->enemyMonster = nullptr;
    } else {
        p->getM()->setLpNow(
                p->getM()->getLpNow() - enemyMonster->getAp()); //Der Gegner kann in diesem Zug trd. angreifen
        deadOrLose(); //hat der Spieler diese Runde überlebt
        this->setFighting(2); //Es geht weiter
    }
}

//Diese Methode gibt dem Monster 2 weiter angriffspunkte aber bekommt 5 maxLP abgezogen
void Game::train() {
    this->p->getM()->setLp(this->p->getM()->getLp() - 5);
    this->p->getM()->setAp(this->p->getM()->getAp() + 2);

    if(this->p->getM()->getLp() < this->p->getM()->getLpNow()){
        this->p->getM()->setLpNow(this->p->getM()->getLp());
    }

    p->getM()->setLpNow(p->getM()->getLpNow() - enemyMonster->getAp()); //Der Gegner greift an
    this->deadOrLose();
}

int Game::getScore() const {
    return score;
}

void Game::setScore(int score) {
    score = score;
}

void Game::setNewMonster(Monster *newMonster) {
    Game::newMonster = newMonster;
}

void Game::setEnemyMonster(Monster *enemyMonster) {
    Game::enemyMonster = enemyMonster;
}
