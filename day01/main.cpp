#include <iostream>
#include <fstream>

using namespace std;

int part_one()
{
    ifstream input("input.txt");

    int current_rotation = 50;
    int num_times_zero = 0;

    string line;
    while (getline(input, line))
    {
        int actual_rotation = stoi(line.substr(1)) % 100;
        if (line.at(0) == 'L')
        {
            current_rotation = (100 + current_rotation - actual_rotation) % 100;
        }
        else if (line.at(0) == 'R')
        {
            current_rotation = (100 + current_rotation - (100 - actual_rotation)) % 100;
        }

        if (current_rotation == 0)
        {
            num_times_zero += 1;
        }
    }

    input.close();

    return num_times_zero;
}

int part_two()
{
    ifstream input("input.txt");

    int current_rotation = 50;
    int num_times_passed_zero = 0;

    string line;
    while (getline(input, line))
    {
        int raw_rotation = stoi(line.substr(1));
        int actual_rotation = raw_rotation % 100;
        if (line.at(0) == 'L')
        {
            num_times_passed_zero += -((current_rotation - raw_rotation - 100) / 100);
            // there is definitely a better way to account for starting point of 0
            if (current_rotation == 0) {
                num_times_passed_zero -= 1;
            }
            current_rotation = (100 + current_rotation - actual_rotation) % 100;
        }
        else if (line.at(0) == 'R')
        {
            // (raw_rotation + current_rotation) / 100 = number of times passed 0
            num_times_passed_zero += (current_rotation + raw_rotation) / 100;
            current_rotation = (100 + current_rotation - (100 - actual_rotation)) % 100;
        }
    }

    input.close();

    return num_times_passed_zero;
}

int main()
{
    cout << "Part 1 solution: " << part_one() << endl;
    cout << "Part 2 solution: " << part_two() << endl;

    return 0;
}
