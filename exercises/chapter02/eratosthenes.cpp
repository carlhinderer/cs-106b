/*
 * File: eratosthenes.cpp
 * --------------------------
 * Use the 'Sieve of Eratosthenes' algorithm to find all the prime numbers
 *   between 2 and 1000.
 */

#include <iostream>
#include <math.h>
using namespace std;

const int UPPER_BOUND = 1000;

void PrintPrimeNumbers(int upperBound);

int main() {
    PrintPrimeNumbers(UPPER_BOUND);
    return 0;
}

void PrintPrimeNumbers(int upperBound) {
    /* Initialize primes array */
    bool allNumbers[upperBound+1];
    for (int i=0; i <= upperBound; i++) {
        allNumbers[i] = true;
    }

    /* Run sieve of eratosthenes */
    for (int i=2; i < sqrt(upperBound); i++) {
        if (allNumbers[i]) {
            for (int j=i*2; j <= upperBound; j+=i) {
                allNumbers[j] = false;
            }
        }
    }

    /* Print primes */
    for (int i=2; i<= upperBound; i++) {
        if (allNumbers[i]) {
            cout << i << " ";
        }
    }
}