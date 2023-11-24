#include <string>
#include <vector>

using namespace std;

class Enemy {
public:
    // Constructor
    Enemy(const string& id, const string& desc, int aggressiveness,
          const string& initialRoom, const vector<string>& killedBy);

    // Destructor
    ~Enemy();

    // Getter functions
    string getId() const;
    string getDescription() const;
    int getAggressiveness() const;
    string getInitialRoom() const;
    const vector<string>& getKilledBy() const;

    // Member functions
    void moveToRoom(const string& room);
    bool attackPlayer() const;
    void printAttackMessage() const;

private:
    // Member variables
    string id_;
    string description_;
    int aggressiveness_;
    string initialRoom_;
    vector<string> killedBy_;
};