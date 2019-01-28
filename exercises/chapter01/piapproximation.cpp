/*
 * File: piapproximation.cpp
 * -------------------------------
 * This program uses 2 different methods of approximating pi.
 *   1. Leibniz series method
 *   2. Inscribed rectangles method
 */

#include <iostream>
#include <math.h>
using namespace std;

const int NUM_SERIES_TERMS = 10000;
const int NUM_RECTANGLES = 100;

float LeibnizSeries(int numTerms);
float InscribedRectangles(int numRectangles);

int main() {
    cout << "Leibniz series approximation with " 
         << NUM_SERIES_TERMS
         << " terms: " 
         << LeibnizSeries(NUM_SERIES_TERMS) 
         << endl;

    cout << "Inscribed rectangles approximation with "
         << NUM_RECTANGLES
         << " rectangles: " 
         << InscribedRectangles(NUM_RECTANGLES)
         << endl;
    return 0;
}

float LeibnizSeries(int numTerms) {
    float approx = 0.0;
    int denominator = 1;
    for (int i=0; i < numTerms; i++) {
        if (i % 2 == 0) {
            approx += (1.0 / denominator);
        } else {
            approx -= (1.0 / denominator);
        }
        denominator += 2;
    }
    return approx * 4;
}

float InscribedRectangles(int numRectangles) {
    float approx = 0.0;
    float xStart = 0.0;
    float width = 1.0 / numRectangles;
    for (int i=0; i < numRectangles; i++) {
        float xMid = xStart + (width / 2);
        float height = sqrt(1 - (xMid * xMid));
        approx += (width * height);
        xStart += width;
    }
    return approx * 4;
}