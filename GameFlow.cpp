#include <iostream>
#include <vector>
#include <map>
#include "json.hpp"
#include "GameFlow.h"
#include "classes/Item.h"
#include "classes/Room.h"
#include "classes/Player.h"
#include "classes/Enemy.h"
#include "Input.h"
using namespace std;
using json = nlohmann::json;

void presentCurrentRoom(Player, vector<Room>&);
void checkGameOver();

// Build all instances of Room, Item, Enemy and Player first, then populate
// all the Room instances with Item, Enemy and Player as defined in the 
// chosen JSON map
void GameFlow::buildGame(json j) {
    try {
        for (auto room: j["rooms"]) {
            vector<map<string, string>> keyValues;

            for (auto exit: room["exits"].items()) {
                map<string, string> map;
                string key = exit.key();
                map[key] = exit.value();
                keyValues.push_back(map);
            }
            Room r(room["id"], room["desc"], keyValues);
            rooms.push_back(r);
        }

        for (auto enemy: j["enemies"]) {
            vector<string> killedBy;

            for (auto item: enemy["killedby"]) {
                killedBy.push_back(item);
            }
            Enemy e(enemy["id"], enemy["desc"], enemy["aggressiveness"], enemy["initialroom"], killedBy);
            enemies.push_back(e);
        }

        for (auto object: j["objects"]) {
            Item i(object["id"], object["desc"], object["initialroom"]);
            items.push_back(i);
        }

        p = Player(j["player"]["initialroom"]);

        for (Room room: rooms) {
            for (Enemy enemy: enemies) {
                if (enemy.getInitialRoom() == room.getId()) {
                    room.addEnemy(enemy);
                }
            }

            for (Item item: items) {
                if (item.getInitialRoom() == room.getId()) {
                    room.addItem(item);
                }
            }

            if (p.getInitialRoom() == room.getId()) {
                room.setPlayerLocation();
                p.setCurrentRoom(room.getId());
            } 
        }

    } catch (exception ex) {
        cerr << "Error reading file" << endl;
        return;
    }
}

// This is where user input is handled
void GameFlow::playGame() {
    presentCurrentRoom(p, rooms);

    string command;

    getline(cin, command);

    Input input;

    while (command != "quit" && command != "q") {
        input = parseInput(command);
        handleUserInput(input, p, rooms, vector<Item>());
        checkGameOver();

        if (input != Input::LOOK && input != Input::UNKNOWN) {
            presentCurrentRoom(p, rooms);
        }

        getline(cin, command);
    }
}

// This presents the current room the player is at
void presentCurrentRoom(Player p, vector<Room>& rooms) {
    for (auto room: rooms) {
        if (p.getCurrentRoom() == room.getId()) {
            cout << room.getDescription() << endl;
        }
    }
}

// This will constantly check if the player has been defeated by enemy or
// by soft-locking themselves
void checkGameOver() {

}