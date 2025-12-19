#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

int count_digits(long num)
{
    int num_digits = 0;
    while (num > 0)
    {
        num /= 10;
        num_digits += 1;
    }
    return num_digits;
}

bool has_odd_digits(long num)
{
    return count_digits(num) % 2 == 1;
}

void append_part_one_valid_ranges(string original_range, vector<tuple<long, long, int>> &computed_ranges)
{
    // Source - https://stackoverflow.com/a
    // Posted by Sam Varshavchik, modified by community. See post 'Timeline' for change history
    // Retrieved 2025-12-18, License - CC BY-SA 3.0
    std::istringstream input_line(original_range);

    string start_raw;
    string end_raw;
    getline(input_line, start_raw, '-');
    getline(input_line, end_raw, '-');

    long start = stol(start_raw);
    long end = stol(end_raw);
    int end_digits = count_digits(end);

    long base = start;
    while (count_digits(base) <= end_digits)
    {
        if (has_odd_digits(base))
        {
            base = (long)pow(10, count_digits(base));
        }
        else if (count_digits(base) == end_digits)
        {
            computed_ranges.push_back({base, end, end_digits});
            return;
        }
        else if (count_digits(base) < end_digits)
        {
            // e.g. previous base of 1000 -> new base of 100000
            long new_base = (long)pow(10, count_digits(base) + 1);
            long cap = (long)pow(10, count_digits(base)) - 1;
            computed_ranges.push_back({base, cap, count_digits(cap)});
            base = new_base;
        }
    }
}

long part_one()
{
    ifstream input("input.txt");

    // tuple: (start, end inclusive, number of digits)
    vector<tuple<long, long, int>> computed_ranges;

    long invalid_id_sum = 0;

    string original_range;
    while (getline(input, original_range, ','))
    {
        append_part_one_valid_ranges(original_range, computed_ranges);
    }

    for (int i = 0; i < computed_ranges.size(); i++)
    {
        long start;
        long end;
        int num_digits;
        tie(start, end, num_digits) = computed_ranges[i];

        // e.g. 5234 / 100 -> 52, 135138 / 1000 -> 135
        long divisor = (long)pow(10, num_digits / 2);
        long start_left = start / divisor;
        long end_left = end / divisor;
        
        for (long j = start_left; j <= end_left; j++) {
            long potential_invalid_id = j + (j * divisor);
            if (potential_invalid_id >= start && potential_invalid_id <= end)
            {
                invalid_id_sum += potential_invalid_id;
            }
        }
    }

    return invalid_id_sum;
}

int main()
{
    // 5287169884 - too low
    // 26255179562
    cout << "Part 1 solution: " << part_one() << endl;

    return 0;
}
