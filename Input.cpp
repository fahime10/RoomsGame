#include <iostream>
#include "Input.h"
using namespace std;

// This is required to work with switch statements
// Some strings/commands could be regarded as the same enum
Input parseInput(const string& input) {
    if (input == "look" || input == "look around" || input == "see" || 
        input == "check room" || input == "check") {
        return Input::LOOK;

    } else if (input == "list items" || input == "items" || input == "inventory" || 
                input == "check inventory" || input == "view inventory") {
        return Input::LIST_ITEMS;

    } else if (input == "list exits" || input == "exits") {
        return Input::LIST_EXITS;

    } else if (input == "go left" || input == "go west") {
        return Input::GO_LEFT;

    } else if (input == "go ahead" || input == "go up" || input == "go north") {
        return Input::GO_UP;

    } else if (input == "go right" || input == "go east") {
        return Input::GO_RIGHT;

    } else if (input == "go down" || input == "go south") {
        return Input::GO_DOWN;

    } else if (input == "go back" || input == "go out") {
        return Input::GO_BACK;

    } else if (input == "quit" || input == "quit game" || input == "q") {
        return Input::QUIT;
    }
    
    return Input::UNKNOWN;
}

void handleUserInput(Input input, Player& p, vector<Room> rooms, vector<Item> items) {
    string currentRoomDesc;
    string exits;
    string itemList;
    bool anyItem;

    for (const auto& room : rooms) {
        if (p.getCurrentRoom() == room.getId()) {
            currentRoomDesc = room.getDescription();

            if (!(room.getItems().empty())) {
                anyItem = true;
                itemList = "There are items in this room \n" + room.printItems();
            } 
            
            exits = room.getExits();
        }
    }

    switch (input) {
        case Input::LOOK:
            cout << currentRoomDesc << endl;

            if (anyItem) {
                cout << itemList << "\n" << endl;
            }
            break;

        case Input::LIST_ITEMS:
            cout << p.viewInventory() << "\n" << endl;
            break;

        case Input::LIST_EXITS:
            cout << exits << endl;
            break;

        case Input::UNKNOWN:
            cout << "Instruction not understood" << "\n" << endl;
            break;
    }
}
