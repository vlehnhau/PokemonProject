#include "Gui.h"

void Gui::onRefresh() { // Diese Methode ist dafür zuständig das board anzuziegen und die tasten anschläge zu erkennen
    if (int(std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::system_clock::now() - startRoundTime).count()) > 50000) { //Hier wird so lange gewartet bis der spieler sich wieder bewegen kann
        //Hier wird das Board aktualisiert
        this->clear();
        this->printBoard();
        this->printPlayer();
        this->printInstructions();
        this->printMonster();
        this->printScore();

        //Hier wird nachgeschaut in welcher Spielphase der Spieler sich befindet und dementsprechent die passenden tasten genutzt
        if (!this->game->isMonsterFound() && this->game->getFighting() == 0) {
            //normal
            if (this->getPressedKey() == CURSOR_UP) {
                this->game->movePlayer("up");
            } else if (this->getPressedKey() == CURSOR_DOWN) {
                this->game->movePlayer("down");
            } else if (this->getPressedKey() == CURSOR_LEFT) {
                this->game->movePlayer("left");
            } else if (this->getPressedKey() == CURSOR_RIGHT) {
                this->game->movePlayer("right");
            } else if (this->getPressedKey() == '1') {
                this->game->selectNewMonster(0);
            } else if (this->getPressedKey() == '2') {
                this->game->selectNewMonster(1);
            } else if (this->getPressedKey() == '3') {
                this->game->selectNewMonster(2);
            } else if (this->getPressedKey() == '4') {
                this->game->selectNewMonster(3);
            } else if (this->getPressedKey() == '5') {
                this->game->selectNewMonster(4);
            } else if (this->getPressedKey() == '6') {
                this->game->selectNewMonster(5);
            }
        } else if (this->game->getFighting() == 0) {
            //take the monster
            if (this->getPressedKey() == '1' && this->game->getP()->getAllMonsters()->size() < 6) {
                this->game->addMonster();
                this->game->setMonsterFound(false);
            } else if (this->getPressedKey() == '2') {
                this->game->setMonsterFound(false);
            }
        } else if (!this->game->isMonsterFound() && this->game->getFighting() != 0) {
            //fighting
            if (this->game->getFighting() == 1) {
                //dialog
                printFight("Gary moechte kaempfen!");
                if (this->getPressedKey() == 'a') {
                    this->game->setFighting(2);
                }
            } else if (this->game->getFighting() == 2) {
                //choices
                if (!this->game->isFightHealingUsed()) {
                    printFight("Was moechtest du tun?", "1: Angriff | 2: Heilen | 3: Flucht | 4: Trainiere Ihn | p: Monster wechseln");
                } else {
                    printFight("Was moechtest du tun?", "1: Angriff | 2: ------ | 3: Flucht | 4: Trainiere Ihn | p: Monster wechseln");
                }

                if (this->getPressedKey() == '1') {
                    this->game->attack();
                } else if (this->getPressedKey() == '2') {
                    if (!this->game->isFightHealingUsed()) {
                        this->game->fightHealing();
                    }
                } else if (this->getPressedKey() == '3') {
                    this->game->run();
                } else if (this->getPressedKey() == 'p') {
                    this->game->setFighting(3);
                } else if (this->getPressedKey() == '4') {
                    this->game->train();
                }
            } else if (this->game->getFighting() == 3) {
                //monsterDead / monster change
                if (this->getPressedKey() == '1') {
                    this->game->selectNewMonster(0);
                } else if (this->getPressedKey() == '2') {
                    this->game->selectNewMonster(1);
                } else if (this->getPressedKey() == '3') {
                    this->game->selectNewMonster(2);
                } else if (this->getPressedKey() == '4') {
                    this->game->selectNewMonster(3);
                } else if (this->getPressedKey() == '5') {
                    this->game->selectNewMonster(4);
                } else if (this->getPressedKey() == '6') {
                    this->game->selectNewMonster(5);
                }
            } else if (this->game->getFighting() == 4) {
                //win
                printFight("Du hast Gary besiegt");
                if (this->getPressedKey() == 'a') {
                    this->game->setFighting(0);
                    this->game->setFightHealingUsed(false);
                }
            }
        }

        //Das passiert wenn der Spieler ein Y Feld betritt -> dies passiert hier und nicht in der move methode da so immerwieder nachgeschaut werden kann wie lange er hier schon steht
        if (this->game->getField()[this->game->getP()->getLocationY()][this->game->getP()->getLocationX()] == 'Y') {
            this->game->newMaxHealth();
        }

        //Hier wird überprüft ob der spieler verloren oder gewonnen hat
        if (this->game->isLose()) {
            this->clear();
            this->writeString(0, 10, "Du hast verloren!");
            this->writeString(0,12, "Dein Score: " + std::to_string(this->game->getScore()));
        } else if (this->game->isWin()) {
            this->clear();
            this->writeString(0, 10, "Du hast gewonnen!");
            this->writeString(0,12, "Dein Score: " + std::to_string(this->game->getScore()));
        }

        //Hier ist die Anzeige, für den Fall dass ein wildes Monster gefunden wurde
        if (this->game->isMonsterFound()) {
            if (this->game->getP()->getAllMonsters()->size() < 6) {
                this->clear();
                this->writeString(0, 10, "Ein Monster (" + this->game->getNewMonster().getName() +
                                         ") erscheint. Was moechtest du tun?");
                this->writeString(0, 11, "1: Fangen | 2: Flucht");
            } else {
                this->clear();
                this->writeString(0, 10, "Ein Monster (" + this->game->getNewMonster().getName() +
                                         ") erscheint, aber du hast leider keinen Platz mehr");
                this->writeString(0, 11, "1: ------ | 2: Flucht");
            }
        }

        //Hier ist die Anzeige, für den Fall dass ein Monster im Kampf gestorben ist / dass monster gewechselt wird
        if (this->game->getFighting() == 3) {
            this->clear();
            if (this->game->getP()->getM()->getLpNow() == 0){
                this->writeString(0, 10, "Dein Monster ist gestortben und du musst ein neues auswaehlen!");
            } else {
                this->writeString(0, 10, "Waehle ein monster!");
            }

            this->writeString(0, 11, "Druecke eine Taste zwischen 1 - " +
                                     std::to_string(this->game->getP()->getAllMonsters()->size()));
            this->printMonster();
        }
        startRoundTime = std::chrono::system_clock::now();//Hier wird eine neue runden Zeit begonnen sodass oben passend gewartet werden kann
    }
}

//Constructor
Gui::Gui() : ConsoleWindow(nullptr, 100, 50) {  //Setzt die Fenstergröße
    this->game = new Game();
}

//das Board wird ausgegeben
void Gui::printBoard() {
    for (int i = 0; i < this->game->getField().size(); ++i) {
        for (int j = 0; j < this->game->getField()[i].size(); ++j) {
            if(this->game->getField()[i][j] == 'G'){
                setCharacter(j, i, QString::fromUtf8("\xF0\x9F\x8C\xB2"));
            } else if(this->game->getField()[i][j] == 'T'){
                setCharacter(j, i, QString::fromUtf8("\xF0\x9F\x98\x92"));
            } else if(this->game->getField()[i][j] == 'P'){
                setCharacter(j, i, QString::fromUtf8("\xF0\x9F\xA4\x8E"));
            } else if(this->game->getField()[i][j] == 'Y'){
                setCharacter(j, i, QString::fromUtf8("\xF0\x9F\x92\xAA"));
            } else if(this->game->getField()[i][j] == '#') {
                setCharacter(j, i, QString("\u2591"));
            } else if(this->game->getField()[i][j] == 'E') {
                setCharacter(j, i, QString("\u27A5"));
            } else if(this->game->getField()[i][j] == '*'){
                setCharacter(j, i, QString("\u2B50"));
            } else {
                setCharacter(j, i, this->game->getField()[i][j]);
            }
        }
    }
}

//der Spieler wird ausgegeben
void Gui::printPlayer() {
    this->setCharacter(this->game->getP()->getLocationX(), this->game->getP()->getLocationY(), QString::fromUtf8("\xF0\x9F\x98\x83"));
}

//die Steuerung wird ausgegeben
void Gui::printInstructions() {
    this->writeString(0, 30, "Steuerung: Pfeiltasten / Tasten 1 - 6 zum Waehlen des aktiven Monsters");
}

//alle eigenen Monster und das aktive Monster wird ausgegeben
void Gui::printMonster() {
    this->writeString(0, 35, "Aktuelles Monster: " + this->game->getP()->getM()->getName() + " " +
                             std::to_string(this->game->getP()->getM()->getLpNow()) + " / " +
                             std::to_string(this->game->getP()->getM()->getLp()) + " LP  Angriff: " +
                             std::to_string(this->game->getP()->getM()->getAp()));


    for (int i = 0; i < this->game->getP()->getAllMonsters()->size(); ++i) {
        this->writeString(0, 37 + i,
                          std::to_string(i + 1) + "." + (*this->game->getP()->getAllMonsters())[i].getName() + " " +
                          std::to_string((*this->game->getP()->getAllMonsters())[i].getLpNow()) + " / " +
                          std::to_string((*this->game->getP()->getAllMonsters())[i].getLp()) + " LP  Angriff: " +
                          std::to_string((*this->game->getP()->getAllMonsters())[i].getAp()));
    }
}

//Der Kampfdialog wird hier ausgegeben
void Gui::printFight(std::string msg) {
    this->clear();
    this->writeString(0, 5, msg);
    this->writeString(0, 12, "####################################################################################################");
    this->writeString(0, 14, "Dialog weiter: a");
    this->writeString(0, 16, "Dein Monster:");
    this->writeString(0, 19, this->game->getP()->getM()->getName() + " " +
                             std::to_string(this->game->getP()->getM()->getLpNow()) + " / " +
                             std::to_string(this->game->getP()->getM()->getLp()) + " LP  Angriff: " +
                             std::to_string(this->game->getP()->getM()->getAp()));

    this->writeString(50, 16, "Monster des Gegners (1/1)");
    this->writeString(50, 19, this->game->getEnemyMonster()->getName() + " " +
                              std::to_string(this->game->getEnemyMonster()->getLpNow()) + " / " +
                              std::to_string(this->game->getEnemyMonster()->getLp()) + " LP  Angriff: " +
                              std::to_string(this->game->getEnemyMonster()->getAp()));
}

//Der Kampfdialog wird hier ausgegeben (Hier können mehrere Nachrichten übergeben werden)
void Gui::printFight(std::string msg, std::string msg2) {
    this->clear();
    this->writeString(0, 5, msg);
    this->writeString(0, 6, msg2);
    this->writeString(0, 12, "####################################################################################################");

    this->writeString(0, 16, "Dein Monster:");
    this->writeString(0, 19, this->game->getP()->getM()->getName() + " " +
                             std::to_string(this->game->getP()->getM()->getLpNow()) + " / " +
                             std::to_string(this->game->getP()->getM()->getLp()) + " LP  Angriff: " +
                             std::to_string(this->game->getP()->getM()->getAp()));

    this->writeString(50, 16, "Monster des Gegners (1/1)");
    this->writeString(50, 19, this->game->getEnemyMonster()->getName() + " " +
                              std::to_string(this->game->getEnemyMonster()->getLpNow()) + " / " +
                              std::to_string(this->game->getEnemyMonster()->getLp()) + " LP  Angriff: " +
                              std::to_string(this->game->getEnemyMonster()->getAp()));
}

//Hier wird der Score ausgegeben
void Gui::printScore() {
    this->writeString(0, 32, "Score: " + std::to_string(this->game->getScore()));
}
