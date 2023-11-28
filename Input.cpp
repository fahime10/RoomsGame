#include <iostream>
#include "Input.h"
using namespace std;

// This is required to work with switch statements
// Some strings/commands could be regarded as the same enum
Input parseInput(const string& input) {
    if (input == "look" || input == "look around" || input == "see" || 
        input == "check room" || input == "check") {
        return Input::LOOK;
    } else if (input == "quit" || input == "quit game" || input == "q") {
        return Input::QUIT;
    } else if (input == "list items" || input == "inventory") {
        return Input::LIST_ITEMS;
    }
    
    return Input::UNKNOWN;
}

void handleUserInput(Input input, Player p, vector<Room> rooms, vector<Item> items) {
    string currentRoomDesc;
    string inventoryList;

    for (const auto& room : rooms) {
        if (p.getCurrentRoom() == room.getId()) {
            currentRoomDesc = room.getDescription();
        }
    }

    // Use the result of p.viewInventory directly
    inventoryList = p.viewInventory();

    switch (input) {
        case Input::LOOK:
            cout << currentRoomDesc << endl;
            break;

        case Input::LIST_ITEMS:
            cout << inventoryList << endl;
            break;

        case Input::UNKNOWN:
            cout << "Instruction not understood" << endl;
            break;
    }
}
