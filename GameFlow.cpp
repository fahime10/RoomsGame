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

void presentCurrentRoom(Player, vector<Room>&, vector<Item>&, vector<Enemy>&);
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

        for (Room& room: rooms) {
            for (Enemy& enemy: enemies) {
                if (enemy.getInitialRoom() == room.getId()) {
                    room.addEnemy(enemy);
                }
            }

            for (Item& item: items) {
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

void GameFlow::printItems() const {
    string itemList;
    for (Item item: items) {
        itemList += "[" + item.getId() + "]";
    }

    cout << itemList << endl;
}

// Function to play the game and handle all sorts of user input
void GameFlow::playGame() {
    presentCurrentRoom(p, rooms, items, enemies);

    string command;

    getline(cin, command);

    // This is used to handle an array of strings
    istringstream is(command);
    vector<string> strArray;
    string singleStr;

    while (is >> singleStr) {
        strArray.push_back(singleStr);
    }

    Input enumInput;

    // This is where user input is handled
    while (command != "quit" && command != "q") {
        enumInput = parseInput(strArray);
        handleUserInput(strArray, enumInput, p, rooms, items);
        checkGameOver();

        // if (enumInput == Input::MOVE) {
        //     presentCurrentRoom(p, rooms, items, enemies);
        //     cout << "\n" << endl;
        // }

        getline(cin, command);

        strArray.clear();

        istringstream is(command);

        while (is >> singleStr) {
            strArray.push_back(singleStr);
        }
    }
}

// This presents the current room the player is at
void presentCurrentRoom(Player p, vector<Room>& rooms, vector<Item>& items, vector<Enemy>& enemies) {
    for (auto room: rooms) {
        if (p.getCurrentRoom() == room.getId()) {
            cout << "\n" << room.getDescription() << endl;

            if (!room.getItems().empty()) {
                cout << "There are items in this room: " << endl;
                cout << room.printItems() << "\n" << endl;
            }
        }
    }
}

// This will constantly check if the player has been defeated by enemy or
// by soft-locking themselves
void checkGameOver() {

}