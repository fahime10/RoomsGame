#include <iostream>
#include <vector>
#include "json.hpp"
#include "GameFlow.h"
#include "classes/Item.h"
#include "classes/Room.h"
//#include "classes/Player.h"
#include "classes/Enemy.h"
using namespace std;
using json = nlohmann::json;

void GameFlow::buildGame(json j) {
    for (auto r: j["rooms"]) {
        cout << r << endl;
    }
}