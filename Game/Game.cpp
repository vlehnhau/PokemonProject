#include "Game.h"

Game::Game() {
    this->p = new Player();
    std::fstream input("../map_basic.txt");
    std::string line;

    for (int i = 0; i < 30; ++i) {
        std::vector<char> vec;
        field.push_back(vec);
        for (int j = 0; j < 80; ++j) {
            field[i].push_back(' ');
        }
    }

    int i = 0;
    while(std::getline(input, line)) {
        for (int j = 0; j < line.size(); ++j) {
            field[i][j] = line[j];
        }
        i++;
    }
}

const std::vector<std::vector<char>> &Game::getField() const {
    return field;
}
