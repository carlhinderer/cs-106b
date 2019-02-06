/* 
 * File: slots.cpp 
 * ------------------ 
 * Plays a slot machine game.
 *
 * Winning Combinations:
 *   BAR     BAR     BAR         pays$250
 *   BELL    BELL    BELL/BAR    pays$20
 *   PLUM    PLUM    PLUM/BAR    pays$14
 *   ORANGE  ORANGE  ORANGE/BAR  pays$10
 *   CHERRY  CHERRY  CHERRY      pays$7
 *   CHERRY  CHERRY  —           pays$5
 *   CHERRY  —       —           pays$2
 */

#include <iostream>
#include <iomanip>
#include <string>
#include "random.h"
using namespace std;

/* Constants */
const int STARTING_DOLLARS = 20;
const string SYMBOLS[] = {"CHERRY", "LEMON", "ORANGE", "PLUM", "BELL", "BAR"};
const int NUM_SYMBOLS = 6;
const int SYMBOL_WIDTH = 9;


/* Function Prototypes */
void PlaySlots();
int PullLever(int dollars);
void PrintLeverPull(string wheel1, string wheel2, string wheel3);
string SpinWheel();
int GetResult(int dollars, string wheel1, string wheel2, string wheel3);
int WinningResult(int dollars, int prize);
int LosingResult(int dollars);
bool PlayAgain(int dollars);
bool UserWantsToPlay();


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
    PrintLeverPull(wheel1, wheel2, wheel3);
    return GetResult(dollars, wheel1, wheel2, wheel3);
}

void PrintLeverPull(string wheel1, string wheel2, string wheel3) {
    cout << left
         << setw(SYMBOL_WIDTH) << wheel1 
         << setw(SYMBOL_WIDTH) << wheel2 
         << setw(SYMBOL_WIDTH) << wheel3 << " -- ";
}

string SpinWheel() {
    int symbolIndex = RandomInteger(0, NUM_SYMBOLS-1);
    return SYMBOLS[symbolIndex];
}

int GetResult(int dollars, string wheel1, string wheel2, string wheel3) {
    if (wheel1 == "BAR") {
        if (wheel2 == "BAR" && wheel3 == "BAR") {
            return WinningResult(dollars, 250);
        }
    }
    else if (wheel1 == "BELL") {
        if (wheel2 == "BELL" && (wheel3 == "BELL" || wheel3 == "BAR")) {
            return WinningResult(dollars, 20);
        }
    }
    else if (wheel1 == "PLUM") {
        if (wheel2 == "PLUM" && (wheel3 == "PLUM" || wheel3 == "BAR")) {
            return WinningResult(dollars, 14);
        }
    }
    else if (wheel1 == "ORANGE") {
        if (wheel2 == "ORANGE" && (wheel3 == "ORANGE" || wheel3 == "BAR")) {
            return WinningResult(dollars, 10);
        }
    }
    else if (wheel1 == "CHERRY") {
        int prize = 2;
        if (wheel2 == "CHERRY") {
            prize += 3;
            if (wheel3 == "CHERRY") prize += 2;
        }
        return WinningResult(dollars, prize);
    }

    return LosingResult(dollars);
}

int WinningResult(int dollars, int prize) {
    cout << "You win $" << prize << "." << endl;
    return dollars + prize;
}

int LosingResult(int dollars) {
    cout << "You lose." << endl;
    return dollars-1;
}

bool PlayAgain(int dollars) {
    cout << "Dollars: " << dollars << endl;
    if (dollars <= 0) return false;
    return UserWantsToPlay();
}

bool UserWantsToPlay() {
    while(true) {
        string input;
        cout << "Would you like to pull the lever? Enter 'Y' or 'N'. ";
        cin >> input;
        if (input == "Y") return true;
        if (input == "N") return false;
    }
}