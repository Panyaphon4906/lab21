#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 1) {
        cout << "Please input numbers to find average." << endl;
        return 0;
    }

    vector<int> numbers;
    
    for (int i = 1; i < argc; ++i) {
        stringstream ss(argv[i]);
        int num;
        ss >> num; 
        numbers.push_back(num);
    }

    int sum = 0;
    for (int num : numbers) {
        sum += num;
    }

    int average = sum / numbers.size();

    cout << "---------------------------------" << endl;
    cout << "Average of " << numbers.size() << " numbers = " 
         << fixed << setprecision(3) << average << endl;
    cout << "---------------------------------" << endl;

    return 0;
}

