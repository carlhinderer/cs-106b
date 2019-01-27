/*
 * File: primefactorization.cpp
 * -------------------------------
 * This program prompts the user for an integer, then prints the
 *   integer's prime factorization.
 */

#include <iostream>
#include <math.h>
using namespace std;

int GetIntFromUser();
void PrintPrimeFactorization(int n);

int main() {
    int n = GetIntFromUser();
    PrintPrimeFactorization(n);
    return 0;
}

int GetIntFromUser() {
    int num;
    cout << "Enter an integer to get it's prime factorization: ";
    cin >> num;
    return num;
}

void PrintPrimeFactorization(int n) {
    /* Keep factoring 2 until you get an odd number */
    while(n % 2 == 0) {
        cout << "2 ";
        n /= 2;
    }

    /* Factor out odd factors larger than 3 */
    for (int i=3; i <= sqrt(n); i+=2) {
        while (n % i == 0) {
            cout << i << " ";
            n /= i;
        }
    }

    /* Handles case in which original n is odd prime */
    if (n > 2) {
        cout << n;
    }

    cout << endl;
}