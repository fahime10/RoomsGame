#include "Input.h"
#include "GameFlow.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

// Function to obtain an enum type
Input parseInput(const vector<string>& input) {
    if (((input[0] == "look" || input[0] == "see" || input[0] == "check") && input.size() == 1) || 
        ((input[0] == "look" || input[0] == "check") && input.size() > 1) ||
        ((input[0] == "look" && input[1] == "around") && input.size() == 2) ||
        ((input[0] == "check" && input[1] == "room") && input.size() == 2)) {
        return Input::LOOK;

    } else if (((input[0] == "items" || input[0] == "inventory") && input.size() == 1) || 
                ((input[0] == "list" && input[1] == "items") && input.size() == 2) || 
                ((input[0] == "check" || input [0] == "view") && input[1] == "inventory" && input.size() == 2)) {
        return Input::LIST_ITEMS;

    } else if ((input[0] == "grab" || input[0] == "take" || input[0] == "pick")) {
        return Input::TAKE_ITEM;

    } else if (((input[0] == "check" || input[0] == "see" || input[0] == "look") && input.size() == 2) ||
                 (input[0] == "look" && input[1] == "at") && input.size() == 3) {
        return Input::CHECK_ITEM;

    } else if ((input[0] == "exit" || input[0] == "exits") && input.size() == 1 || 
                ((input[0] == "list" && input[1] == "exits" && input.size() == 2))) {
        return Input::LIST_EXITS;

    } else if ((input[0] == "go" || input[0] == "move") && input.size() == 2) {
        return Input::MOVE;

    } else if ((input[0] == "attack" || input[0] == "kill")) {
        return Input::ATTACK;

    }
    
    return Input::UNKNOWN;
}

// Get a random number between 0 and 100
int getRandomNumber(int min, int max) {
    srand(time(0));
    return rand() % (max - min + 1) + min;
}

// Function to handle the different actions such as moving rooms, attacking enemies and more
void handleInput(vector<string> input, Input enumInput, Player& p, map<string, Room>& rooms, 
                 map<string, Item>& items, map<string, Enemy>& enemies) {
    int itemsSize = 0;
    int enemiesSize = 0;

    bool anyItem = !rooms[p.getCurrentRoom()].getItems().empty();
    itemsSize = rooms[p.getCurrentRoom()].getItems().size();

    bool anyEnemy = !rooms[p.getCurrentRoom()].getEnemies().empty();
    enemiesSize = rooms[p.getCurrentRoom()].getEnemies().size();

    switch (enumInput) {
        case Input::LOOK: 
        {
            string request;

            for (int i = 1; i < input.size(); i++) {
                if (i + 1 == input.size()) {
                    request += input[i];
                } else {
                    request += input[i] + " ";   
                }
            }

            if (anyItem) {
                for (auto item: rooms[p.getCurrentRoom()].getItems()) {
                    if (request == item.second.getId()) {
                        cout << item.second.getDescription() << "\n" << endl;
                        return;
                    }
                }
            }

            if (anyEnemy) {
                for (auto enemy: rooms[p.getCurrentRoom()].getEnemies()) {
                    if (request == enemy.second.getId()) {
                        cout << enemy.second.getDescription() << "\n" << endl;
                        return;
                    }
                }
            }

            for (auto item: p.getInventory()) {
                if (request == item.second.getId()) {
                    cout << item.second.getDescription() << "\n" << endl;
                    return;
                }
            }

            cout << "\n" << rooms[p.getCurrentRoom()].getDescription() << "\n" << endl;

            if (anyItem && itemsSize > 1) {
                cout << "There are items in this room: " << endl;
                cout << rooms[p.getCurrentRoom()].printItems() << "\n" << endl;
            } else if (anyItem) {
                cout << "There is an item in this room: " << endl;
                cout << rooms[p.getCurrentRoom()].printItems() << "\n" << endl;
            }

            if (anyEnemy && enemiesSize > 1) {
                cout << "There are enemies in this room: " << endl;
                cout << rooms[p.getCurrentRoom()].printEnemies() << "\n" << endl;
            } else if (anyEnemy) {
                cout << "There is an enemy in this room: " << endl;
                cout << rooms[p.getCurrentRoom()].printEnemies() << "\n" << endl;
            }
            break;
        }

        case Input::LIST_ITEMS:
        {
            cout << p.viewInventory() << "\n" << endl;
            break;
        }

        case Input::TAKE_ITEM:
        {
            bool itemFound = false;

            if (anyItem) {
                string requestedItem = "";

                for (int i = 1; i < input.size(); i++) {
                    if (i + 1 == input.size()) {
                        requestedItem += input[i];
                    } else {
                        requestedItem += input[i] + " ";   
                    }
                }
                
                itemFound = items[requestedItem].getId() == requestedItem;

                if (itemFound && !requestedItem.empty()) {
                    p.addToInventory(items[requestedItem]);
                    rooms[p.getCurrentRoom()].removeItem(requestedItem);
                    items.erase(requestedItem);
                    cout << "You have taken: " + requestedItem + "\n" << endl;

                } else {
                    cout << "Item not found in the room\n" << endl;
                }
            } else {
                cout << "Item not found in the room\n" << endl;
            }
            break;
        }

        case Input::CHECK_ITEM:
        {
            if (!p.getInventory().empty()) {
                string object = "";

                for(const auto& item: p.getInventory()) {
                    if (item.second.getId() == input[1] || item.second.getId() == input[2]) {
                        object += item.second.getDescription();
                        break;
                    }
                }

                if (object.empty()) {
                    cout << "Item not found\n" << endl;
                } else {
                    cout << object << "\n" << endl;
                }

            } else {
                cout << "Item not found\n" << endl;
            }
            break;
        }
        
        case Input::MOVE: {
            string requestedDirection = "";

            for (int i = 1; i < input.size(); i++) {
                if (i + 1 == input.size()) {
                    requestedDirection += input[i];
                } else {
                    requestedDirection += input[i] + " ";
                }
            }

            bool movePossible = false;
            string newRoom = "";

            if (anyEnemy) {
                int aggressiveness = 
                    rooms[p.getCurrentRoom()].getEnemies().begin()->second.getAggressiveness();

                int chance = getRandomNumber(0, 100);

                if (chance < aggressiveness) {
                    cout << "Enemy has attacked you. You have been defeated.\n" << endl;
                    exit(0);
                }
            }

            auto roomIt = rooms.find(p.getCurrentRoom());
            if (roomIt != rooms.end()) {
                const Room& currentRoom = roomIt->second;

                auto exitIt = currentRoom.getExits().find(requestedDirection);
                if (exitIt != currentRoom.getExits().end()) {
                    movePossible = true;
                    newRoom = exitIt->second;
                }
            }

            if (movePossible) {
                p.setCurrentRoom(newRoom);
                cout << "You moved to " << newRoom << endl;
            } else {
                cout << "Instruction not understood\n" << endl;
            }
            break;
        }

        case Input::ATTACK:
        {
            bool success = false;
            string requestedEnemy = "";
            bool enemyFound;

            for (int i = 1; i < input.size(); i++) {
                if (i + 1 == input.size()) {
                    requestedEnemy += input[i];
                } else {
                    requestedEnemy += input[i] + " ";
                }
            }

            enemyFound = 
                (enemies[requestedEnemy].getId() == requestedEnemy) && 
                (p.getCurrentRoom() == enemies[requestedEnemy].getInitialRoom());

            if (enemyFound) {
                success = 
                    all_of(enemies[requestedEnemy].getKilledBy().begin(),
                        enemies[requestedEnemy].getKilledBy().end(),
                        [&p](const auto& enemyItems) {
                            return p.getInventory().count(enemyItems.first) > 0;
                        });
            }

            if (success) {
                cout << enemies[requestedEnemy].getId() << " has been defeated\n" << endl;
                enemies.erase(requestedEnemy);
                rooms[p.getCurrentRoom()].removeEnemy(requestedEnemy);
            } else if (!enemyFound) {
                cout << "Instruction not understood\n" << endl;
            } else {
                cout << "\nYou do not have enough items. \nYou have been defeated\n" << endl;
                exit(0);
            }
            break;
        }

        case Input::LIST_EXITS:
        {
            cout << rooms[p.getCurrentRoom()].printExits() << endl;
            break;
        }

        case Input::UNKNOWN:
        {
            cout << "Instruction not understood" << "\n" << endl;
            break;
        }
    }
}
