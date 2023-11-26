#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <vector>

using namespace std;

class Enemy {
public:
    // Constructor
    Enemy(const string id, const string desc, int aggressiveness,
          const string initialRoom, const vector<string> killedBy);

    // Destructor
    ~Enemy();

    // Getter functions
    string getId() const;
    string getDescription() const;
    int getAggressiveness() const;
    string getInitialRoom() const;
    string getKilledBy() const;

    // Member functions
    bool attackPlayer() const;
    void printAttackMessage() const;

private:
    // Member variables
    string id_;
    string description_;
    int aggressiveness_;
    string initial_room;
    vector<string> killed_by;
};

#endif // ENEMY_H