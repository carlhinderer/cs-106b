/*
 * File: histogram.cpp
 * --------------------------
 * This program takes an array of integers and draws a histogram of their values
 *   with categories [0-9, 10-19, 20-29, ..., 90-99, 100].
 */

#include <iostream>
using namespace std;

const int TEST_VALUES[] = {2, 0, 29, 87, 100, 82, 45, 34, 56, 66, 66, 45, 78, 34, 90, 99};
const int TEST_VALUES_SIZE = 16;

void DrawHistogram(const int values[], int valuesSize);
void InitializeCounts(int counts[]);
void GetCounts(int counts[], const int values[], int valuesSize);
void DrawDataPoints(int counts[]);
void DrawHistogramKey();

int main() {
    DrawHistogram(TEST_VALUES, TEST_VALUES_SIZE);
    return 0;
}

void DrawHistogram(const int values[], int valuesSize) {
    int counts [11];
    InitializeCounts(counts);
    GetCounts(counts, values, valuesSize);
    DrawDataPoints(counts);
    DrawHistogramKey();
}

void InitializeCounts(int counts[]) {
    for (int i=0; i<11; i++) {
        counts[i] = 0;
    }
}

void GetCounts(int counts[], const int values[], int valuesSize) {
    for (int i=0; i < valuesSize; i++) {
        int column = values[i] / 10;
        counts[column]++;
    }
}

int LargestCount(int counts[]) {
    /* Get largest count */
    int largestCount = 0;
    for (int i=0; i < 11; i++) {
        if (counts[i] > largestCount) largestCount = counts[i];
    }
    return largestCount;
}

void DrawDataPoints(int counts[]) {
    int largestCount = LargestCount(counts);
    for (int i=0; i < largestCount; i++) {
        for (int j=0; j < 11; j++) {
            if (counts[j] >= largestCount - i) {
                cout << "*";
            } else {
                cout << " ";
            }
            cout << "  ";
        }
        cout << endl;
    } 
}

void DrawHistogramKey() {
    for (int i=0; i < 11; i++) {
        cout << i*10 << " ";
    }
    cout << endl;
}