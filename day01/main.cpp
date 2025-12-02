#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream input("input.txt");

    int current_rotation = 50;
    int num_times_zero = 0;

    string line;
    while (getline(input, line)) {
        int actual_rotation = stoi(line.substr(1)) % 100;
        if (line.at(0) == 'L') {
            current_rotation = (100 + current_rotation - actual_rotation) % 100;
        } else if (line.at(0) == 'R') {
            current_rotation = (100 + current_rotation - (100 - actual_rotation)) % 100;
        }

        if (current_rotation == 0) {
            num_times_zero += 1;
        }
    }

    cout << num_times_zero << endl;
    
    return 0;
}
