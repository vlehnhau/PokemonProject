#include "Gui.h"

void Gui::onRefresh() { // Diese Methode ist dafür zuständig das board anzuziegen und die tasten anschläge zu erkennen
    if (!gameStarted){
        this->clear();
        this->writeString(0,5,"Menue");
        this->writeString(0,10,"Waehle dein Level aus");
        this->writeString(0,12,"1. Level (Basic)");
        this->writeString(0,14,"2. Level (Advanced)");
        this->writeString(0,16,"3. Level (Boss Level)");
        this->writeString(0,18,"4. Level (Test Level)");
        this->writeString(0,22,"e: Veralssen des Spiels");
        if (this->getPressedKey() == '1') {
            this->game = new Game(1);
            gameStarted = true;
        } else if (this->getPressedKey() == '2') {
            this->game = new Game(2);
            gameStarted = true;
        } else if (this->getPressedKey() == '3') {
            this->game = new Game(3);
            gameStarted = true;
        } else if (this->getPressedKey() == '4') {
            this->game = new Game(4);
            gameStarted = true;
        } else if (this->getPressedKey() == 'e') {
            exit(0);
        }
    }
    if (gameStarted && int(std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::system_clock::now() - startRoundTime).count()) > 50000) { //Hier wird so lange gewartet bis der spieler sich wieder bewegen kann
        //Hier wird das Board aktualisiert
        this->clear();
        this->printBoard();
        this->printPlayer();
        this->printInstructions();
        this->printMonster();
        this->printScore();

        //Hier wird nachgeschaut in welcher Spielphase der Spieler sich befindet und dementsprechent die passenden tasten genutzt
        if (!this->game->isMonsterFound() && this->game->getFighting() == 0 && !this->game->isLose() && !this->game->isWin()) {
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
        } else if (this->game->getFighting() == 0 && !this->game->isLose() && !this->game->isWin()) {
            //take the monster
            if (this->getPressedKey() == '1' && this->game->getP()->getAllMonsters()->size() < 6) {
                this->game->addMonster();
                this->game->setMonsterFound(false);
            } else if (this->getPressedKey() == '2') {
                this->game->setMonsterFound(false);
                delete this->game->getNewMonster();
                this->game->setNewMonster(nullptr);
            }
        } else if (!this->game->isMonsterFound() && this->game->getFighting() != 0 && !this->game->isLose() && !this->game->isWin()) {
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

                if(this->game->getP()->getM()->getSpecial() != 0 && this->getPressedKey() == 's' && !this->game->isLose() && !this->game->isWin()){
                    if(this->game->getP()->getM()->getSpecial() == 1){
                        this->game->specialAttack(1);
                    } else if(this->game->getP()->getM()->getSpecial() == 2){
                        this->game->specialAttack(2);
                    } else if(this->game->getP()->getM()->getSpecial() == 3){
                        this->game->specialAttack(3);
                    }
                }

                if (this->getPressedKey() == '1' && !this->game->isLose() && !this->game->isWin()) {
                    this->game->attack();
                } else if (this->getPressedKey() == '2' && !this->game->isLose() && !this->game->isWin()) {
                    if (!this->game->isFightHealingUsed()) {
                        this->game->fightHealing();
                    }
                } else if (this->getPressedKey() == '3' && !this->game->isLose() && !this->game->isWin()) {
                    this->game->run();
                } else if (this->getPressedKey() == 'p' && !this->game->isLose() && !this->game->isWin()) {
                    this->game->setFighting(3);
                } else if (this->getPressedKey() == '4' && !this->game->isLose() && !this->game->isWin()) {
                    this->game->train();
                }
            } else if (this->game->getFighting() == 3 && !this->game->isLose() && !this->game->isWin()) {
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
            } else if (this->game->getFighting() == 4 && !this->game->isLose() && !this->game->isWin()) {
                //win
                printFight("Du hast Gary besiegt");
                if (this->getPressedKey() == 'a') {
                    this->game->setFighting(0);
                    this->game->setFightHealingUsed(false);
                    delete this->game->getEnemyMonster();
                    this->game->setEnemyMonster(nullptr);
                }
            }
        }

        //Das passiert wenn der Spieler ein Y Feld betritt -> dies passiert hier und nicht in der move methode da so immerwieder nachgeschaut werden kann wie lange er hier schon steht
        if (this->game->getField()[this->game->getP()->getLocationY()][this->game->getP()->getLocationX()] == 'Y') {
            this->game->newMaxHealth();
        }

        //Hier ist die Anzeige, für den Fall dass ein wildes Monster gefunden wurde
        if (this->game->isMonsterFound()) {
            if (this->game->getP()->getAllMonsters()->size() < 6) {
                this->clear();
                this->writeString(0, 10, "Ein Monster (" + this->game->getNewMonster()->getName() +
                                         ") erscheint. Was moechtest du tun?");
                this->writeString(0, 11, "1: Fangen | 2: Flucht");
            } else {
                this->clear();
                this->writeString(0, 10, "Ein Monster (" + this->game->getNewMonster()->getName() +
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

        //Hier wird überprüft ob der spieler verloren oder gewonnen hat
        if (this->game->isLose()) {
            this->clear();
            this->writeString(0, 10, "Du hast verloren!");
            this->writeString(0,12, "Dein Score: " + std::to_string(this->game->getScore()));
            this->writeString(0, 14, "Zurueck zum Menue?: a");
            if (this->getPressedKey() == 'a') {
                this->gameStarted = false;
                delete game;
                game = nullptr;
            }
        } else if (this->game->isWin()) {
            this->clear();
            this->writeString(0, 10, "Du hast gewonnen!");
            this->writeString(0,12, "Dein Score: " + std::to_string(this->game->getScore()));
            this->writeString(0, 14, "Zurueck zum Menue?: a");
            if (this->getPressedKey() == 'a') {
                this->gameStarted = false;
                delete game;
                game = nullptr;
            }
        }
        startRoundTime = std::chrono::system_clock::now();//Hier wird eine neue runden Zeit begonnen sodass oben passend gewartet werden kann
    }
}

//Constructor
Gui::Gui() : ConsoleWindow(nullptr, 100, 50) {  //Setzt die Fenstergröße

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
    this->writeString(0, 3, msg);
    this->writeString(0, 4, msg2);
    this->writeString(0, 14, "####################################################################################################");

    this->writeString(0, 18, "Dein Monster:");
    this->writeString(0, 21, this->game->getP()->getM()->getName() + " " +
                             std::to_string(this->game->getP()->getM()->getLpNow()) + " / " +
                             std::to_string(this->game->getP()->getM()->getLp()) + " LP  Angriff: " +
                             std::to_string(this->game->getP()->getM()->getAp()));

    if(this->game->getP()->getM()->getSpecial() != 0){
        this->writeString(0, 8, "Dein Monster hat eine Specielle Faehigkeit und kann");
        if(this->game->getP()->getM()->getSpecial() == 1){
            this->writeString(0, 9, "einfach aus dem Kapf fliegen! (Flucht zu 100%)");
        } else if(this->game->getP()->getM()->getSpecial() == 2){
            this->writeString(0, 9, "den Gegner schwaechen! (-2 AP) Er kann nicht unter 1 AP Fallen");
        } else if(this->game->getP()->getM()->getSpecial() == 3){
            this->writeString(0, 9, "dem Gegner 2 LP klauen! (Du kannst ihn damit aber nicht toeten)");
        }
        this->writeString(0, 10, "Druecke \"s\" um diese Attacke zu waehlen");
    }

    this->writeString(50, 18, "Monster des Gegners (1/1)");
    this->writeString(50, 21, this->game->getEnemyMonster()->getName() + " " +
                              std::to_string(this->game->getEnemyMonster()->getLpNow()) + " / " +
                              std::to_string(this->game->getEnemyMonster()->getLp()) + " LP  Angriff: " +
                              std::to_string(this->game->getEnemyMonster()->getAp()));
}

//Hier wird der Score ausgegeben
void Gui::printScore() {
    this->writeString(0, 32, "Score: " + std::to_string(this->game->getScore()));
}
