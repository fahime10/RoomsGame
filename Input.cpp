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
    }


    
    return Input::UNKNOWN;

}

void handleUserInput(Input input, Player p, vector<Room> rooms) {
    string currentRoomDesc;

    for (auto room: rooms) {
        if (p.getCurrentRoom() == room.getId()) {
            currentRoomDesc = room.getDescription();
        }
    }

    switch (input) {
        case Input::LOOK:
            cout << currentRoomDesc << endl;
            break;

        case Input::UNKNOWN:
            cout << "Instruction not understood" << endl;
            break;
    }
}