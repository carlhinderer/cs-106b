/*
 * File: powertab.cpp
 * ------------------
 * This program generates a table comparing values
 * of the functions n^2 and 2^n.
 */

#include "genlib.h"
#include <iostream>
#include <iomanip>

/*
 * Constants
 * ---------
 * LOWER_LIMIT -- Starting value for the table
 * UPPER_LIMIT -- Final value for the table
 */

const int LOWER_LIMIT = 0;
const int UPPER_LIMIT = 12;

/* Private function prototypes */
int RaiseIntToPower(int n, int k);

/* Main program */
int main() {
    cout << "    |   2 |    N" << endl;
    cout << "  N |  N  |   2" << endl;
    cout << "----+-----+------" << endl;
    for (int n = LOWER_LIMIT; n <= UPPER_LIMIT; n++) {
        cout << setw(3) << n << " |" ;
        cout << setw(4) << RaiseIntToPower(n, 2) << " |" ;
        cout << setw(5) << RaiseIntToPower(2, n) << endl;
    }
    return 0;
}

/*
 * Function: RaiseIntToPower
 * Usage: p = RaiseIntToPower(n, k);
 * ---------------------------------
 * This function returns n to the kth power.
 */
int RaiseIntToPower(int n, int k) {
    int result;
    result = 1;
    for (int i = 0; i < k; i++) {
        result *= n;
    }
    return result;
}