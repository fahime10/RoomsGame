#include <iostream>
#include "Input.h"
#include "GameFlow.h"
#include <algorithm>
using namespace std;

// This is required to work with switch statements
// Some strings/commands could be regarded as the same enum
Input parseInput(const vector<string>& input) {
    if (((input[0] == "look" || input[0] == "see" || input[0] == "check") && input.size() == 1) || 
        ((input[0] == "look" && input[1] == "around") && input.size() == 2) ||
        ((input[0] == "check" && input[1] == "room") && input.size() == 2)) {
        return Input::LOOK;

    } else if (((input[0] == "items" || input[0] == "inventory") && input.size() == 1) || 
                ((input[0] == "list" && input[1] == "items") && input.size() == 2) || 
                ((input[0] == "check" || input [0] == "view") && input[1] == "inventory" && input.size() == 2)) {
        return Input::LIST_ITEMS;

    } else if ((input[0] == "grab" || input[0] == "take" || input[0] == "pick")) {
        return Input::TAKE_ITEM;

    } else if (((input[0] == "check" || input[0] == "see") && input.size() == 2) ||
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

void handleUserInput(vector<string> input, Input enumInput, Player& p, 
                     map<string, Room>& rooms, map<string, Item>& items, map<string, Enemy>& enemies) {

    string exits;
    bool anyItem;
    bool anyEnemy;

    anyItem = !rooms[p.getCurrentRoom()].getItems().empty();

    anyEnemy = !rooms[p.getCurrentRoom()].getEnemies().empty();

    exits = rooms[p.getCurrentRoom()].printExits();

    switch (enumInput) {
        case Input::LOOK: 
        {
            for (auto& room: rooms) {
                if (p.getCurrentRoom() == room.first) {
                    cout << "\n" << room.second.getDescription() << endl;

                    if (!room.second.getItems().empty()) {
                        cout << "There are items in this room: " << endl;
                        cout << room.second.printItems() << "\n" << endl;
                    }

                    if (!room.second.getEnemies().empty()) {
                        cout << "There are enemies in this room: " << endl;
                        
                        for (auto& enemy: enemies) {
                            if (enemy.second.getInitialRoom() == room.first) {
                                cout << "[ " << enemy.second.getId() << " ]" << endl;
                                cout << enemy.second.getDescription() << endl;
                                cout << "It can be killed by: " << endl;

                                if (enemy.second.getKilledBy().empty()) {
                                    cout << "[ Bare hands ] \n" << endl;
                                } else {
                                    cout << enemy.second.printKilledBy() << "\n" <<  endl;
                                }
                            }
                        }
                    }
                }
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
            if (anyItem) {
                string requestedItem = "";

                for (int i = 1; i < input.size(); i++) {
                    if (i + 1 == input.size()) {
                        requestedItem += input[i];
                    } else {
                        requestedItem += input[i] + " ";   
                    }
                }
                
                bool itemFound = items[requestedItem].getId() == requestedItem;

                if (itemFound) {
                    p.addToInventory(items[requestedItem]);
                    rooms[p.getCurrentRoom()].removeItem(requestedItem);
                    items.erase(requestedItem);
                    cout << "You have taken: " + requestedItem + "\n" << endl;

                } else {
                    cout << "Item not found in the room\n" << endl;
                }
                break;
            }
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
        
        case Input::MOVE:
        {
            if (input.size() == 2) {
                string direction = input[1];
                bool movePossible = false;
                bool success;

                movePossible = rooms[direction].getId() == direction;

                auto it = rooms[p.getCurrentRoom()].getExits().find(direction);

                if (it != rooms[p.getCurrentRoom()].getExits().end()) {
                    movePossible = true;
                }

                if (movePossible) {
                    p.setCurrentRoom(it->second);
                    cout << "You moved in " << p.getCurrentRoom() << endl;
                } else {
                    cout << "Move not possible\n" << endl;
                }

            } else {
                cout << "Invalid move command. Usage: go <direction>.\n" << endl;
            }
            break;
        }

        case Input::ATTACK:
        {
            bool success;
            string requestedEnemy = "";
            bool enemyFound;

            for (int i = 1; i < input.size(); i++) {
                if (i + 1 == input.size()) {
                    requestedEnemy += input[i];
                } else {
                    requestedEnemy += input[i] + " ";
                }
            }

            enemyFound = (enemies[requestedEnemy].getId() == requestedEnemy) && 
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
                cout << "Enemy " << enemies[requestedEnemy].getId() << " has been defeated\n" << endl;
                rooms[p.getCurrentRoom()].removeEnemy(requestedEnemy);
            } else if (!enemyFound) {
                cout << "Instruction not understood\n" << endl;
            } else {
                cout << "You do not have enough items. \nYou have been defeated" << endl;
                exit(0);
            }
            break;
        }

        case Input::LIST_EXITS:
        {
            cout << exits << endl;
            break;
        }

        case Input::UNKNOWN:
        {
            cout << "Instruction not understood" << "\n" << endl;
            break;
        }
    }
}
