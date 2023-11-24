#include <string>

using namespace std;

class Item {
public:
    // Constructor
    Item(const string& id, const string& desc, const string& initialRoom);

    // Destructor
    ~Item();

    // Getter functions
    string getId() const;
    string getDescription() const;
    string getInitialRoom() const;

private:
    // Member variables
    string id_;
    string description_;
    string initial_room;
};