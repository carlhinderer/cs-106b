/*
 * File: perfectnumbers.cpp
 * --------------------------
 * This program prints all the perfect numbers from
 *   1 to 99999.
 */

#include <iostream>
using namespace std;

const int LOWER_BOUND = 1;
const int UPPER_BOUND = 99999;

void PrintPerfectNumbers(int lowerBound, int upperBound);
bool IsPerfect(int num);

int main() {
    PrintPerfectNumbers(LOWER_BOUND, UPPER_BOUND);
}

void PrintPerfectNumbers(int lowerBound, int upperBound) {
    for (int i=lowerBound; i <= upperBound; i++) {
        if (IsPerfect(i)) {
            cout << "Found perfect number: " << i << endl;
        }
    }
}

bool IsPerfect(int num){
    int factorSum = 0;
    for(int i=1; i < num-1; i++) {
        if (num % i == 0) factorSum += i;
    }
    return factorSum == num;
}