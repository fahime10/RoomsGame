#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "json.hpp"
#include "GameFlow.h"
using namespace std;
using json = nlohmann::json;

int main(int argc, char* argv[]) {

    string map;

    if (argc == 2) {
        map = *(argv+1);
    } else {
        cerr << "Please select a suitable map" << endl;
        return 1;
    }

	ifstream fin(map);
	json j;
	fin >> j;

    GameFlow game;
    game.buildGame(j);
	game.playGame();
}
