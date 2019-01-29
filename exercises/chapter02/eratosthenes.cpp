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
void InitializePrimes(bool primes[], int upperBound);
void SieveOfEratosthenes(bool primes[], int upperBound);
void PrintPrimes(bool primes[], int upperBound);

int main() {
    PrintPrimeNumbers(UPPER_BOUND);
    return 0;
}

void PrintPrimeNumbers(int upperBound) {
    bool primes[upperBound+1];
    InitializePrimes(primes, upperBound);
    SieveOfEratosthenes(primes, upperBound);
    PrintPrimes(primes, upperBound);
}

void InitializePrimes(bool primes[], int upperBound) {
    for (int i=0; i <= upperBound; i++) {
        primes[i] = true;
    }    
}

void SieveOfEratosthenes(bool primes[], int upperBound) {
    for (int i=2; i < sqrt(upperBound); i++) {
        if (primes[i]) {
            for (int j=i*2; j <= upperBound; j+=i) {
                primes[j] = false;
            }
        }
    }
}

void PrintPrimes(bool primes[], int upperBound) {
    for (int i=2; i<= upperBound; i++) {
        if (primes[i]) {
            cout << i << " ";
        }
    }
}