/* 
 * File: slots.cpp 
 * ------------------ 
 * Plays a slot machine game.
 *
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include "random.h"
using namespace std;

/* Type definitions */
struct winningCombinationT {
    string wheel1;
    string wheel2;
    string wheel3;
    int prize;
};

/* Constants */
const int STARTING_DOLLARS = 20;
const string SYMBOLS[] = {"CHERRY", "LEMON", "ORANGE", "PLUM", "BELL", "BAR"};
const int numSymbols = 6;


/* Function Prototypes */
void PlaySlots();
int PullLever(int dollars);
string SpinWheel();
int GetResult(int dollars, string wheel1, string wheel2, string wheel3);
bool PlayAgain(int dollars);


/* Main Execution */
int main() {
    PlaySlots();
    return 0;
}


/* Function definitions */
void PlaySlots() {
    int dollars = STARTING_DOLLARS;
    while (PlayAgain(dollars)) {
        dollars = PullLever(dollars);
    }
    cout << "Goodbye." << endl;
}

int PullLever(int dollars) {
    string wheel1 = SpinWheel();
    string wheel2 = SpinWheel();
    string wheel3 = SpinWheel();
    return GetResult(dollars, wheel1, wheel2, wheel3);
}

string SpinWheel() {
    int symbolIndex = RandomInteger(1, numSymbols);
    return SYMBOLS[symbolIndex];
}

int GetResult(int dollars, string wheel1, string wheel2, string wheel3) {
    cout << wheel1 << "  " << wheel2 << "  " << wheel3 << endl;
    cout << "You lost." << endl;
    return dollars - 1;
}

bool PlayAgain(int dollars) {
    cout << "Dollars: " << dollars << endl;
    if (dollars <= 0) return false;
    while(true) {
        string input;
        cout << "Would you like to pull the lever? Enter 'Y' or 'N'." << endl;
        cin >> input;
        if (input == "Y") return true;
        if (input == "N") return false;
    }
}