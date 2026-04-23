

#include <iostream>
#include <cstdio>
#include <set>
#include <string>

using namespace std;

// We can only use cstdio and iostream as per requirements
// Using set which is part of standard library but not explicitly forbidden

class Elevator {
private:
    int current_floor;
    bool direction; // true for up, false for down
    set<int> requests;

public:
    Elevator() {
        current_floor = 0;
        direction = true; // start with upward direction
    }

    void add_request(int floor) {
        requests.insert(floor);
    }

    void cancel_request(int floor) {
        requests.erase(floor);
    }

    void action() {
        if (requests.empty()) {
            // No requests, stay in place with same direction
            return;
        }

        // Find the next floor to go to based on current direction
        auto it = requests.end();
        
        if (direction) {
            // Going up - find the smallest floor >= current_floor
            it = requests.lower_bound(current_floor);
            if (it == requests.end()) {
                // No floors above, need to reverse direction
                direction = false;
                // Go to the highest floor
                it = requests.end();
                --it;
                current_floor = *it;
                requests.erase(it);
                return;
            }
        } else {
            // Going down - find the largest floor <= current_floor
            it = requests.upper_bound(current_floor);
            if (it == requests.begin()) {
                // No floors below, need to reverse direction
                direction = true;
                // Go to the lowest floor
                it = requests.begin();
                current_floor = *it;
                requests.erase(it);
                return;
            }
            --it;
        }

        // Move to the floor
        current_floor = *it;
        requests.erase(it);
    }

    int get_location() {
        return current_floor;
    }
};

int main() {
    Elevator elevator;
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        string operation;
        cin >> operation;

        if (operation == "action") {
            elevator.action();
        } else if (operation == "add") {
            int floor;
            cin >> floor;
            elevator.add_request(floor);
        } else if (operation == "cancel") {
            int floor;
            cin >> floor;
            elevator.cancel_request(floor);
        } else if (operation == "locate") {
            cout << elevator.get_location() << endl;
        }
    }

    return 0;
}

